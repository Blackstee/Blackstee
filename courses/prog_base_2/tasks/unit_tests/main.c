#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "array.h"

// unit-test function
static void new_void_zeroCount(void **state)
{
    array_t * array = array_new();
    assert_int_equal(array_count(array), 0);
    array_free(array);
}

static void add_oneValue_countOne(void **state)
{
    array_t * array = array_new();
    array_add (array, 34);
    assert_int_equal(array_count(array), 1);
    array_free(array);
}

static void add_twoValues_countTwo(void **state)
{
    array_t * array = array_new();
    array_add (array, 8);
    array_add (array, 42);
    assert_int_equal(array_count(array), 2);
    array_free(array);
}

static void delete_hasoneaddedValue_countZero(void **state)
{
    array_t * array = array_new();
    array_add (array, 34);
    array_delete (array, 34);
    assert_int_equal(array_count(array), 0);
    array_free(array);
}

static void rand_fourValues_countFour(void **state)
{
    array_t * array = array_rand(4);
    assert_int_equal(array_count(array), 4);
    array_free(array);
}

static void unific_twoArrays_unification(void **state)
{
    array_t * array1 = array_new();
    array_add (array1, 34);
    array_t * array2 = array_new();
    array_add (array2, 76);
    array_t * array3 = array_unific(array1, array2);
    assert_int_equal(array_count(array3), 2);
    assert_true (array_isSame(array3, 34));
    assert_true (array_isSame(array3, 76));
    array_free(array1);
    array_free(array2);
    array_free(array3);
}

static void intersec_twoArrays_intersection(void **state)
{
    array_t * array1 = array_new();
    array_add (array1, 34);
    array_add (array1, 54);
    array_add (array1, 32);
    array_t * array2 = array_new();
    array_add (array2, 76);
    array_add (array2, 34);
    array_add (array2, 88);
    array_t * array3 = array_intersec(array1, array2);
    assert_int_equal(array_count(array3), 1);
    assert_true (array_isSame(array3, 34));
    assert_false (array_isSame(array3, 76));
    assert_false (array_isSame (array3, 88));
    array_free(array1);
    array_free(array2);
    array_free(array3);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zeroCount),
        cmocka_unit_test(add_oneValue_countOne),
        cmocka_unit_test(add_twoValues_countTwo),
        cmocka_unit_test(delete_hasoneaddedValue_countZero),
        cmocka_unit_test(rand_fourValues_countFour),
        cmocka_unit_test(unific_twoArrays_unification),
        cmocka_unit_test(intersec_twoArrays_intersection),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
