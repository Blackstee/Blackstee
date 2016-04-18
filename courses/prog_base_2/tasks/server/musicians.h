#ifndef MUSICIANS_H_INCLUDED
#define MUSICIANS_H_INCLUDED

typedef struct {
	char * style;
	char * role;
} band_t;

typedef struct {
    int     id;
	char * 	name;
	char * 	surname;
	char *  birthdate;
	int 	year;
	double	rating;
	band_t band;
} musician_t;

typedef struct error_s
{
    int status;
    char * error;
}error_t;

//typedef struct error_s * error_t;

musician_t
musician_empty(void);

const char *
musician_toJSON(const musician_t * self);

const char *
musician_listToJSON(const musician_t * const musicianList, int musicianListSize);

const char *
error_toJSON(const error_t * self);

#endif // MUSICIANS_H_INCLUDED
