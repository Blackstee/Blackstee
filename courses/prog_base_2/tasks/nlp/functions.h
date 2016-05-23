#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

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
void fprint(text_t * text);

void file_read (const char * txt, text_t * text, sentence_t * sentence);
#endif // FUNCTIONS_H_INCLUDED
