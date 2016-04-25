#ifndef MUSICIANS_H_INCLUDED
#define MUSICIANS_H_INCLUDED

typedef struct musician_s {
    int number;
    char name[200];
    char surname[200];
    char style [50];
    double rating;
    int instruments;
    int salary;
} musician_t;

void musician_print(musician_t * mus) ;
void musician_printList(musician_t * array, int length) ;

#endif // MUSICIANS_H_INCLUDED
