#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main(void)
{
    text_t * text = text_t_new();
    sentence_t * sentence = sentence_t_new();
    file_read ("input.txt", text, sentence);
    fprint(text);
    text_free(text);
    return 0;
}
