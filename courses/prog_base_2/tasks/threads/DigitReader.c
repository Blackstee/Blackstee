#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "thread.h"
#include "mutex.h"
#include "SymbolSetter.h"
#include "DigitReader.h"


struct DigitReader_s
{
    thread_t *thread;
};

void *DigitReader (void *args)
{
    strings_t *curstr = (strings_t *)args;
    while (1)
        {
        mutex_lock(curstr->mu);
        if(isdigit(curstr->symbol[0]) == 1)
            printf("%c", *(curstr->symbol));
        mutex_unlock(curstr->mu);
        Sleep(1);
        }
    return NULL;
}

DigitReader_t *DigitReader_new (strings_t *sharedstring)
{
    DigitReader_t * Reader = malloc(sizeof(DigitReader_t));
    Reader->thread = thread_create_args(DigitReader, sharedstring);
    return Reader;
}

void DigitReader_join (DigitReader_t *DigitReader)
{
    thread_join(DigitReader->thread);
}

void DigitReader_free (DigitReader_t *DigitReader)
{
    thread_free(DigitReader->thread);
    free (DigitReader);
}
