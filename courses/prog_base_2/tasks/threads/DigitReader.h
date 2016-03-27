#ifndef DIGITREADER_H_INCLUDED
#define DIGITREADER_H_INCLUDED

#include "thread.h"
#include "mutex.h"
#include "SymbolSetter.h"
#include "DigitReader.h"


typedef struct DigitReader_s DigitReader_t;
void *DigitReader (void *args);
void DigitReader_join (DigitReader_t *DigitReader);
void DigitReader_free (DigitReader_t *DigitReader);

#endif // DIGITREADER_H_INCLUDED
