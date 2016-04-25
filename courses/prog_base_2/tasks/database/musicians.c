#include <stdlib.h>
#include <stdio.h>

#include "musicians.h"

void musician_print(musician_t * mus)
{
    puts ("------------------------------");
    puts ("The musician:");
    puts ("------------------------------");
    printf("Name: \t\t%s\nSurname: \t%s\nStyle: \t\t%s\nRating: \t%f\nInstruments: \t%i\nSalary: \t%i\n",
        mus->name, mus->surname, mus->style, mus->rating, mus->instruments, mus->salary);
}

void musician_printList(musician_t * array, int length)
{
    puts ("==============================");
    for (int i = 0; i < length; i++)
        musician_print(&array[i]);
}
