#include <stdlib.h>
#include <stdio.h>

#include "cJSON.h"
#include "info.h"
//#include "musicians.h"

static cJSON * info_serializeJSON(const info_t *self)
{
    cJSON * jInfo = cJSON_CreateObject();
    cJSON_AddItemToObject(jInfo, "student", cJSON_CreateString (self->student));
    cJSON_AddItemToObject(jInfo, "group", cJSON_CreateString(self->group));
    cJSON_AddItemToObject(jInfo, "variant", cJSON_CreateNumber(self->variant));
	return jInfo;
}

const char *
info_toJSON(const info_t * self)
{
    cJSON * jInfo = info_serializeJSON(self);
	const char * jsonString = cJSON_Print(jInfo);
	cJSON_Delete(jInfo);
    return jsonString;
}
