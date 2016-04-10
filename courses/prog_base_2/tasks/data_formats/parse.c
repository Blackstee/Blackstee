#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "parse.h"
#include "musicians.h"

void enter_to_pointers (musicians_t * mus, xmlNode * xMus)
{
    char * name;
    char * surname;
    char * birthdate;
    char * year;
    char * rating;
    char * style;
    char * role;
    xmlNode * xCur;
    for(xCur = xMus->children; NULL != xCur; xCur = xCur->next)
    {
        if(XML_ELEMENT_NODE == xCur->type)
        {
            if(strcmp(xCur->name, "name") == 0)
                name = xmlNodeGetContent(xCur);
            if(strcmp(xCur->name, "surname") == 0)
                surname = xmlNodeGetContent(xCur);
            if(strcmp(xCur->name, "birthdate") == 0)
                birthdate = xmlNodeGetContent(xCur);
            if(strcmp(xCur->name, "year") == 0)
                year = xmlNodeGetContent(xCur);
            if(strcmp(xCur->name, "rating") == 0)
                rating = xmlNodeGetContent(xCur);
            if(strcmp(xCur->name, "band") == 0)
            {
                style = xmlGetProp(xCur, "style");
                role = xmlNodeGetContent(xCur->children->next);
            }
        }
    }
    musicians_t_enter (mus, name, surname, birthdate, atoi(year), atof(rating), style, role);
}


void parse (musicians_t ** mus, const char * title)
{
    char line[100];
    char text[10000] = "";
    FILE * fr = fopen(title, "r");

    while(fgets(line, 100, fr))
    {
        strcat(text, line);
    }

    xmlDoc * xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc)
    {
        printf("Error parsing xml from memory");
        return;
    }
    xmlNode * xMusicians;
    xMusicians = xmlDocGetRootElement(xDoc);
    xmlNode * xMus;
    int i;
    for (i = 0, xMus = xMusicians->children; NULL != xMus; xMus = xMus->next)
    {
        if (XML_ELEMENT_NODE == xMus->type){
            enter_to_pointers (mus[i], xMus);
            i++;
        }
    }
}
