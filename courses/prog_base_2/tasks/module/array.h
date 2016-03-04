#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

typedef struct array_s array_t;

array_t * array_new(void);
void array_free(array_t * array);
int array_isSame(array_t * array, unsigned int elem);
int array_add (array_t * array, unsigned int elem);
void array_delete (array_t * array, unsigned int elem);
array_t * array_rand (unsigned int size);
array_t * array_unific (array_t * array1, array_t * array2);
array_t * array_intersec (array_t * array1, array_t * array2);
array_t * array_dif (array_t * array1, array_t * array2);
void array_print(const array_t * self);

#endif // ARRAY_H_INCLUDED
