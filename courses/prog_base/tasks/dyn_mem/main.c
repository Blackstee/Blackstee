#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char * text = (char *)malloc(sizeof(char) * 100);
    int * i = (int *)malloc(sizeof(int));
    int * numofop = (int *)malloc(sizeof(int));
    int * numofcl = (int *)malloc(sizeof(int));
    *i = 100;
    *numofop = 0;
    *numofcl = 0;
    puts("Please, enter the string\n");
    fgets(text, *i, stdin);
    for(*i = 0; *i < strlen(text) - 1; (*i)++){
        if(text[*i] == '(')
        (*numofop)++;
        if(text[*i]== ')')
        (*numofcl)++;
        }
    if (*numofop == *numofcl)
     puts("1");
     else puts ("0");
    free(text);
    free(i);
    free(numofop);
    free(numofcl);
    return EXIT_SUCCESS;
}
