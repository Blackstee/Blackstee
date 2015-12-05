#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    char nameofarticle[50];
    char author [30];
    int valueofwords;
} article;

int main(void)
{
    int i, k;
    char c[10];
    article art[3] = {{"Ukraine is Europe", "Skazochnik", 567}, 
	                  {"Demons in Kyiv", "Kyselev", 5463}, 
					  {"Trying to pass exams", "Unknown student of KPI ", 57864456}};
    printf("These aricles are:\n");
    for(i = 0; i < 3; i++)
    {
        printf ("\n");
		print(&art[i]);
    }
    printf("\nThere are %i articles with more than 1000 words\n", count(3, art));
    i = 0;
	while(i > 3 || i < 1){
    printf ("\nEnter the index of the article you want to change in range [0..2]\n");
    gets (c);
    i = atoi (c);
    }   
    change(&art[i-1], "Kittens one LOVE");
    puts("\nChanged article: \n");
    print(&art[i-1]);
    return EXIT_SUCCESS;
}
int count(int size, article arr[size])
{
    int i, count;
    count = 0;
    for(i = 0; i < size; i++)
        if(arr[i].valueofwords > 1000)
            count++;
    return count;
}
void change(article * pVar, const char * newValue)
{
    strcpy(pVar -> nameofarticle, newValue);
}

void print(article * pVar)
{
    printf("Name of article: %s\nAuthor of article: %s\nValue of words: %i\n", pVar -> nameofarticle, pVar -> author, pVar -> valueofwords);
}
