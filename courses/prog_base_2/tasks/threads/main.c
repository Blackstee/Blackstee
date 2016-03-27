#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "thread.h"
#include "mutex.h"
#include "SymbolSetter.h"
#include "DigitReader.h"



int main(void) {
    srand(time(NULL));
    strings_t sharedstring;
    int x = 0;
    sharedstring.symbol = &x;
    strcpy (sharedstring.string, "HEY WOOOORLD 123 DFGHJK");
    sharedstring.mu = mutex_new();
    SymbolSetter_t *setternumone = SymbolSetter_new (&sharedstring);
    SymbolSetter_t *setternumtwo = SymbolSetter_new (&sharedstring);
    DigitReader_t *readernumone = DigitReader_new (&sharedstring);
    DigitReader_t *readernumtwo  = DigitReader_new (&sharedstring);
    DigitReader_t *readernumthree = DigitReader_new (&sharedstring);
    DigitReader_join (readernumone);
    DigitReader_join (readernumtwo);
    DigitReader_join (readernumthree);
    SymbolSetter_free (setternumone);
    SymbolSetter_free (setternumtwo);
    DigitReader_free (readernumone);
    DigitReader_free (readernumtwo);
    DigitReader_free (readernumthree);
    mutex_free(sharedstring.mu);
    return 0;
}
