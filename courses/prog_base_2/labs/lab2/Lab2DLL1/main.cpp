#include "main.h"
#include <stdio.h>

int compare(list_t * list1) {
    char element;
    int vowels = 0;
    int consonants = 0;
    for (int i = 0; i < list_t_get_size(list1); i++)
    {
        element = list_t_get_elem(list1, i);
        if (element>= 'A' && element <= 'Z')
            element = element + 'a' - 'A';
        if (element >= 'a' && element <= 'z')
            if (element == 'a' || element == 'e' || element == 'i' || element == 'o' || element == 'u')
                vowels++;
                else consonants++;
    }
    if (vowels > consonants)
        return 1;
        else
           return 0;
}

void reaction(list_t * list1) {
      int react = compare (list1);
      if (react == 1)
        printf ("Vowels win!");
      else printf ("Consonants win!");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
