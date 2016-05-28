#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

#include "fs.h"
#include "list.h"

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
            return;
    }
    list_push_back(sentence->words, word);
}

void sentence_add (text_t * text, sentence_t * sentence)
{
    list_push_back(text->sentences, sentence);
}

cons_t * fprint(text_t * text)
{
    int vowels = 0;
    int consonants = 0;
    cons_t * cons = cons_t_new();
    int i, j, k;
     for(i = 0; i < list_getSize(text->sentences); i++)
      {
        sentence_t * sentence = list_get(text->sentences, i);
        for(j = 0; j < list_getSize(sentence->words); j++)
        {
            word_t * word = list_get(sentence->words, j);
            for (k = 0; k < strlen (word->letters); k++)
            {
                if (word->letters[k]>= 'A' && word->letters[k]<= 'Z')
                     word->letters[k] = word->letters[k] + 'a' - 'A';
                if (word->letters[k] >= 'a' && word->letters[k] <= 'z')
            if (word->letters[k] == 'a' || word->letters[k] == 'e' || word->letters[k] == 'i' || word->letters[k] == 'o' || word->letters[k] == 'u')
                vowels++;
                else consonants++;
            }
        }
    }
    cons->vowels = vowels;
    cons->consonants = consonants;
    printf ("Vowels %i\n", vowels);
    printf ("Consonants %i\n", consonants);
    puts (cons);
    return cons;
}

/**
*   @return the existence of directory
*/
int dir_exists(const char * dirname) {
    struct stat buffer;
    return (stat (dirname, &buffer) == 0) && S_ISDIR(buffer.st_mode);
}

/**
*   Prints out list of files in directory
*
*   @return number of files
*/
int dir_printFiles(const char * dirname) {
    DIR *dp;
    struct dirent *ep;
    int file_count = 0;
    dp = opendir (dirname);
    if (dp != NULL) {
        while ((ep = readdir (dp))) {
            if(32 == dp->dd_dta.attrib) {
                puts(dp->dd_dir.d_name);
                file_count++;
            }
        }
        (void) closedir (dp);
        return file_count;
    }
    else {
        return -1;
    }
}

/**
*   @return the existence of file
*/
int file_exists(const char * filename)
{
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}

/**
*   @return -1 if file not found
*/
long long file_getSize(const char * filename) {
    struct stat st;
    if (0 != stat(filename, &st)) {
        return -1;
    }
    long long size = st.st_size;
    return size;
}

time_t file_getCreateTime(const char * filename) {
    struct stat st;
    if (0 != stat(filename, &st)) {
        return (time_t)0;
    }
    return st.st_ctime;
}

/**
*   @return success of the action
*/
int file_create(const char * filename) {
    FILE * fp;
    int success = NULL != (fp = fopen(filename, "file.h"));
    if (!success) {
        return 0;
    }
    fclose(fp);
    return 1;
}

/**
*   @return success of the action
*/
int file_remove(const char * filename) {
    return 0 == remove(filename);
}
