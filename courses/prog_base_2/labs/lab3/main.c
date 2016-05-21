#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "list.h"
#include "stack.h"
#include <cmocka.h>
#include <time.h>


// unit-test functions

//create new stack
static void new_void_zerocount (void ** state)
{
    stack_t * stack = stack_t_new(1);
    assert_int_equal(stack_t_getCount(stack), 0);
    stack_t_free (stack);
}

//push element to stack, checking count
static void add_element_onecount (void ** state)
{
    stack_t * stack = stack_t_new(1);
    stack_t_push(stack, 5);
    assert_int_equal(stack_t_getCount(stack), 1);
    stack_t_free (stack);
}

//push element to stack, checking value
static void add_element_value (void ** state)
{
    stack_t * stack = stack_t_new(1);
    stack_t_push(stack, 5);
    assert_int_equal(stack_t_peek(stack), 5);
    stack_t_free (stack);
}

//delete element from stack, checking value and count
static void pop_element_onecountAndValue (void ** state)
{
    stack_t * stack = stack_t_new(1);
    stack_t_push(stack, 9);
    stack_t_push(stack, 7);
    stack_t_pop(stack);
    assert_int_equal(stack_t_peek(stack), 9);
    assert_int_equal(stack_t_getCount (stack), 1);
    stack_t_free (stack);
}

//create new list
static void new_void_zeroc(void ** state)
{
    list_t * list = list_new();
    assert_int_equal(list_getCount(list), 0);
    free(list);
};

//adding the event to list and checking count
static void add_EventToList_Onecount(void ** state)
{
    list_t * list = list_new();
    event_t * ev = malloc(sizeof(event_t));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(list, ev);
    assert_int_equal(list_getCount(list), 1);
    free(ev);
    free(list);
}


//adding the event to list and checking value
static void add_EventToList_Event(void ** state)
{
    list_t * list = list_new();
    event_t * ev = malloc(sizeof(event_t));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(list, ev);
    assert_memory_equal(list_getEl(list, 0), ev, 0);
    free(ev);
    free(list);
}

//deleting event from list, checking count
static void pop_EventFromList_Zerocount(void ** state)
{
    list_t * list = list_new();
    event_t * ev = malloc(sizeof(event_t));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(list, ev);
    list_pop_back(list);
    assert_int_equal(list_getCount(list), 0);
    free(ev);
    free(list);
}

//deleting event from list, checking value
static void pop_EventFromList_Event (void ** state)
{
    list_t * list = list_new();
    event_t * ev = malloc(sizeof(event_t));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(list, ev);
    assert_memory_equal(list_pop_back(list), ev, 0);
    free(ev);
    free(list);
}


void user_tests()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zerocount),
        cmocka_unit_test(add_element_onecount),
        cmocka_unit_test(add_element_value),
        cmocka_unit_test(pop_element_onecountAndValue),
        cmocka_unit_test(new_void_zeroc),
        cmocka_unit_test(add_EventToList_Onecount),
        cmocka_unit_test(add_EventToList_Event),
        cmocka_unit_test(pop_EventFromList_Zerocount),
        cmocka_unit_test(pop_EventFromList_Event)
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}

int main(void) {
    //user_tests ();
    srand (time (NULL));
    stack_t * st1 = stack_t_make_stack(7, 1);
    stack_t * st2 = stack_t_make_stack(2, 2);
    stack_t_print(st1);
    stack_t_print (st2);
   // stack_t * st1 = stack_t_new();
    //stack_t * st2 = stack_t_new ();
    stack_subscribe_full (st1, st2, stack_Event);
    stack_subscribe_full (st2, st1, stack_Event);
    stack_subscribe_empty (st1, st2, stack_Event);
    stack_subscribe_empty (st2, st1, stack_Event);
    user_t users1[4] = {{"Vasya"}, {"Galya"}};
    user_t users2[3] = {{"Petya"}, {"Roma"}};
    for(int i = 0; i < 2; i++)
    {
        stack_subscribe_multi (st1, &users1[i], stack_Event);
        stack_subscribe_multi(st2, &users2[i], stack_Event);
    }
    stack_t_print(st1);
    stack_t_print (st2);

    while(1)
    {
        stack_t_rand_choice(st1, st2);

    }

    stack_delete(st1);
    stack_delete(st2);
    return 0;
}
