#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int numberofpunct (char *ptr, int number){
    if (*ptr == '\0')
        return number;
    else if (ispunct(*ptr))
        number++;
    numberofpunct (ptr + 1, number);
}

int main(void){
    char string[100];
    puts("Please, enter the string\n");
    gets (string);
    char *ptr = &string;
    int number = 0;
    number = numberofpunct (ptr, number);
    printf ("%i", number);
    return EXIT_SUCCESS;
}
