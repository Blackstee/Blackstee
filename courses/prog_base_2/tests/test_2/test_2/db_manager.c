#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>

#include "db_manager.h"

//#include "musicians.h"

/*struct db_s
{
    sqlite3 * db;
};

db_t * db_new(const char * dbFile)
{
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, &self->db);
    if (SQLITE_ERROR == rc) {
        printf("Can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self)
{
    sqlite3_close(self->db);
    free(self);
}

int db_insertMusician(db_t * self, musician_t * mus)
{
    int newMusicianNumber = -1;
    sqlite3_stmt * stmt = NULL;
    int rc = 0;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db,"INSERT INTO data  (Name, Surname, Rating, Instruments, Salary, Style) VALUES (?, ?, ?, ?, ?, ?);", -1, &stmt, NULL))
        puts("It is not prepared!\n");
    sqlite3_bind_text(stmt, 1, mus->name, strlen(mus->name), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, mus->surname, strlen(mus->surname), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, mus->rating);
    sqlite3_bind_int(stmt, 4, mus->instruments);
    sqlite3_bind_int(stmt, 5, mus->salary);
    sqlite3_bind_text(stmt, 6, mus->style,strlen(mus->style),SQLITE_TRANSIENT);
    if (SQLITE_DONE != (rc = sqlite3_step(stmt)))
        printf("It is not inserted! %i\n", rc);
     newMusicianNumber = (int) sqlite3_last_insert_rowid (self->db);
     sqlite3_finalize(stmt);
    return newMusicianNumber;
}

musician_t * db_getMusicianByNumber(db_t * self, int number)
{
    musician_t * mus = malloc(sizeof(musician_t*));
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT * FROM data WHERE ID = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, number);
     while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
        {
            printf("Can't select musicians\n");
            exit(1);
        }
        else if (SQLITE_DONE == rc)
        {   sqlite3_finalize(stmt);
            return mus;
}
        else
        {
            _fillMusician(stmt, mus);
        }
    }
    sqlite3_finalize(stmt);
}

void db_updateMusician(db_t * self, musician_t * mus, int number)
{
    sqlite3_stmt * stmt = NULL;
    int rc = 0;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db,"UPDATE data SET Name = ?, Surname = ?, Rating = ?, Instruments = ?, Salary = ?, Style = ? WHERE ID = ?;", -1, &stmt, NULL)) {
        printf("It is not prepared!\n");
    }
    sqlite3_bind_text(stmt, 1, mus->name, strlen(mus->name), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, mus->surname, strlen(mus->surname), SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, mus->rating);
    sqlite3_bind_int(stmt, 4, mus->instruments);
    sqlite3_bind_int(stmt, 5, mus->salary);
    sqlite3_bind_text(stmt, 6, mus->style,strlen(mus->style),SQLITE_TRANSIENT);
     if (SQLITE_DONE != (rc = sqlite3_step(stmt)))
        printf("It is not updated! %i\n", rc);
     sqlite3_finalize(stmt);
}

void db_deleteMusician(db_t * self, int number)
{
    sqlite3_stmt * stmt = NULL;
    if(SQLITE_OK != sqlite3_prepare_v2(self->db, "DELETE FROM data WHERE ID = ?;", -1, &stmt, 0))
        printf("It is not prepared!\n");
    sqlite3_bind_int(stmt, 1, number);
    int rc = sqlite3_step(stmt);
    if (SQLITE_DONE != rc) {
        printf("It is not deleted! %i\n", rc);
    }
    sqlite3_finalize(stmt);

}

int db_countMusicians(db_t * self)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM data;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

static void _fillMusician(sqlite3_stmt * stmt, musician_t * mus)
{
    int number = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    const unsigned char * style = sqlite3_column_text(stmt, 3);
    double rating = sqlite3_column_double(stmt, 4);
    int instruments = sqlite3_column_int(stmt, 5);
    int salary = sqlite3_column_int(stmt, 6);
    mus->number = number;
    strcpy(mus->name, (const char *)name);
    strcpy(mus->surname, (const char *)surname);
    strcpy(mus->style, (const char *)style);
    mus->rating = rating;
    mus->instruments = instruments;
    mus->salary = salary;
}

int db_getMusiciansTask(db_t * self, int K, int P, musician_t * arr, int arrMax)
{
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM data WHERE Instruments > ? AND Salary > ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_int(stmt, 2,P);
    int count = 0;
    while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
        {
            printf("Can't select musicians\n");

            exit(1);
        }
        else if (SQLITE_DONE == rc)
        {

            break;
        }
        else
        {
            _fillMusician(stmt,&arr[count]);
            count++;
        }
    }

    sqlite3_finalize(stmt);
    return count;
}
*/
