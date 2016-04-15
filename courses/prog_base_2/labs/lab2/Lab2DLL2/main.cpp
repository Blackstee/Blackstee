#include "main.h"
#include <stdio.h>

int compare(list_t * list1) {
    int i;
    int count = 0;
    for (i = 0; i < list_t_get_size(list1); i++)
    {
        if (list_t_get_elem(list1, i) == ' ')
            count++;
    }
    if (count > 5)
        return 1;
    return 0;
}

void reaction(list_t * list1) {
    int react = compare (list1);
    int k;
    if (react == 1)
    {
        for (k = 0; k < list_t_get_size(list1); k++)
        {
            if (list_t_get_elem(list1, k) == ' ')
                list_t_change_elem_by_index(list1, '_', k);
        }
    }
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
