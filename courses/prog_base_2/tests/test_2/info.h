#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

typedef struct info_t
{
	char * 	student;
	char * 	group;
	int 	variant;
} info_t;

typedef struct cons_s
{
    int vowels;
    int consonants;
} cons_t;

typedef struct error_s
{
    int status;
    char * error;
}error_t;

//================info=====================
const char *
info_toJSON(const info_t * self);


const char *
cons_toJSON(const cons_t * self);

const char *
error_toJSON(const error_t * self);

#endif // INFO_H_INCLUDED
