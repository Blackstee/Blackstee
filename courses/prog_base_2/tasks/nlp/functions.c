#include <stdlib.h>
#include<stdio.h>

#include "functions.h"
#include "list.h"
#include <string.h>
struct text_s
{
    list_t * sentences;
};

struct sentence_s
{
    list_t * words;
};

struct word_s
{
    char * letters;
};

text_t * text_t_new ()
{
    text_t * text = malloc (sizeof (struct text_s));
    text->sentences = list_new();
    return text;
}

sentence_t * sentence_t_new ()
{
    sentence_t * sentence = malloc (sizeof (struct sentence_s));
    sentence->words = list_new();
    return sentence;
}

word_t * word_t_new(char * letters)
{
    word_t * word = malloc(sizeof(word_t));
    word->letters = malloc(sizeof(char)*strlen(letters));
    strcpy(word->letters, letters);
    return word;
}

void text_free(text_t * text)
{
	for (int i = 0; i < list_getSize(text->sentences); i++)
		sentence_free(list_get(text->sentences, i));
	list_free(text->sentences);
	free(text);
}

void sentence_free(sentence_t * sentence)
{
	for (int i = 0; i < list_getSize(sentence->words); i++)
		word_free(list_get(sentence->words, i));
	list_free(sentence->words);
	free(sentence);
}

void word_free(word_t * word)
{
	free(word);
}

void file_read (const char * txt, text_t * text, sentence_t * sentence)
{
    FILE * file = fopen(txt, "r");
    if(file == NULL)
        return;
    char c;
    int len = 0;
    char word[25] = "";
    while((c = fgetc(file)) != EOF)
    {
       if(ispunct(c))
        {
            if(c == '.' || c == '!' || c == '?')
            {
                if(len == 0)
                    continue;
                word_add(sentence, word_t_new(word));
                sentence_add(text, sentence);
                sentence = sentence_t_new();
                memset(word, 0, 25);
                len = 0;
            }
            continue;
        }
        else if(isspace(c))
        {
            if(len == 0)
                continue;
            word_add(sentence, word_t_new(word));
            memset(word, 0, 25);
            len = 0;
        }
        else
        {
            word[len] = c;
            len++;
        }
    }
    fclose(file);
}

void word_add (sentence_t * sentence, word_t * word)
{
    for(int i = 0; i < list_getSize(sentence->words); i++)
    {
        word_t * wrd = list_get(sentence->words, i);
        if(!strcmp(word->letters, wrd->letters))
            return 0;
    }
    list_push_back(sentence->words, word);
}

void sentence_add (text_t * text, sentence_t * sentence)
{
    list_push_back(text->sentences, sentence);
}

void fprint(text_t * text)
{
    FILE * file = fopen("output.txt", "w");
    if(NULL == file)
        return 1;
    int i, j, count = 1;
    for (count = 0; count < 15; count++)
    {
     for(i = 0; i < list_getSize(text->sentences); i++)
      {
        sentence_t * sentence = list_get(text->sentences, i);
        for(j = 0; j < list_getSize(sentence->words); j++)
        {
            word_t * word = list_get(sentence->words, j);
            if (strlen(word->letters) == count && isupper(abs(word->letters[0])))
            {
                printf("%s", word->letters);
                fprintf(file, "%s",  word->letters);
                fprintf(file, "\n");
                printf("\n");
            }
        }
       }
    }
    fclose(file);
}

