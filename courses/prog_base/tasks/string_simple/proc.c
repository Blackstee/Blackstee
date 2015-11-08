#include <string.h>
#include <stdlib.h>
#include <stdio.h>



char * process(char * resultStr, const char * textLines[],
               int linesNum, const char * extraStr) {
    int i, j, a, s, sum = 0, l = 0;
    char str[100];
    str[0] = 0;
    for(i = 0; i < linesNum; i++)
    {
       s = 0;
       a = 0;
       str[0] = 0;
       for(j = 0; j < strlen(textLines[i]); j++)
       {
           if(*(textLines[i] + j) == '0')
           {

               if (a == 1)
               {
                  a = 0;
                  s = s + 1;
               } else
                   a = 1;
           }
       }
       s++;
       if (s >= sum)
       {
           sum = s;
           l = i;
       }
    }
    sprintf(resultStr, "%i ", sum);
    strcat(resultStr, textLines[l]);
    return resultStr;
}
