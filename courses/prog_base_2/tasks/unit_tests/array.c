#include "array.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct array_s {
    unsigned int * elements;
    unsigned int size;
};

array_t * array_new(void)
{
    array_t * array = malloc (sizeof(array_t));
    array->size = 0;
    array->elements = malloc(0);
    return array;
}

int array_count(array_t * array)
{
    return array->size;
}

void array_free(array_t * array)
{
    free (array->elements);
    free(array);
}

int array_isSame(array_t * array, unsigned int elem)
{
    int i;
    for (i = 0; i < array->size; i++)
    {
        if (array->elements[i] == elem)
            return 1;
    }
    return 0;
}

int array_add (array_t * array, unsigned int elem)
{
    int check = array_isSame (array, elem);
    if (check == 0)
    {
        array->size++;
        array->elements = realloc(array->elements, array->size * sizeof (int));
        array->elements[array->size - 1] = elem;
    }
}

void array_delete (array_t * array, unsigned int elem)
{
    int i;
    for (i = 0; i < array->size; i++)
        if (array->elements[i] == elem)
        {
            memmove(array->elements + i, array->elements + i + 1, (array->size - i - 1) * sizeof(int));
            array->size--;
            array->elements = realloc (array->elements, array->size * sizeof (int));
        }
}

array_t * array_rand (unsigned int size)
{
    srand(time(NULL));
    int i;
    int elem;
    array_t * array = array_new();
    if (size < 1)
        return array;
    for ( i = 0; i < size; i++)
    {
        elem = rand()%100;
        array_add(array, elem);
    }
    return array;
}

array_t * array_unific (array_t * array1, array_t * array2)
{
    int i;
    array_t * array3 = array_new();
    for (i = 0; i < array1->size; i++)
        array_add(array3, array1->elements[i]);
    for (i = 0; i < array2->size; i++)
        array_add(array3, array2->elements[i]);
    return array3;
}

array_t * array_intersec (array_t * array1, array_t * array2)
{
    int i;
    array_t * array3 = array_new();
    for (i = 0; i < array1->size; i++)
        if (array_isSame(array2, array1->elements[i]) == 1)
        array_add(array3, array1->elements[i]);
    return array3;
}

array_t * array_dif (array_t * array1, array_t * array2)
{
    int i;
    array_t * array3 = array_new();
    for (i = 0; i < array1->size; i++)
       {
          if (array_isSame(array2, array1->elements[i]) == 0)
          array_add(array3, array1->elements[i]);
       }
    return array3;
}

void array_print(const array_t * array)
{
    int i;
    printf ("Here is the array:  (");
    for (i = 0; i < (array->size - 1); i++)
        printf("%i, ", array->elements[i]);
    printf ("%i", array->elements[i++]);
    printf (")\n");
}
