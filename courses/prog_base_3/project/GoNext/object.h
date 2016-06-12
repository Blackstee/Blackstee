#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED


typedef struct object_s object_t;

object_t * object_t_new (char * name, bool ispicked);

void object_t_free (object_t * self);

void object_t_change (object_t * self);

void object_t_print (object_t * self);

bool object_t_get_ispicked (object_t * self);

void object_t_write_plan (object_t * self, int plan);

int object_t_get_plan (object_t * self);

void object_t_copy (object_t * to, object_t * from);

#endif // OBJECT_H_INCLUDED
