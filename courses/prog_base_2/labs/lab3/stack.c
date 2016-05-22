#include "stack.h"
#include "list.h"

#include <stdlib.h>
#include <stdio.h>

struct stack_s
{
    char array [10];
    int count;
    int number;
    void * full_sb;
    void * empty_sb;
    cb_fn full_cb;
    cb_fn empty_cb;
    list_t * multi;
};


stack_t * stack_t_new(int number)
{
    stack_t * st = malloc(sizeof(struct stack_s));
    st->count = 0;
    st->number = number;
    st->multi = list_new();
    st->full_sb = NULL;
    st->empty_sb = NULL;
    st->full_cb = NULL;
    st->empty_cb = NULL;
    return st;
}

void stack_t_free(stack_t * st)
{
    free(st);
}

void stack_delete (stack_t * st)
{
    list_free (st->multi);
    stack_t_free (st);
}

int stack_t_getCount(stack_t * st) {
    return st->count;
}

void stack_t_push(stack_t * st, int val) {
    if (st->count > 9 )
        puts ("Full stack");
    else
    {
        st->array[st->count] = val;
        st->count++;
    }
}

int stack_t_pop(stack_t * st) {
    if (st->count > 0) {
        int el = st->array[st->count - 1];
        st->count--;
        return el;
    } else puts ("Empty stack");
}

int stack_t_peek(stack_t * st) {
    if (st->count > 0) {
        int el = st->array[st->count - 1];
        return el;
    }
}

void stack_t_print (stack_t * st)
{
    printf ("Here is the stack number %i:\n", st->number);
    if (st->count == 0)
    puts ("Stack is empty");
    else
    {
        for (int i = 0; i < st->count; i++)
        printf ("\t\t'%i'\n", st->array[i]);
    }
}

stack_t * stack_t_make_stack (int count_to_fill, int number)
{
    stack_t * st1 = stack_t_new(number);
    stack_t_fill_random (st1, count_to_fill);
    return st1;
}


void stack_t_fill_random (stack_t * st, int count_to_fill)
{
       int k = st->count;
       for (int i = 0; i < count_to_fill; i++)
    {
        int b  = rand ()%200 - 100;
        if (b > 0 && st->count < 10)
            stack_t_push (st, b);
        else stack_t_pop(st);
            if (st->count == 10)
               st->full_cb(st->full_sb, st, 0, b);
    }
}

int stack_t_pop_val (stack_t * st)
{
    if (st->count > 0)
        stack_t_pop(st);
    else
        st->empty_cb(st->empty_sb, st, 1, NULL);
}

void stack_t_rand_choice (stack_t * st1, stack_t * st2)
{
    int b = rand ()%10 - 5;
    if (b >= 0)
        stack_t_fill_random(st1, 1);
    else stack_t_fill_random (st2, 1);
}

void stack_subscribe_full (stack_t * stack, void * listener, cb_fn cb)
{
    stack->full_sb = listener;
    stack->full_cb = cb;
}

void stack_subscribe_empty (stack_t * stack, void * listener, cb_fn cb)
{
    stack->empty_sb = listener;
    stack->empty_cb = cb;
}

void stack_subscribe_multi (stack_t * stack, void * listener, cb_fn cb)
{
    event_t * ev = (event_t*)malloc (sizeof(event_t));
    ev->receiver = listener;
    ev->callback = cb;
    list_push_back(stack->multi, ev);
}

void multi (event_t * ev, char message[70] , stack_t * st, int status, int value)
{
    if(ev->callback != NULL)
                {
                    cb_fn fn = (cb_fn)ev->callback;
                    sprintf(message, "%s", (char *)ev->receiver);
					fn(ev->receiver, st, status, value);
                }
}

void stack_Event (void * listener, stack_t * stack, enum status_en status, int value)
{
    int count;
    char message[70];
    stack_t * st;
    st = (stack_t *)listener;
    if (status == 0)
    {
        if(st->count < 10)
        {
            sprintf(message, "The stack number %i is FULL\n", stack->number);
            printf(message);
            stack_t_push(st, value);
        }
        else
        {

            for(int i = 0; i < list_getCount(st->multi); i++)
            {
                event_t * ev = list_getEl(st->multi, i);
                multi (ev, message, st, 2, 1);
            }
            for(int i = 0; i < list_getCount(stack->multi); i++)
            {
                event_t * ev = list_getEl(stack->multi, i);
                multi (ev, message, stack, 2, 1);
            }
        }
    }
    else if (status == 1)
    {
         if(st->count > 0)
        {
            sprintf(message, "The stack number %i is EMPTY\n", stack->number);
            printf(message);
            stack_t_pop (st);
        }
        else
        {
            for(int i = 0; i < list_getCount(st->multi); i++)
            {
                event_t * ev = list_getEl(st->multi, i);
                if(ev->callback != NULL)
                multi (ev, message, st, 2, 1);
            }
            for(int i = 0; i < list_getCount(stack->multi); i++)
            {
                event_t * ev = list_getEl(stack->multi, i);
                multi (ev, message, stack, 2, 1);
            }
        }
    }
    if(status == 2)
    {
        user_t * user = (user_t *)listener;
        sprintf(message, "User %s gets that it is the EVENT\n", user->users);
        printf(message);
    }
}
