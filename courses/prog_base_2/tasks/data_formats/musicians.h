#ifndef MUSICIANS_H_INCLUDED
#define MUSICIANS_H_INCLUDED

typedef struct Musicians_s * musicians_t;

musicians_t * musicians_new (void);

musicians_t_free (musicians_t * mus);

musicians_t_enter (musicians_t  mus, char * name, char * surname, char * birthdate, int year, double rating, char * style, char * role);
musicians_t_print (musicians_t mus);


#endif // MUSICIANS_H_INCLUDED
