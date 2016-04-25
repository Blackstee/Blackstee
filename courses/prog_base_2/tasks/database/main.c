#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>
#include "db_manager.h"
#include "musicians.h"

int main(void)
{
    const char * dbFile = "musicians.db";
    musician_t musicianList[50];
    db_t * db = db_new(dbFile);
    //counting all musicians in the beginning
    int countAllMusicians = db_countMusicians(db);
    //printing the number of musicians
    printf("\nThe number of musicians: %i\n", countAllMusicians);
    //making the select
    int count = db_getMusiciansTask(db, 0, 10000, musicianList, 20);
    //printing selected
    printf("Here are the selected: %d\n",count);
    musician_printList(&musicianList, count);
    //inserting musician number 1 one more time
    db_insertMusician(db,&musicianList[0]);
    //update: on the place number 2 stands number 1
    db_updateMusician(db,&musicianList[1],3);
    //counting all musicians after inserting one musician
    countAllMusicians = db_countMusicians(db);
    //printing the number of musicians
    printf("\nThe number of musicians: %i\n", countAllMusicians);
    //deleting Musician number 1
    db_deleteMusician(db, 1);
    //getting the musician by number
    musician_t * mus = db_getMusicianByNumber(db,2);
    getch();
    db_free(db);
    return 0;
}
