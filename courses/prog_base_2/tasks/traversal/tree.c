#include "tree.h"
#include "cJSON.h"

#include "string.h"

typedef struct node_s node_t;

struct node_s {
	struct musician_s * data;
	node_t * left;
	node_t * right;
};

struct tree_s {
	node_t * root;
	data_destructor_fn data_destructor;
};

node_t * node_insert(node_t * node)
{

    // problem with memory
    // has to be solved in recursion (?)

    if (node->data == NULL)
    {
        //node_t * node = malloc(sizeof(struct node_s));
        return node;
    }
    node_insert(node->left);
    node_insert(node->right);
}

void node_new (node_t * node)
{
    node_t * node1 =  malloc (sizeof (struct node_s));
    node1->left = NULL;
    node1->right = NULL;
    node1->data = NULL;
    if (node->data = NULL)
        node = node1;
    node_free (node1);
    node_new (node->left);
    node_new (node->right);
}

tree_t * tree_new_from_stream(
		FILE * inputStream,
		data_constructor_fn constructorCallback,
		data_destructor_fn destructorCallback
	) {
	 char line[100];
	 char text[10000];
	 while(fgets(line, 100, inputStream) != NULL) {  // read file
        strcat(text, line);
    }

	//new tree
	tree_t * tree = malloc(sizeof(struct tree_s));
	node_new (tree->root);

    //has to be recursion there (parsing of json)
    cJSON * jList = cJSON_Parse(text);
    int n = cJSON_GetArraySize(jList);
    printf ("count %i", n);
    for (int i = 0; i < n; i++) {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        musician_t * mus = musician_new ();
        node_t * node = node_insert (tree->root);
        musician_new_from_json_object(jItem, mus);
        tree->root = mus;
        }
    cJSON_Delete(jList);
    return tree;
}

//============free==========
void node_free (node_t * self)
{
    if (self->left != NULL)
        node_free (self->left);
        else
            free(self->left);
    if (self->right != NULL)
        node_free (self->right);
        else
            free (self->right);
    if (self->data != NULL)
        free (self->data);
}

void tree_free(tree_t * self) {
	if (self->root == NULL)
	free(self->root);
	else
       node_free (self->root);
}
//===============search=================

node_t * node_search (node_t * root)
{
    int max = 0;
    if (root->data == NULL)
        return;
    if (root->data->year > max)
        max = root->data->year;
    node_search (root->left);
    node_search (root->right);
}
void tree_traversal(tree_t * self, void * userdata, traversal_callback_fn callback)
{
    if (self->root == NULL)
    {
        return;
    }
    node_search (self->root);
}

//=============print====================

void print_tree (node_t * root)
{
    musician_t * mus = musician_new();
    mus = root->data;
    if (root->data == NULL)
        return;
    printf ("The name: %s", mus->name);
    printf ("The surname: %s", mus->surname);
    printf ("The year of popularity: %i", mus->year);
    print_tree (root->left);
    print_tree (root->right);
}

