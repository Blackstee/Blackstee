#include <stdlib.h>
#include <stdio.h>

#include "cJSON.h"
#include "musicians.h"

static cJSON * _musician_serializeJSON(const musician_t * self) {
    cJSON * jMusician = cJSON_CreateObject();

    cJSON_AddItemToObject(jMusician, "id", cJSON_CreateNumber(self->id));
	cJSON_AddItemToObject(jMusician, "name", cJSON_CreateString(self->name));
	cJSON_AddItemToObject(jMusician, "surname", cJSON_CreateString(self->surname));
	cJSON_AddItemToObject(jMusician, "birthdate", cJSON_CreateString(self->birthdate));
    cJSON_AddItemToObject(jMusician, "year", cJSON_CreateNumber(self->year));
	cJSON_AddItemToObject(jMusician, "rating", cJSON_CreateNumber(self->rating));

	cJSON * jBand = cJSON_CreateObject();
	cJSON_AddItemToObject(jBand, "style", cJSON_CreateString(self->band.style));
	cJSON_AddItemToObject(jBand, "role", cJSON_CreateString(self->band.role));
	cJSON_AddItemToObject(jMusician, "band", jBand);

	return jMusician;
}

static cJSON * _error_serializeJSON(const error_t * self) {
    cJSON * jError = cJSON_CreateObject();
    cJSON_AddItemToObject(jError, "status", cJSON_CreateNumber(self->status));
	cJSON_AddItemToObject(jError, "error", cJSON_CreateString(self->error));
	return jError;
}
musician_t
musician_empty(void) {
    musician_t st = {
        .id = 0,
        .name = "",
        .surname = "",
        .birthdate = "",
        .year = 0,
        .rating = 0.0,
        .band = {
            .style = "",
            .role = "",
        }
    };
    return st;
}

const char *
musician_toJSON(const musician_t * self) {
    cJSON * jMusician = _musician_serializeJSON(self);
	const char * jsonString = cJSON_Print(jMusician);
	cJSON_Delete(jMusician);
    return jsonString;
}

const char *
error_toJSON(const error_t * self) {
    cJSON * jError = _error_serializeJSON(self);
	const char * jsonString = cJSON_Print(jError);
	cJSON_Delete(jError);
    return jsonString;
}
const char *
musician_listToJSON(const musician_t * const musicianList, int musicianListSize) {
    cJSON * jArr = cJSON_CreateArray();
    for (int i = 0; i < musicianListSize; i++) {
        cJSON * jMusician = _musician_serializeJSON(musicianList + i);
        cJSON_AddItemToArray(jArr, jMusician);
    }
    const char * jsonString = cJSON_Print(jArr);
	cJSON_Delete(jArr);
    return jsonString;
}
