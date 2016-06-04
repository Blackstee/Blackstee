#include <stdlib.h>
#include <stdio.h>

#include "cJSON.h"
#include "Resource.h"
#include "list.h"


//==========================musician====================================

musician_t * musician_t_new (void)
{
    musician_t * self = malloc (sizeof( musician_t));
    self->id = -999;
    self->name = "Name";
    self->surname = "Surname";
    self->birthdate = "01-01-1900";
    self->year = 1900;
    self->rating = 0.0;
    memset(&(self->band), 0, sizeof (self->band));
    self->band.role = "Role";
    self->band.style = "Style";
    return self;
}

struct mus_arr_s
{
    list_t * musicians;
};

void musician_t_free (musician_t * self)
{
    free (self);
}

void musician_t_add_info (musician_t * self, int id, char * name, char * surname, char * birthdate, int year, float rating, char * role, char * style)
{
    self->id = id;
    self->name = name;
    self->surname = surname;
    self->birthdate = birthdate;
    self->year = year;
    self->rating = rating;
    self->band.role = role;
    self->band.style = style;
}

musician_t * mus_delete (const mus_arr_t * self, int ID)
{
    musician_t * deleted = list_remove (self->musicians, ID);
    return deleted;
}

musician_t * mus_get (mus_arr_t * self, int ID)
{
    for (int i = 0; i < mus_arr_t_get_size(self); i++)
    {
		musician_t * gotten = list_get (self->musicians, i);
        if (gotten->id == ID)
            return gotten;
	}
	return NULL;
}


//===========================list of musicians============================

mus_arr_t * mus_arr_t_new (void)
{
    mus_arr_t * self = malloc (sizeof (struct mus_arr_s));
    self -> musicians = list_new();
    return self;
}

void mus_arr_t_free (mus_arr_t * self)
{
    list_free (self -> musicians);
    free(self);
}

int mus_arr_t_get_size (mus_arr_t * self)
{
    return list_getSize(self->musicians);
}

void mus_arr_t_add_back (mus_arr_t * mus_arr, const musician_t * musician)
{
    list_push_back(mus_arr->musicians, musician);
}

void mus_arr_t_add_by_index(mus_arr_t * mus_arr, const musician_t * musician, int index)
{
	list_insert(mus_arr->musicians, index, musician);
}

//===========================================errors JSON===================
static cJSON * _error_serializeJSON(const error_t * self)
{
    cJSON * jError = cJSON_CreateObject();
    cJSON_AddItemToObject(jError, "Number of requests", cJSON_CreateNumber(self->status));
	cJSON_AddItemToObject(jError, "Current existence of problem", cJSON_CreateString(self->error));
	return jError;
}

const char *
error_toJSON(const error_t * self)
{
    cJSON * jError = _error_serializeJSON(self);
	const char * jsonString = cJSON_Print(jError);
	cJSON_Delete(jError);
    return jsonString;
}

//=======================================ID==================================
int mus_arr_t_get_free_id (mus_arr_t * self)
{
    int size = mus_arr_t_get_size(self);
    if (size == 0) {
		return 0;
	}
	for (int i = 0; i <= size; i++)
    {
		if (i == size)
			return i;
		else {
			musician_t * one = list_get(self->musicians, i);
			if (one->id != i)
				return i;
		}
	}
}

//=========================================musicians JSON===================
static cJSON * _musician_serializeJSON(const musician_t * self)
{
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

const char * musician_toJSON(const musician_t * self)
{
    cJSON * jMusician = _musician_serializeJSON(self);
	const char * jsonString = cJSON_Print(jMusician);
	cJSON_Delete(jMusician);
    return jsonString;
}

const char * musician_listToJSON(const mus_arr_t * mus_arr, int musicianListSize)
{
    cJSON * jArr = cJSON_CreateArray();
    for (int i = 0; i < musicianListSize; i++) {
        musician_t * cur = list_get (mus_arr->musicians, i);
        cJSON * jMusician = _musician_serializeJSON(cur);
        cJSON_AddItemToArray(jArr, jMusician);
    }
    const char * jsonString = cJSON_Print(jArr);
	cJSON_Delete(jArr);
    return jsonString;
}

//========================================musicians HTML====================

char * musician_listToHTML (const mus_arr_t * self)
{
	char * buff = calloc(10000, sizeof(char));
	char music[1000];
	char adres[100];
sprintf(buff,
		"<html><head><title>Musicians</title></head><body><h1 align = \"center\">Musicians </h1><table border=\"2\" align = \"center\">"
		"<tr><td align = \"center\"><i><strong>Link</strong></i></td>"
		"<td align = \"center\"><i><strong>Name</strong></i></td>"
		"<td align = \"center\"><i><strong>Surname</strong></i></td></tr>");
	for (int i = 0; i < mus_arr_t_get_size(self); i++)
    {
		musician_t * cur = list_get(self->musicians, i);
		sprintf(adres,
			"<a href=\"/musicians/%d\">Link</a>", cur->id);
		sprintf(music,
			"<tr><td>%s</td>"
			"<td>%s</td>"
			"<td>%s</td></tr>",
			adres, cur->name, cur->surname);
		strcat(buff, music);
	}
	strcat(buff, "</table></body>");
	return buff;
}

char * musician_toHTML (const musician_t * self)
{
	char * buff = calloc(10000, sizeof(char));
	sprintf(buff,
		"<html><head><title>Musician</title><h2 align = \"center\"><strong>Musician</strong></h2></head><body><table border=\"2\" align = \"center\">"
		"<tr><td align = \"center\"><i><strong>ID</strong></i></td>"
		"<td align = \"center\"><i><strong>Name</strong></i></td>"
		"<td align = \"center\"><i><strong>Surname</strong></i></td>"
		"<td align = \"center\"><i><strong>Birthdate</strong></i></td>"
		"<td align = \"center\"><i><strong>Year</strong></i></td>"
		"<td align = \"center\"><i><strong>Rating</strong></i></td>"
		"<td align = \"center\"><i><strong>Role</strong></i></td>"
		"<td align = \"center\"><i><strong>Style</strong></i></td></tr>"
		"<tr><td>%i</td>"
		"<td>%s</td>"
		"<td>%s</td>"
		"<td>%s</td>"
		"<td>%i</td>"
		"<td>%.2f</td>"
		"<td>%s</td>"
		"<td>%s</td></tr>"
		"</table></body>",
		self->id, self->name, self->surname, self->birthdate, self->year, self->rating, self->band.role, self->band.style);
	return buff;
}
