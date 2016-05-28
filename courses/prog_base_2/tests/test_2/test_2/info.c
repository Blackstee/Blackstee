#include <stdlib.h>
#include <stdio.h>

#include "cJSON.h"
//#include "musicians.h"

info_t
info_new (void)
{
    info_t st = {
        .student = "Nastya Shapovalova",
        .group = "KP-51",
        .variant = 15;
    };
    return st;
}

const char *
info_toJSON()
{
    info_t inf =
    cJSON * jInfo = cJSON_CreateObject();
    cJSON_AddItemToObject(jInfo, "student", cJSON_CreateString(name));
    cJSON_AddItemToObject(jInfo, "group", cJSON_CreateString(group));
    cJSON_AddItemToObject(jInfo, "variant", cJSON_CreateNumber(var));
	const char * jsonString = cJSON_Print(jInfo);
	cJSON_Delete(jInfo);
    return jsonString;
}
