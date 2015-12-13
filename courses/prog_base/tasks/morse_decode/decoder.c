#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *morse_decode(char *message, const char *signal){
    char result[100];
    message = &result;
    result [0] = 0;
    int i, h, unit = 100, count = 0;
    for (i = 0; i < strlen(signal)+ 1; i++){
       if (signal[i] == '1' ) count++;
       if (signal[i] == '0'|| signal[i] == '\0'){
            if (count < unit && count > 0)
            unit = count;
            count = 0;
    }
    }
    for (i = 0; i < strlen(signal); i++){
    if (signal[i] == '1'){
        h = i;
        break;
    }
    }
    char text [100];
    text [0] = " ";
    int fornull = 0, forone = 0, znak, k = 0;
    for (i = h; i < strlen(signal) + 1; i++){
        if ((signal[i] == '1' && fornull != 0) || signal[i] == '\0'){
            forone ++;
            znak = fornull/unit;
            switch (znak){
            case 1: break;
            case 3: strcat(text, " ");
            break;
            case 7: strcat(text,"&");
            break;
            }
            fornull = 0;
        } else if (signal[i] == '1') forone++;
        if ((signal[i] == '0' && forone != 0) || signal[i] == '\0' ){
            fornull++;
            znak = forone/unit;
            switch (znak) {
            case 1: strcat(text, ".");
            break;
            case 3: strcat(text, "-");
            break;
            }
            forone = 0;
        } else if (signal[i] == '0') fornull++;
    }
    char prom [100];
    for (i = 0; i < strlen(text) + 1; i++){
        if (text[i] == '.') strcat (prom, ".");
        if (text[i] == '-') strcat (prom, "-");
        if (text[i] == ' ' || text[i] == '&' || text[i] == '\0') {
            if (strcmp (prom, ".-")== 0) strcat (result, "A"); else
            if (strcmp (prom, "-...") == 0) strcat (result, "B"); else
            if (strcmp (prom, "-.-.") == 0) strcat (result, "C"); else
            if (strcmp (prom, "-..") == 0) strcat (result, "D"); else
            if (strcmp (prom, ".") == 0) strcat (result, "E"); else
            if (strcmp (prom, "..-.") == 0) strcat (result, "F"); else
            if (strcmp (prom, "--.") == 0) strcat (result, "G"); else
            if (strcmp (prom, "....") == 0) strcat (result, "H"); else
            if (strcmp (prom, "..") == 0) strcat (result, "I"); else
            if (strcmp (prom, ".---") == 0) strcat (result, "J"); else
            if (strcmp (prom, "-.-") == 0) strcat (result, "K"); else
            if (strcmp (prom, ".-..") == 0) strcat (result, "L"); else
            if (strcmp (prom, "--") == 0) strcat (result, "M"); else
            if (strcmp (prom, "-.") == 0) strcat (result, "N"); else
            if (strcmp (prom, "---") == 0) strcat (result, "O"); else
            if (strcmp (prom, ".--.") == 0) strcat (result, "P"); else
            if (strcmp (prom, "--.-") == 0) strcat (result, "Q"); else
            if (strcmp (prom, ".-.") == 0) strcat (result, "R"); else
            if (strcmp (prom, "...") == 0) strcat (result, "S"); else
            if (strcmp (prom, "-") == 0) strcat (result, "T"); else
            if (strcmp (prom, "..-") == 0) strcat (result, "U"); else
            if (strcmp (prom, "...-") == 0) strcat (result, "V"); else
            if (strcmp (prom, ".--") == 0) strcat (result, "W"); else
            if (strcmp (prom, "-..-") == 0) strcat (result, "X"); else
            if (strcmp (prom, "-.--") == 0) strcat (result, "Y"); else
            if (strcmp (prom, "--..") == 0) strcat (result, "Z"); else
            if (strcmp (prom, "-----") == 0) strcat (result, "0"); else
            if (strcmp (prom, ".----") == 0) strcat (result, "1"); else
            if (strcmp (prom, "..---") == 0) strcat (result, "2"); else
            if (strcmp (prom, "...--") == 0) strcat (result, "3"); else
            if (strcmp (prom, "....-") == 0) strcat (result, "4"); else
            if (strcmp (prom, ".....") == 0) strcat (result, "5"); else
            if (strcmp (prom, "-....") == 0) strcat (result, "6"); else
            if (strcmp (prom, "--...") == 0) strcat (result, "7"); else
            if (strcmp (prom, "---..") == 0) strcat (result, "8"); else
            if (strcmp (prom, "----.") == 0) strcat (result, "9");
         prom [0] = 0;
    }
        if (text[i] == '&') {strcat (result, " ");
        prom[0] = 0;}
    }
    return message;
}

/*int main(void){
    char string[1000];
    puts("Please, enter the string\n");
    gets (string);
    char *signal = &string;
    char *message;
    puts (morse_decode(message, signal));
    return EXIT_SUCCESS;
}*/
