#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "list.h"

typedef int (*cmp_f)(list_t * list1);
typedef void (*react_f)(list_t * list1);

typedef struct dynamic_s {
    HANDLE hLib;
    cmp_f cmp;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();
void print(list_t * list1);

int main(void) {
    const int max_size_list = 20;
    list_t * list1 = list_t_new();
    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->cmp) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!");
    srand(time(NULL));
    int i;
    for (i = 0; i < max_size_list; i++)
    {
        list_t_add_elem_end(list1, 'g');
        list_t_add_elem_end (list1, 'a');//list_t_add_elem(list1, rand()%100+22);
    }
        list_t_print(list1);
        if(dll->cmp(list1)== 1 || dll->cmp(list1) == 0) {
            dll->react(list1);
        }
    list_t_add_elem_end (list1, 'j');
        list_t_print(list1);
        if(dll->cmp(list1)== 1 || dll->cmp(list1) == 0) {
            dll->react(list1);
        }
    list_t_add_elem_end (list1, 'a');
    list_t_add_elem_end (list1, 'e');
       list_t_print(list1);
        if(dll->cmp(list1)== 1 || dll->cmp(list1) == 0) {
            dll->react(list1);
        }
    for (int k = 0; k < 7; k++)
    list_t_add_elem_end (list1, ' ');
       list_t_print(list1);
        if(dll->cmp(list1)== 1 || dll->cmp(list1) == 0) {
            dll->react(list1);
        }
         list_t_print(list1);
    list_t_free(list1);
    dynamic_clean(dll);
    return 0;
}

const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "Lab2DLL1.dll";
        } else if (dllNum == 2) {
            return "Lab2DLL2.dll";
        }
    }
    return NULL;
}

void print(list_t * list1) {
    system("cls");
    printf("List: ");
    list_t_print(list1);
    Sleep(500);
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->cmp = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->cmp = (cmp_f)GetProcAddress(dyn->hLib, "compare");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
