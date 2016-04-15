#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define max_size_list 20

struct list_s
{
    char * elements;
    char size;
};

list_t * list_t_new ()
{
    list_t * list = malloc (sizeof (list_t));
    list->elements = malloc (max_size_list * sizeof(char));
    list->size = 0;
    return list;
}

void list_t_add_elem_end (list_t * list, char value)
{
    if (value == NULL)
        return;
    int index;
    if (list->size == max_size_list)
        {
            for (index = 0; index < (max_size_list - 1); index++)
            list->elements[index] = list->elements[index + 1];
            list->elements [max_size_list - 1] = value;
            return ;
        }
    list->elements[list->size] = value;
    list->size++;
}

void list_t_change_elem_by_index (list_t * list, char value, int ind)
{
    if (ind > list->size || value == NULL)
        return;
    list->elements[ind] = value;
}

void list_t_free (list_t * list)
{
    free (list->elements);
    free (list);
}

void list_t_print (list_t * list)
{
    puts ("\nThe elements of list:");
    int i;
    for ( i = 0; i < list->size; i++)
    {
        printf ("'%c' ", list->elements[i]);
    }
}

int list_t_get_size (list_t * list)
{
    return list->size;
}

char list_t_get_elem (list_t * list, int index)
{
    return list->elements[index];
}
