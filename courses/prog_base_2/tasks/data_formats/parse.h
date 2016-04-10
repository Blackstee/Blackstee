#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED
#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct Musicians_s * musicians_t;

void enter_to_pointers (musicians_t * mus, xmlNode * xMus);
void parse (musicians_t ** mus, const char * title);

#endif // PARSE_H_INCLUDED
