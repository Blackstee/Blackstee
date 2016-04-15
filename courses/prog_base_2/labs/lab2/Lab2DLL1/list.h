#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct list_s  list_t;

list_t * list_t_new ();

void list_t_free (list_t * list);

void list_t_add_elem_end (list_t * list, char value);
void list_t_print (list_t * list);
int list_t_get_size (list_t * list);
char list_t_get_elem (list_t * list, int index);
void list_t_change_elem_by_index (list_t * list, char value, int ind);

#endif // LIST_H_INCLUDED
