#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

//============musician============
typedef struct {
	char * style;
	char * role;
} band_t;

typedef struct {
    int     id;
	char * 	name;
	char * 	surname;
	char *  birthdate;
	int 	year;
	float	rating;
	band_t band;
} musician_t;

//==============errors=============
typedef struct error_s
{
    int status;
    char * error;
}error_t;

//===============list of musicians=========
typedef struct mus_arr_s mus_arr_t;

//================musician=================
musician_t * musician_t_new (void);
void musician_t_free (musician_t * self);
void musician_t_add_info (musician_t * self, int id, char * name, char * surname, char * birthdate, int year, float rating, char * role, char * style);
musician_t * mus_delete (const mus_arr_t * self, int ID);
musician_t * mus_get (mus_arr_t * self, int ID);

//===============list of musicians========
mus_arr_t * mus_arr_t_new (void);
void mus_arr_t_free (mus_arr_t * self);
int mus_arr_t_get_size (mus_arr_t * self);
void mus_arr_t_add_back (mus_arr_t * mus_arr, const musician_t * musician);
void mus_arr_t_add_by_index(mus_arr_t * mus_arr, const musician_t * musician, int index) ;

//==================ID====================
int mus_arr_t_get_free_id (mus_arr_t * self);

//=============musicians Json==============
const char * musician_toJSON(const musician_t * self);
const char * musician_listToJSON(const mus_arr_t * mus_arr, int musicianListSize);

//============error Json==================
const char * error_toJSON(const error_t * self);

//===========musicians HTML=================
char * musician_listToHTML (const mus_arr_t * self) ;
char * musician_toHTML (const musician_t * self);


#endif // RESOURCE_H_INCLUDED
