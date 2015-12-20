#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *morse_encode(char *signal, const char *message,int unit_len, int pad_len){
    strcpy (signal, "");
    int i;
    for (i = 0; i < pad_len; i++)
        strcat (signal, "0");
    char prot [300];
    prot [0] = 0;
    char *ing = &prot;
    for (i = 0; i < strlen (message); i++){
        switch (message[i]){
            case 'A': strcat (prot, ".-"); break;
            case 'B': strcat (prot, "-..."); break;
            case 'C': strcat (prot, "-.-."); break;
            case 'D': strcat (prot, "-.."); break;
            case 'E': strcat (prot, "."); break;
            case 'F': strcat (prot, "..-."); break;
            case 'G': strcat (prot, "--."); break;
            case 'H': strcat (prot, "...."); break;
            case 'I': strcat (prot, ".."); break;
            case 'J': strcat (prot, ".---"); break;
            case 'K': strcat (prot, "-.-"); break;
            case 'L': strcat (prot, ".-.."); break;
            case 'M': strcat (prot, "--"); break;
            case 'N': strcat (prot, "-."); break;
            case 'O': strcat (prot, "---"); break;
            case 'P': strcat (prot, ".--."); break;
            case 'Q': strcat (prot, "--.-"); break;
            case 'R': strcat (prot, ".-."); break;
            case 'S': strcat (prot, "..."); break;
            case 'T': strcat (prot, "-"); break;
            case 'U': strcat (prot, "..-"); break;
            case 'V': strcat (prot, "...-"); break;
            case 'W': strcat (prot, ".--"); break;
            case 'X': strcat (prot, "-..-"); break;
            case 'Y': strcat (prot, "-.--"); break;
            case 'Z': strcat (prot, "--.."); break;
            case '0': strcat (prot, "-----"); break;
            case '1': strcat (prot, ".----"); break;
            case '2': strcat (prot, "..---"); break;
            case '3': strcat (prot, "...--"); break;
            case '4': strcat (prot, "....-"); break;
            case '5': strcat (prot, "....."); break;
            case '6': strcat (prot, "-...."); break;
            case '7': strcat (prot, "--..."); break;
            case '8': strcat (prot, "---.."); break;
            case '9': strcat (prot, "-----"); break;
            case ' ': strcat (prot, "&"); break;
        }
        if (message[i] != ' ' && message [i+1] != '\0' && message [i+1] != ' ') strcat (prot, " ");
    }
    int k;
    for (i = 0; i < strlen(prot); i++){
        switch (prot[i])
        {
        case '.': for (k = 0; k < unit_len; k++)
                  strcat (signal, "1");
            break;
        case '-': for (k = 0; k < 3 * unit_len; k++)
                  strcat (signal, "1");
            break;
        case ' ': for (k = 0; k < 3 * unit_len; k++)
                  strcat (signal, "0");
            break;
        case '&': for (k = 0; k < 7 * unit_len; k++)
                  strcat (signal, "0");
            break;
        }
        if (prot[i + 1] != ' ' && prot[i] != ' ' && prot[i + 1] != '&' && prot [i] != '&' && prot[i] !='\0' && prot[i + 1] != '\0')
        for (k = 0; k < unit_len; k++)
            strcat (signal, "0");
    }
    for (i = 0; i < pad_len; i++)
        strcat (signal, "0");
    return signal;
}

/*int main(void){
    int unit_len, pad_len;
    char string[1000];
    puts("Please, enter the string\n");
    gets (string);
    puts ("The unit length:");
    scanf ("%i", &unit_len);
    puts ("The pad length:");
    scanf ("%i", &pad_len);
    char str[50];
    char *message = &string;
    char *signal = str;
    puts (morse_encode(signal, message, unit_len, pad_len));
    return EXIT_SUCCESS;
}*/
