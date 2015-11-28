#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main()
{
    /*char * fileName = "in.txt";
    char * mode = "r";
    FILE * fp;
    char t1, t2;
    int i;


    fp = fopen(fileName, mode);
    if (NULL == fp) {
        puts("Error!");
        return EXIT_FAILURE;
    }

    t1 = fgetc(fp);
    while (EOF != t1) {
        printf("%c", t1);
        t1 = fgetc(fp);
    }

    for (i = sizeof (t1); i > 0; i--)
       printf ("%d", sizeof (t1));

*/
    char str1 [100], str2 [100];
    int i;

    FILE * fp;

    fp = fopen("in.txt", "r");
    if (fp == NULL) {
        puts("Error!");
        return EXIT_FAILURE;
    }

    puts("I read this!");
    fgets(str1, 100, fp);
    fclose(fp);
    for (i = 0; i < strlen (str1); i++)
    {
        if (str1[i] == '\0')
        return 0;
        if (str1[i] != ' ')
          str2[i] = str1 [i];
    }
    for (i = 0; i < strlen (str1); i++)
        str2[strlen(str1)- i- 1] = str1 [i];
    fp = fopen("out.txt", "w");
    if (fp == NULL) {
        puts("Error!");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%s", str2);
    puts("I wrote this!");

    fclose(fp);
    return 0;

}
