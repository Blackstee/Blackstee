#ifndef FS_H_INCLUDED
#define FS_H_INCLUDED

#include "server.h"
#include "info.h"
typedef struct text_s text_t;

typedef struct sentence_s sentence_t;

typedef struct word_s word_t;

text_t * text_t_new ();
sentence_t * sentence_t_new ();
word_t * word_t_new(char * letters);

void text_free(text_t * text);
void sentence_free(sentence_t * sentence);
void word_free(word_t * word);

void word_add (sentence_t * sentence, word_t * word);
void sentence_add (text_t * text, sentence_t * sentence);
cons_t * fprint(text_t * text);

void file_read (const char * txt, text_t * text, sentence_t * sentence);
int dir_exists(const char * dirname) ;

int dir_printFiles(const char * dirname);

int file_exists(const char * filename);

long long file_getSize(const char * filename);

//time_t file_getCreateTime(const char * filename);

int file_create(const char * filename);

int file_remove(const char * filename);

#endif // FS_H_INCLUDED
