#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "linked_list.h"

int match(const void *key1, const void *key2);
void test_destroy_func(void *data);
int do_test(void *data);
char **alloc_test_strings(int count);
void display_strings(char **strings);
void free_strings(char **strings);
char *itoa(long n);

int main()
{
    list_t *list = list_init(&match, &test_destroy_func);

    if(!list)
        return -1;

    const int count = 10000;
    char **strings = alloc_test_strings(count);
    // display_strings(strings);

    list_display(list);
        
    for(int i = 0; i < count / 2; i++)
    {
        list_append(list, strings[i]);
    }
    
    for(int i = count / 2; i < count; i++)
    {
        list_prepend(list, strings[i]);
    }

    
    // list_remove_data(list, strings[0]);
    // list_remove_data(list, strings[2]);

    // list_remove_data(list, strings[9]);

    list_do(list, &do_test);
    
    // Test removing all from head
    // for(int i = 0; i < count; i++)
    // {
    //     list_remove_data(list, strings[i]);
    // }
    fprintf(stdout, "Linked list size: %d\n", list->size);
    
    // Test removing from the tail
    for(int i = count - 1; i != 0; i--)
    {
        // list_remove_data(list, strings[i]);
    }
    
    char *find_test = list_find(list, "Test string #7");
    
    if(find_test)
        printf("%s\n%s\n%s\n", find_test, find_test, find_test);

    // fprintf(stdout, "Linked list size: %d\n", list->size);

    list_destroy(list);
    //free_strings(strings);
    free(strings); // valgrind doesn't detect this??..
    return 0;
}

int do_test(void *data)
{
    fprintf(stdout, "%s\n", (char*)data);
    return 0;
}

int match(const void *key1, const void *key2)
{
    const char *k1 = (char*) key1;
    const char *k2 = (char*) key2;

    return strcmp(k1, k2);
}

void test_destroy_func(void *data)
{
    if(data)
        free(data);
}

char **alloc_test_strings(int count)
{
    const char *test_string = "Test string #";
    char **strings = calloc(sizeof(char*), count + 1);
    
    for(int i = 0; i < count; i++)
    {
        char *num = itoa(i);
        int size = strlen(test_string) + strlen(num) + 1;
        strings[i] = calloc(sizeof(char), size);
        strcpy(strings[i], test_string);
        strcat(strings[i], num);
        free(num);
    }
    strings[count] = NULL; // null terminate it.
    return strings;
}

void display_strings(char **strings)
{
    int i = 0;
    if(strings)
    {
        while(strings[i])
            fprintf(stdout, "%s\n", strings[i++]);
    }
}

void free_strings(char **strings)
{
    int i = 0;
    if(strings)
    {
        while(strings[i])
            free(strings[i++]);

        free(strings);
    }
}

char *itoa(long n)
{
    int len = n == 0 ? 1 : floor(log10l(labs(n))) + 1;
    if (n < 0) len++; // room for negative sign '-'

    char *buf = calloc(sizeof(char), len + 1); // +1 for null
    snprintf(buf, len + 1, "%ld", n);

    return buf;
}
