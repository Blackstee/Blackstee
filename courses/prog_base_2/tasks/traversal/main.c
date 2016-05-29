#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tree.h"
#include "cJSON.h"


struct musician_s {
    char * name;
    char * surname;
    int year;
    double rating;
};

// write students data to stream
void musician_write(musician_t * self, FILE * outputStream) {

}

musician_t * musician_new_from_json_object(void * fileTreeNode,  musician_t * self) {


	 char * name = cJSON_GetObjectItem(fileTreeNode, "name")->valuestring;
	 strcpy(self->name, name);
	 puts (self->name);
	 char * surname = cJSON_GetObjectItem(fileTreeNode, "surname")->valuestring;
	 strcpy(self->surname, surname);
	 puts(self->surname);
     int year = cJSON_GetObjectItem(fileTreeNode, "year")->valueint;
     self->year = year;
     printf ("%i\n", self->year);
     puts ("finished");
     return self;
}

musician_t * musician_new ()
{
    musician_t * mus = malloc (sizeof(struct musician_s));
    return mus;
}

void * musician_free(musician_t * self) {
	free(self->name);
	free(self->surname);
	free(self);
}

// traversal search
void find_eldest(void * userdata, musician_t * mus) {
	/* */
}

int main(void) {
	FILE * inputStream = fopen("data.json", "r");
	tree_t * tree = tree_new_from_stream(
			inputStream,
			(data_constructor_fn) musician_new_from_json_object,
			(data_destructor_fn) musician_free
		);
	fclose (inputStream);
	if (NULL == tree) {
		/* */
	}
	void * userdata = NULL; // value can be changed
	//
	// find a student by a specified criteria
	tree_traversal(tree, userdata, (traversal_callback_fn)find_eldest);
	//
	// output student data to console if search was successfull
	// @todo student_write()
	tree_free(tree);

	return 0;
}
