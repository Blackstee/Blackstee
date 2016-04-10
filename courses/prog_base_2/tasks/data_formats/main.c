#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "parse.h"
#include "musicians.h"

int main ()
{
    musicians_t * music [3];
    int i;
    for (i = 0; i < 3; i++)
        music [i] = musicians_new();
    for (i = 0; i <3; i++)
    parse(music, "musicians.xml");
    for(int i = 0; i < 3; i++)
        musicians_t_print(music[i]);
    for(int i = 0; i < 3; i++)
        musicians_t_free(music[i]);
    return 0;
}
