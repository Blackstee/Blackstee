#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

struct Musician_s
{
    char * style;
    char * role;
};

struct Musicians_s
{
    char * name;
    char * surname;
    char * birthdate;
    int year;
    double rating;
    struct Musician_s musician_t;
};

musicians_t * musicians_new()
{
    musicians_t * mus = malloc(sizeof(struct Musicians_s));
    return mus;
}

void musicians_t_free(musicians_t * mus)
{
    free(mus);
}

void musicians_t_enter (musicians_t  mus, char * name, char * surname, char * birthdate, int year, double rating, char * style, char * role)
{
    mus->name = name;
    mus->surname = surname;
    mus->birthdate = birthdate;
    mus->year = year;
    mus->rating = rating;
    mus->musician_t.style = style;
    mus->musician_t.role = role;
}

void musicians_t_print(musicians_t mus)
{
    puts ("--------------------------");
    puts ("Information about musician:");
    printf("|Name: \t\t%s\n|Surname: \t%s\n|Birthdate: \t%s\n|Year: \t\t%d\n|Rating: \t%f\n\t|About band\n\t||Style: \t%s\n\t||Role: \t%s\n", mus->name, mus->surname, mus->birthdate, mus->year, mus->rating, mus->musician_t.style, mus->musician_t.role);
}
