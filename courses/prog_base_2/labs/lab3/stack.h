#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "list.h"

enum status_en
{
    STACK_FULL,
    STACK_EMPTY,
    STACK_EV,
};

typedef struct user_s
{
   char users [50];
} user_t;

typedef struct stack_s stack_t;

stack_t * stack_t_new(int number);

void stack_t_free(stack_t * st);

int stack_t_getCount(stack_t * st);

void stack_t_push(stack_t * st, int el);

int stack_t_pop(stack_t * st);

int stack_t_peek(stack_t * st);

void stack_t_print (stack_t * st);

stack_t * stack_t_make_stack (int count_to_fill, int number);

void stack_t_fill_random (stack_t * st, int count_to_fill);

int stack_t_pop_val (stack_t * st);

void stack_t_rand_choice (stack_t * st1, stack_t * st2);

typedef void (*cb_fn)(void * listener, stack_t * st, enum  status_en status, int value);

void stack_subscribe_multi (stack_t * stack, void * listener, cb_fn cb);

void stack_subscribe_empty (stack_t * stack, void * listener, cb_fn cb);

void stack_subscribe_full (stack_t * stack, void * listener, cb_fn cb);

void stack_Event (void * listener, stack_t * stack, enum status_en status, int value);

void multi (event_t * ev, char message[70] , stack_t * st, int status, int value);

#endif // STACK_H_INCLUDED
