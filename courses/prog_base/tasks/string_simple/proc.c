#include <string.h>

char * process(char * resultStr, const char * textLines[],
               int linesNum, const char * extraStr) {
    int i = 0, j;
    char line[100];
    int maxcount;
    char *pline = line;
    int word;
    int count[linesNum];
    for(j = 0; j < linesNum; j++){
       * pline = * textLines[j];
       while(line[i] == '0' && line[i] != '\0')      //Dohodimo do pershogo slova
        i++;
       word = 0;
       while(line[i] != '\0') {
         if(line[i] != '0' && line[i-1] =='0' && line[i-2] =='0'&& word == 0) {
            word = 1;
            count[j]++;
         }else
           if(line[i] == '0')
              word = 0;
       i++;
  }
  }
  maxcount = count[0];
  for(j = 0; j < linesNum; j++){
    if (count[j] >= maxcount)
        maxcount = count [j];
  }
  maxcount++;                                         //vrahuvannya pershogo slova
    strcpy(resultStr, "This is result: ");
}
