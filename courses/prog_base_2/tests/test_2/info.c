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

static cJSON * cons_serializeJSON(const cons_t *self)
{
    cJSON * jCons = cJSON_CreateObject();
    cJSON_AddItemToObject(jCons, "Vowels", cJSON_CreateNumber(self->vowels));
    cJSON_AddItemToObject(jCons, "Consonants", cJSON_CreateNumber(self->consonants));
	return jCons;
}

const char *
cons_toJSON(const cons_t * self)
{
    cJSON * jCons = cons_serializeJSON(self);
	const char * jsonString = cJSON_Print(jCons);
	cJSON_Delete(jCons);
    return jsonString;
}

static cJSON * _error_serializeJSON(const error_t * self) {
    cJSON * jError = cJSON_CreateObject();
    cJSON_AddItemToObject(jError, "Number of requests", cJSON_CreateNumber(self->status));
	cJSON_AddItemToObject(jError, "Current existence of problem", cJSON_CreateString(self->error));
	return jError;
}

const char *
error_toJSON(const error_t * self) {
    cJSON * jError = _error_serializeJSON(self);
	const char * jsonString = cJSON_Print(jError);
	cJSON_Delete(jError);
    return jsonString;
}
