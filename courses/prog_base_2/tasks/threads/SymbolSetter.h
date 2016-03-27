#ifndef SYMBOLSETTER_H_INCLUDED
#define SYMBOLSETTER_H_INCLUDED

#include "thread.h"
#include "mutex.h"
#include "SymbolSetter.h"
#include "DigitReader.h"


typedef struct SymbolSetter_s SymbolSetter_t;

typedef struct strings_s {
    char string [200];
    char *symbol;
    mutex_t *mu;
} strings_t;

SymbolSetter_t *SymbolSetter_new (strings_t *sharedstring);
void * SymbolSetter(void *args);
void SymbolSetter_free (SymbolSetter_t *SymbolSetter);

#endif // SYMBOLSETTER_H_INCLUDED
