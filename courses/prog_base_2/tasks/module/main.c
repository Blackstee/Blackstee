#include <stdio.h>
#include <stdlib.h>

#include "array.h"

#include <time.h>
#include <stdlib.h>

int main(void) {

    srand(time(NULL));
    array_t * array1 = array_new();
    array_add(array1, 36);
    array_print (array1);
    array_add(array1, 45);
    array_print (array1);
    array_add(array1, 2);
    array_print(array1);
    array_delete(array1, 2);
    array_print (array1);
    array_t * array2 = array_rand(2);
    array_t * array3 = array_unific(array1, array2);
    array_t * array4 = array_dif(array1, array2);
    array_print(array2);
    array_print(array3);
    array_print(array4);
    array_free (array1);
    array_free (array2);
    array_free (array3);
    array_free (array4);
    return 0;
}
