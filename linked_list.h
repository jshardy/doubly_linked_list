/************************************************************
 * Professor: Philip Howard Phd
 * Student: Joshua Hardy
 * Date: 5/19/2019
 * Modified:
 * Doubly Linked Lists!
 * Written so that I never have to write another linked list!
*************************************************************/ 
#pragma once

/***********************************
 * Doubly Linked list ITEM
 * data - store user data
 * Node pointers next, and previous
 **********************************/
typedef struct list_item_s
{
    void *data;
    struct list_item_s *next;
    struct list_item_s *previous;
} list_item_t;

/************************************
 *  Doubly linked list header
 *  Keeps track of head, and tail.
 *  Size
 *  Match function pointer
 *  Destroy function pointer
 * **********************************/
typedef struct list_s
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    list_item_t *head;
    list_item_t *tail;
} list_t;

/*************************************************************************
 * Purpose: Initialzed the linked list. Must be called before first use.
 * Precondition:
 *          Pass NULL or function pointer to your match function
 *          and your destroy function. Match is called when searching
 *          for data. Destroy is called on list_destroy or data
 *          removal from list.
 *
 * Postcondition:
 *          Returns valid list on success. Returns NULL on failure.
 ************************************************************************/
list_t *list_init(int (*match)(const void *, const void *), 
                  void (*destroy)(void *data));

/*************************************************************************
 * Purpose: Appends an item to doubly linked list.
 * Precondition: Pass valid *list and *data to be inserted.
 * Postcondition: Returns 0 on success. Returns -1 on failure.
 ************************************************************************/
int list_append(list_t *list, void *data);

/**********************************************************************
 * Purpose: Prepends items to doubly linked list.
 * Precondition: Pass a valid *list and a valid *data.
 * Postcondition: Returns 0 on success. Returns -1 on failure.
 ************************************************************************/
int list_prepend(list_t *list, void *data);

/**********************************************************************
 * Purpose: Returns item at index
 * Precondition: Pass a valid list_t* and a valid index
 * Postcondition: Returns address of list_item_t->data
 *                Returns NULL if index is out of range
 *                or list is empty.
 ************************************************************************/
void *list_at_index(list_t *list, int index);
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
 * Postcondition: Returns 0 on success. Returns the linked list item
 *          that error occured on.
 ************************************************************************/
void *list_do(list_t *list, int (*do_func)(void *data));

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
int list_remove_data(list_t *list, void *data);

/**********************************************************************
 * Purpose: Displays all nodes in doubly linked list.
 * Precondition: Pass a valid *list;
 * Postcondition: Data displayed to stdout with \n for each item.
 ************************************************************************/
void list_display(list_t *);

/**********************************************************************
 * Purpose: Deletes all item in doubly linked list.
 * Precondition: Pass valid *list.
 *    Uses destroy pointer given at list_init or list_set_destroy.
 *    (*dstroy)(void *data)
 *    Function pointer will be ignored if NULL
 * Postcondition:  List and list items are free.
 *************************************************************************/
void list_destroy(list_t *list);


/**********************************************************************
 * Purpose: Deletes all item in doubly linked list.
 * Precondition: Pass valid *list.
 *      *Uses destroy pointer given at list_init or list_set_destroy.
 *      (*dstroy)(void *data)
 *      Function pointer will be ignored if NULL
 * Postcondition:
 *      List and list items are free.
 ************************************************************************/
void list_set_destroy(list_t *, void (*destroy)(void *data));

/**********************************************************************
 * Purpose: Sets match function pointer for use after list_init has
 *          been called. Used by linked list to compare items.
 *          Used in list_remove_data.
 * Precondition: Pass a valid function pointer of type
 *               (*match)(const void *, const void *).
 *               Function pointer ill be ignored if NULL.
 * Postcondition: Match function set.
 ************************************************************************/
void list_set_match(list_t *, 
        int (*match)(const void *, const void *));

/************************************************************************
* Purpose: Gets size of doubly linked list
* Precondition: list_init must have been called on list.
* Postcondition: Returns size of list
*************************************************************************/
int list_size(list_t *list);
