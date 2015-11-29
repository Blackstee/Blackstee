#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void fprocess(const char * pread, const char * pwrite)
{
    int a, b, c, i, na, nb, k;
    char str [5], str1[100];
    FILE * fp1;
    FILE * fp2;
    fp1 = fopen("pread.txt", "r");
    fp2 = fopen("pwrite.txt", "w");
    if (fp1 == NULL) {
        puts("Error!");
        return EXIT_FAILURE;
    }
    for (i = 0; i < 19 ; i++){
       fgets(str1, 100, fp1);
    }
    na = 0;
    nb = 0;
    k = 0;
    for (i = 0; i < 50; i++){
        k++;
        if (str1[i] == ' ' && na != 0) {
          nb = k;
          break;
          }
        if (str1[i] == ' ' && na == 0)
          na = k;
    }
    a = atoi (str1);
    b = atoi (str1 + na);
    c = atoi (str1 + nb);
    if (((a + b) > c && (a + c) > b && (b + c) > a) && (a > 0 && b >0 && c > 0))
        fprintf(fp2, "true");
        else
            fprintf(fp2, "false");
    fclose(fp1);
    fclose(fp2);
    return 0;
}
