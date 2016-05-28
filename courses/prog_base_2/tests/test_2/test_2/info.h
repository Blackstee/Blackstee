#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

typedef struct {
	char * 	student;
	char * 	group;
	int 	variant;
} info_t;

//================info=====================
const char *
info_toJSON();





#endif // INFO_H_INCLUDED
