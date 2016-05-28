#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

typedef struct info_t
{
	char * 	student;
	char * 	group;
	int 	variant;
} info_t;

//================info=====================
const char *
info_toJSON(const info_t * self);





#endif // INFO_H_INCLUDED
