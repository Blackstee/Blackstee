#include <stdlib.h>
#include<stdio.h>

#include "object.h"

 struct object_s
 {
     bool ispicked;
     char * name;
     int plan;
 };

 object_t * object_t_new (char * name, bool ispicked)
 {
     object_t * obj = (object_t *)malloc (sizeof(struct object_s));
     obj->name = name;
     obj->ispicked = ispicked;
     obj->plan = 0;
     return obj;
 }

 void object_t_free (object_t * self)
 {
     free (self->name);
     free (self);
 }

 void object_t_change (object_t * self)
 {
     if (self->ispicked)
        self->ispicked = false;
     else self->ispicked = true;
 }

 void object_t_print (object_t * self)
 {
     puts ("HERE IS ");
     puts (self->name);
     printf ("%i", self->ispicked);
 }

 bool object_t_get_ispicked (object_t * self)
 {
     return self->ispicked;
 }

 int object_t_get_plan(object_t * self)
 {
     return self->plan;
 }

 void object_t_write_plan (object_t * self, int plan)
 {
     self->plan = plan;
 }

void object_t_copy (object_t * to, object_t * from)
 {
    to->name = from->name;
    to->ispicked = from->ispicked;
    to->plan = from ->plan;
 }
