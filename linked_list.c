#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/*************************************************************************
 * Purpose: Initialzed the linked list. Must be called before first use.
 * Precondition: Pass NULL or function pointer to your match function
 *          and your destroy function. Match is called when searching
 *          for data. Destroy is called on list_destroy or data
 *          removal from list.
 * Postcondition:
 *          Returns valid list on success. Returns NULL on failure.
 ************************************************************************/
list_t *list_init(int (*match)(const void *key1, const void *key2),
                  void (*destroy)(void *data))
{
    list_t *new_list = malloc(sizeof(list_t));

    if(!new_list)
        return NULL;

    memset(new_list, 0, sizeof(list_t));
    new_list->destroy = destroy;
    new_list->match = match;

    return new_list;
}

/*************************************************************************
 * Purpose: Appends an item to doubly linked list.
 * Precondition: Pass valid *list and *data to be inserted.
 * Postcondition: Returns 0 on success. Returns -1 on failure.
 ************************************************************************/
int list_append(list_t *list, void *data)
{
    if(!list)
        return -1;

    list_item_t *new_item = calloc(sizeof(list_item_t), 1);
    if(!new_item)
        return -1;

    new_item->data = data;
    list->size++;

    if(!list->head) // Handle head case \_("/)_/
    {
        list->head = new_item;
        list->tail = new_item;
    }
    else // Inserting at end
    {
        list->tail->next = new_item;
        new_item->previous = list->tail;
        list->tail = new_item;
    }
    return 0;
}

/**********************************************************************
 * Purpose: Prepends items to doubly linked list.
 * Precondition: Pass a valid *list and a valid *data.
 * Postcondition: Returns 0 on success. Returns -1 on failure.
 ************************************************************************/
int list_prepend(list_t *list, void *data)
{
    if(!list)
        return -1;

    list_item_t *new_item = calloc(sizeof(list_item_t), 1);
    if(!new_item)
        return -1;

    new_item->data = data;
    list->size++;

    if(!list->head) // Handle head case
    {
        list->head = new_item;
        list->tail = new_item;
    }
    else // Handle insert at front
    {
        new_item->next = list->head;
        list->head->previous = new_item;
        list->head = new_item;
    }
    return 0;
}

/**********************************************************************
 * Purpose: Returns item at index
 * Precondition: Pass a valid list_t* and a valid index
 * Postcondition: Returns address of list_item_t->data
 *                Returns NULL if index is out of range
 *                or list is empty.
 ************************************************************************/
void *list_at_index(list_t *list, int index)
{
    list_item_t *travel = list->head;
    if(list && list->head && index >= 0 && index < list->size)
    {
        for(int i = 0; i < index; i++)
            travel = travel->next;

        return travel->data;
    }
    return NULL;
}

/**********************************************************************
 * Purpose: Iterates over list executing user specified function with
 *          the data.
 * Precondition: Pass a valid *list and a valid function pointer.
 *          int my_do_function(void *data)
 *          ***do_func function is expected to return 0.***
 *          If  function returns anything else,
 *          it will stop iteration and return to you
 *          the linked list item that caused the none
 *          NULL value.
 * Postcondition: Returns 0 on success. On error the linked list item
 *          that error occured on is returned.
 ************************************************************************/
void *list_do(list_t *list, int (*do_func)(void *data))
{
    if(list && do_func)
    {
        list_item_t *travel = list->head;
        while(travel)
        {
            if((*do_func)(travel->data) != 0)
                return travel;

            travel = travel->next;
        }
    }
    return NULL;
}

/**********************************************************************
 * Purpose: list_remove_data(list, data) - Removes data from list
 * Precondition:
 *          *match* function pointer must be passed into list_init
 *          or list_set_match();
 *
 *          *match* is expected to act like memcpy/strcmp
 *          -1 left side greator than
 *          0 both equal
 *          1 right side greator than
 *
 *          *destroy* function pointer must be passed into list_init
 *          or list_set_destroy() -- IF you can want it to free your
 *          data for you.
 *      
 *          A valid list_t* from list_init()
 * Postcondition:
 *          Returns 0 for success and -1 for failure
 ************************************************************************/
int list_remove_data(list_t *list, void *data)
{
    list_item_t *found = NULL;
    if(!list && !list->head && !list->match)
        return -1;

    list_item_t *travel = list->head;
    while(travel)
    {
        if((*list->match)(data, travel->data) == 0)
        {
            found = travel;
            break;
        }
        travel = travel->next;
    }

    if(!found)
        return -1;
    
    if(found == list->head)
    {
        list->head = list->head->next;
        if(list->head)
            list->head->previous = NULL;
    }
    else if(found == list->tail)
    {
        list->tail->previous->next = NULL;
        list->tail = list->tail->previous;
    }
    else
    {
        found->previous->next = found->next;
        found->next->previous = found->previous;
    }
    
    if(list->destroy)
        (*list->destroy)(found->data);

    free(found);
    list->size--;

    return 0;
}

// WARNING - Assumes list->item->data is a char *
// In future will be marked static
/**********************************************************************
 * Purpose: Displays all nodes in doubly linked list.
 * Precondition: Pass a valid *list;
 * Postcondition: Data displayed to stdout with \n for each item.
 ************************************************************************/
void list_display(list_t *list)
{
    if(!list)
        return;

    list_item_t *travel = list->head;
    int i = 0;
    while(travel)
    {
        fprintf(stdout, "%d: %s\n", i, (char*)travel->data);
        i++;
        travel = travel->next;
    }
}

/**********************************************************************
 * Purpose: Deletes all item in doubly linked list.
 * Precondition: Pass valid *list.
 *      *Uses destroy pointer given at list_init or list_set_destroy.
 *      (*dstroy)(void *data)
 *      Function pointer will be ignored if NULL
 * Postcondition:
 *      List and list items are free.
 ************************************************************************/
void list_destroy(list_t *list)
{
    if(!list)
        return;

    list_item_t *travel = list->head;
    while(travel)
    {
        list_item_t *to_delete = travel;
        travel = travel->next;

        if(list->destroy)
            (*list->destroy)(to_delete->data);
     
        free(to_delete);
    }
    free(list);
}

/**********************************************************************
 * Purpose: Sets match function pointer for use after list_init has
 *          been called. Used by linked list to compare items.
 *          Used in list_remove_data.
 * Precondition: Pass a valid function pointer of type
 *               (*match)(const void *, const void *).
 *               Function pointer ill be ignored if NULL.
 * Postcondition: Match function set.
 ************************************************************************/
void list_set_match(list_t *list, 
    int (*match)(const void *key1, const void *key2))
{
    list->match = match;
}

/************************************************************************
 * Purpose: Sets destroy function pointer after list_init has been called.
 *          This is called to delete allow freeing of user data in list.
 *          list_remove_data and list_destroy call this.
 * Precondition: Pass a valid function pointer in the form
 *               (*destroy)(void *data)
 *               Function pointer will be ignored if it is NULL.
 * Postcondition: Destroy function set.
 ************************************************************************/
void list_set_destroy(list_t *list, void (*destroy)(void *data))
{
    list->destroy = destroy;
}

/************************************************************************
 * Purpose: Gets size of doubly linked list
 * Precondition: list_init must have been called on list.
 * Postcondition: Returns size of list
 ************************************************************************/
int list_size(list_t *list)
{
    if(!list)
        return -1;

    return list->size;
}
