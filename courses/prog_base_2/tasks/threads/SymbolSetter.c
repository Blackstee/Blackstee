#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "thread.h"
#include "mutex.h"
#include "SymbolSetter.h"
#include "DigitReader.h"



struct SymbolSetter_s
{
    thread_t *thread;
};

 void *SymbolSetter (void *args)
{
    strings_t *curstr = (strings_t *)args;
    int i = 0;
    while (1)
        {
        mutex_lock(curstr->mu);
        curstr->symbol = &curstr->string[i];
        i++;
        if (i == 200)//beginning again - cycle
                i = 0;
        mutex_unlock(curstr->mu);
    }
    return NULL;
}

SymbolSetter_t *SymbolSetter_new (strings_t *sharedstring)
{
    SymbolSetter_t *Setter = malloc(sizeof(SymbolSetter_t));
    Setter->thread = thread_create_args(SymbolSetter, sharedstring);
    return Setter;
}

void SymbolSetter_free (SymbolSetter_t *SymbolSetter)
{
    thread_free(SymbolSetter->thread);
    free (SymbolSetter);
}
