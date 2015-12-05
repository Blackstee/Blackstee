#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <tchar.h>
#include <conio.h>
void PosColor(int x, int y, int color)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    SetConsoleCursorPosition(hConsole, coord);
}
void initWork (int linesNum){
    int curX, curY;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    smile ();
    system ("cls");
    for (curX = 5; curX < 75; curX++)
        for (curY = 2; curY < (6 + linesNum) ; curY++){
        PosColor (curX, curY, green);
        puts(" ");
        }
    for (curX = 5; curX < 75; curX++){
        PosColor (curX, 2, green);
        printf ("*");
        Sleep (10);
    }
    for (curY = 2; curY < (6 + linesNum); curY++){
        PosColor (74, curY, green);
        printf ("*");
        Sleep (10);
    }
    for (curX = 74; curX > 4; curX--){
        PosColor (curX, (5 + linesNum), green);
        printf ("*");
        Sleep (10);
    }
    for (curY = (5 + linesNum); curY > 1; curY--){
        PosColor (5, curY, green);
        printf ("*");
        Sleep (10);
    }
    charmaking (linesNum);
}

void charmaking (int linesNum) {
    char a [linesNum][60];
    char *text [linesNum];
    int i, curX, curY;
    int white_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    int blue_text = FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int blueB_text = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    int red_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY;
    for (i = 0; i < linesNum; i++) {
    PosColor  (3, (7 + linesNum), white_text);
    printf (" Enter a string number ");
    printf ("%i", i + 1);
    printf ( " \n\n             HERE>> ");
    PosColor ( 20, 9 + linesNum, white_text);
    gets(a[i]);
    if (strlen(a[0]) == 0)
        i = -1; else {
    if (strlen(a[i]) > 59 ) {
       PosColor (5, 12 + linesNum, white_text);
       printf ("The line is too long!");
       i--;
       getch();
       for (curX = 5; curX < 26; curX++){
        PosColor (curX, 12 + linesNum, 0);
        printf (" ");
       }
        for (curX = 0; curX < 81; curX++){
        PosColor (curX, 10 + linesNum, 0 );
        printf (" ");
        PosColor(0, 0, blue_text);
    }
       }
    else {
       PosColor(10, 4 + i, blue_text);
       text[i] = &a[i][0];
       puts(a[i]);
    }
    for (curX = 20; curX < 81; curX++){
        PosColor (curX, 9 + linesNum, 0 );
        printf (" ");
    }
    if (i != 0 && strlen(a[i]) == 0)
        i--;
    PosColor(0, 0, blue_text);
    }
    }
    clearaftertable (linesNum);
    PosColor (0, 7 + linesNum, white_text);
    functions(text, linesNum);
}

void functions (char * text[], int linesNum){
    char c [80], k [80];
    char * ptr = &c;
    int i, j = 0, l = 0, number;
    int white_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE |FOREGROUND_INTENSITY;
    help (linesNum);
    PosColor (5, 7 + linesNum, white_text);
    printf ("Please, enter the needed function without a number\n\n     HERE>> ");
    gets (c);
    for (i = 0; i < 80; i++){
        if (c[i] != ' '){
          k[j] = c[i];
          j++;
          l = 1;
        }
        if (c[i] == ' ' && l == 1){
          k[j] = c[i];
          j++;
          k[j] = 0;
          break;
        }
    }
    if (strcmp(k, "random") == 0  || strcmp(k, "shorterthan") == 0 || strcmp(k, "longerthan") == 0){
        printf ("Enter the number >> ");
        scanf ("%i", &number);
        printf ("\n");
        printf ("%i", number);
    }
    clearaftertable (linesNum);
    if (strcmp(k, "help") == 0){
            help (linesNum);
    } else
      if (strcmp(k, "exit") == 0){
          PosColor (0,0,0);
          system ("cls");
          getch();
          initRectf();
    } else
      if (strcmp(k, "length") == 0){
          lenofstrings (text, linesNum);
    } else
      if (strcmp(k, "longest") == 0){
            maxlen (text, linesNum);

    }
      if (strcmp(k, "shortest") == 0){
          minlen (text, linesNum);
    }
      if (strcmp(k, "random") == 0){
        randomletters(text, linesNum, number);
    }
      if (strcmp(k, "swap") == 0){
        change (text, linesNum);

    }
      if (strcmp(k, "shorterthan") == 0){
        findlessthan (text, linesNum, number);
    }
      if (strcmp(k, "longerthan") == 0){
        findmorethan (text, linesNum, number);
    }
      if (strcmp(k, "numberofwords") == 0){
        wordcount (text, linesNum);
    }
      if (strcmp(k, "integer") == 0){
            findNumInAllStrings(text, linesNum);

    }
     functions(text, linesNum);
}

void help (int linesNum){
    int curX, curY;
    int green_text = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int white_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE |FOREGROUND_INTENSITY;
    int yellow_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    PosColor (20, 7 +linesNum, yellow_text);
    puts("HELP");
    curX = 5;
    curY = 9 + linesNum;
    PosColor (curX, curY++, green_text);
    puts("length");
    PosColor (curX, curY++, green_text);
    puts("longest");
    PosColor (curX, curY++, green_text);
    puts("shortest");
    PosColor (curX, curY++, green_text);
    puts("random r");
    PosColor (curX, curY++, green_text);
    puts("swap");
    PosColor (curX, curY++, green_text);
    puts("shorterthan s");
    PosColor (curX, curY++, green_text);
    puts("longerthan l");
    PosColor (curX, curY++, green_text);
    puts("numberofwords");
    PosColor (curX, curY++, green_text);
    puts("integer");
    PosColor (curX, curY++, green_text);
    puts("exit");
    curX = 20;
    curY = 9 + linesNum;
    PosColor (curX, curY++, white_text);
    puts("Shows the length of each string");
    PosColor (curX, curY++, white_text);
    puts("Shows the longest string");
    PosColor (curX, curY++, white_text);
    puts("Shows the shortest string");
    PosColor (curX, curY++, white_text);
    puts("Fills with random symbols r length strings");
    PosColor (curX, curY++, white_text);
    puts("Swaps the first longest string and the last shortest one");
    PosColor (curX, curY++, white_text);
    puts("Shows the strings with shorter length than s");
    PosColor (curX, curY++, white_text);
    puts("Shows the strings with longer length than l");
    PosColor (curX, curY++, white_text);
    puts("Shows the number of words in each string");
    PosColor (curX, curY++, white_text);
    puts("Shows if there is only one integer in string");
    PosColor (curX, curY++, white_text);
    puts("Exit program");
    getch ();
    clearaftertable (linesNum);
}

void clearaftertable (int linesNum){
    int curX, curY;
    for (curX = 0; curX < 85; curX++)
    for (curY = 7 + linesNum; curY < 25; curY++){
        PosColor(curX, curY, 0);
        printf (" ");
    }
}
void initRectf (){
    int curX, curY;
    int yellow = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    for (curX = 10; curX < 70; curX++)
        for (curY = 5; curY < 15 ; curY++){
        PosColor (curX, curY, yellow);
        puts(" ");
        }
    for (curX = 10; curX < 70; curX++){
        PosColor (curX, 5, yellow);
        printf ("*");
        Sleep (10);
    }
    for (curY = 5; curY < 15; curY++){
        PosColor (69, curY, yellow);
        printf ("*");
        Sleep (10);
    }
    for (curX = 69; curX > 9; curX--){
        PosColor (curX, 14, yellow);
        printf ("*");
        Sleep (10);
    }
    for (curY = 14; curY > 4; curY--){
        PosColor (10, curY, yellow);
        printf ("*");
        Sleep (10);
    }
    initsize(curX = 13, curY = 8, 0);
}

void smile () {
int curX, curY;
int yellow = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
for (curX = 37; curX < 42; curX++) {
    PosColor (curX, 16, yellow);
    printf (" ");
}
for (curX = 35; curX < 44; curX++){
    if (curX < 37 || curX > 41){
    PosColor (curX, 17, yellow);
    printf (" ");
    }
}
for (curX = 34; curX < 45; curX+= 10){
    PosColor (curX, 18, yellow);
    printf (" ");
}
for (curX = 33; curX < 46; curX+= 12){
        for (curY = 19; curY < 21; curY++){
    PosColor (curX, curY, yellow);
    printf (" ");
}
}
for (curX = 32; curX < 47; curX+= 14){
        for (curY = 21; curY < 26; curY++){
    PosColor (curX, curY, yellow);
    printf (" ");
}
}
for (curX = 33; curX < 46; curX+= 12){
        for (curY = 26; curY < 28; curY++){
    PosColor (curX, curY, yellow);
    printf (" ");
}
}
for (curX = 34; curX < 45; curX+= 10){
    PosColor (curX, 28, yellow);
    printf (" ");
}
for (curX = 35; curX < 44; curX++){
    if (curX < 37 || curX > 41){
    PosColor (curX, 29, yellow);
    printf (" ");
    }
}
for (curX = 37; curX < 42; curX++) {
    PosColor (curX, 30, yellow);
    printf (" ");
}
for (curX = 39; curX < 44; curX+= 3){
        for (curY = 20; curY < 23; curY++){
    PosColor (curX, curY, yellow);
    printf (" ");
}
}
for (curX = 40; curX < 45; curX+= 3) {
    PosColor (curX, 22, yellow);
    printf (" ");
}
for (curX = 39; curX < 44; curX++) {
    PosColor (curX, 27, yellow);
    printf (" ");
}
for (curX = 37; curX < 40; curX++) {
    PosColor (curX, 26, yellow);
    printf (" ");
}
for (curX = 43; curX < 45; curX++) {
    PosColor (curX, 26, yellow);
    printf (" ");
}
for (curX = 36; curX < 38; curX++) {
    PosColor (curX, 25, yellow);
    printf (" ");
}
PosColor (5, 2,  0);
getch ();
}
void cherepok () {
int curX, curY;
int red = BACKGROUND_RED | BACKGROUND_INTENSITY;
PosColor (37, 16, red);
for (curX = 37; curX < 42; curX++) {
    PosColor (curX, 16, red);
    printf (" ");
}
for (curX = 36; curX < 43; curX++)
for (curY = 17; curY < 19; curY++){
    PosColor (curX, curY, red);
    printf (" ");
}
for (curX = 36; curX < 43; curX += 3)
for (curY = 19; curY < 21; curY++){
    PosColor (curX, curY, red);
    printf (" ");
}
for (curX = 37; curX < 42; curX++){
    if (curX != 39){
    PosColor (curX, 21, red);
    printf (" ");
    }
}
for (curX = 38; curX < 41; curX++)
    for (curY = 22; curY < 25; curY+=2){
    PosColor (curX, curY, red);
    printf (" ");
}
for (curX = 37; curX < 42; curX+=4){
    PosColor (curX, 23, red);
    printf (" ");
}
for (curX = 35; curX < 44; curX+= 8)
    for (curY = 24; curY < 31; curY+= 6){
    PosColor (curX, curY, red);
    printf (" ");
}
for (curX = 34; curX < 45; curX++)
    for (curY = 25; curY < 31; curY+= 4){
    if (curX < 37 || curX > 41) {
    PosColor (curX, curY, red);
    printf (" ");
    }
}
for (curX = 36; curX < 43; curX++)
    for (curY = 26; curY < 30; curY+= 2){
    if (curX != 39) {
    PosColor (curX, curY, red);
    printf (" ");
    }
}
for (curX = 38; curX < 41; curX++){
    PosColor (curX, 27, red);
    printf (" ");
}
}
void initsize(int curX, int curY, int k){
int red_text = FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
int white_text = FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY ;
int linesNum ;
char c [10];
    PosColor (37, 7, white_text);
    printf("HELLO!");
    PosColor (15, 9, white_text);
    printf("Please, enter the number of strings (from 2 to 15)" );
    PosColor (35, 11, white_text);
    printf ("Here >> ");
    gets (c);
    linesNum = atoi (c);
    //scanf ("%d", &linesNum);
    if (linesNum <= 15 && linesNum >= 2)
    initWork (linesNum);
    else
    {
    PosColor (20, 13, red_text);
    printf ("Please, enter the NUMBER from the range");
    cherepok ();
    PosColor (43, 11, 0);
    getch();
    system ("cls");
    initRectf();
}
}
int main(void) {
initRectf ();
EXIT_SUCCESS;
    getchar();
    }
void printArray (char *text[], int linesNum){
        int i;
        for (i = 0; i < linesNum; i++){
            puts (text [i]);
            printf ("\n");
         }
     }

void lenofstrings (char *text[], int linesNum) {
    int i, len, curX, curY;
    int green_text = FOREGROUND_GREEN  | FOREGROUND_INTENSITY |BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    curX = 7;
    curY = 4;
    for (i = 0; i < linesNum; i++)
{

     len = strlen(text[i]);
     PosColor (curX, curY, yellow_text);
     printf ("%i\n", len);
     curY++;
}
     getch();
    curX = 7;
    curY = 4;
    for (curY = 4; curY < 4 + linesNum; curY++)
        for (curX = 7; curX < 9; curX++)
{
     PosColor (curX, curY, green_text);
     printf (" ");
}

    }


void maxlen (char *text[], int linesNum) {
    int maxlen, i;
    int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    maxlen = strlen (text [0]);
    for (i = 0; i < linesNum; i++)
    {
        if (strlen (text[i]) >= maxlen)
            maxlen = strlen (text[i]);
    }
    for (i = 0; i < linesNum; i++)
    {
        if (strlen (text[i]) == maxlen){
            PosColor(10, 4 + i, yellow_text);
            puts (text[i]);
        }
    }
    }

void minlen (char *text[], int linesNum) {
    int i, minlen;
    int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    minlen = strlen (text[0]);
    for (i = 0; i < linesNum; i++)
    {
        if (strlen (text[i]) <= minlen)
            minlen = strlen (text[i]);
    }
    for (i = 0; i < linesNum; i++)
    {
        if (strlen (text[i]) == minlen){
            PosColor (10, 4 + i, yellow_text);
            puts (text[i]);
        }
    }
    }

void randomletters (char *text[], int linesNum, int k) {
    char *randch;
    int curX, curY;
    int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int i, j;
    time_t t;
    for (curX = 10; curX < 73; curX++)
    for (curY = 4; curY < 5 + linesNum; curY ++){
        PosColor(curX, curY, green);
        printf(" ");
    }

    srand((unsigned) time (&t));
    for (i = 0; i < linesNum; i++){
        randch = (char*)malloc(k*sizeof(char));
        for (j = -1; j < k+1; j++){
            if ( k == j){
                randch[j] = '\0';
                break;

            }
            randch[j] = (char) ((rand()%94) + 33);
        }
        *(text + i) = randch;
        PosColor (10, 4 + i, yellow_text);
          printf ("%s\n", *(text + i));
    }
    }

void change (char *text[], int linesNum) {
    int maxfirst, minlast, maxlen, minlen, i, curX, curY, k, r;
    int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int green_text = FOREGROUND_GREEN  | FOREGROUND_INTENSITY |BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    char *string;
    maxlen = strlen (text[0]);
    for (i = 0; i < linesNum; i++)
    {
        if (strlen (text[i]) > maxlen){
            maxlen = strlen (text[i]);
            maxfirst = i;
        }
    }
    minlen = strlen (text[0]);
    for (i = 0; i < linesNum; i++)
    {
        if (strlen (text[i]) <= minlen){
            minlen = strlen (text[i]);
            minlast = i;
            }
    }
    if (minlen == maxlen)
        printf ("Dovshina usih strok odnakova");
    else {
            string = text [minlast];
            text [minlast] = text [maxfirst];
            text [maxfirst] = string;
    }
    curY = 4 + maxfirst;
    for (curX = 10; curX < 75; curX++)
    {
        PosColor (curX, curY, green_text);
        printf (" ");
    }
    for (i = 0; i < linesNum; i++){
            if (i == minlast){
            PosColor(10, 4 + i, yellow_text);
            puts (text [i]);}
            if (i == maxfirst){
            PosColor(10, 4 + i, yellow_text);
            puts (text [i]);
         }}
    }
void findlessthan (char *text[], int linesNum, int l){
         int i;
         int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
         for (i = 0; i < linesNum; i++)
         {
             if (strlen(text[i]) < l){
                PosColor (10, 4 + i, yellow_text);
                puts (text [i]);
             }
         }
     }

void findmorethan (char *text[], int linesNum, int l){
         int i;
         int red_text = FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
         for (i = 0; i < linesNum; i++)
         {
             if (strlen(text[i]) > l){
                PosColor (10, 4 + i, red_text);
                puts (text [i]);
             }

         }
     }

void wordcount (char *text[], int linesNum){
        int i, j, counter, l;
        const char *invalid_characters = " 1234567890!@#$%^&*()_+=-{}[];:<>,./?|\\\"'~`";
        for (i = 0; i < linesNum; i++)
    {
        counter = 0;
        l = 0;
            for (j = 0; j < strlen(invalid_characters); j++) {

              if (*(text[i] + j) == *(invalid_characters + j)) {
                    l = 1;
               } else {
                   if (l == 1) {
                       counter++; l = 0;
                    }
              }
                if (counter == 1)
                    printf ("line number %d has %d word\n", i, counter);
                else
                    printf("line number %d has %d words\n", i, counter);
            }

     }}


void checkDigitsStr(char * s, int index, int val) {
    int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    while (*s) {
		if (isdigit(*s++) == 0) {
			printf("String num %d is not string with the number only\n", index);
			return;
		}
	}
	printf("String num %d consists of number %d\n", index, val);
}

void findNumInStr(char * myText [], int len, int index) {
	int val;
	int yellow_text = FOREGROUND_GREEN  | FOREGROUND_RED |FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	if (index >= len) {
		puts("Sorry, index is out of range of array");
		return;
	}
	val = atoi(myText[index]);
	checkDigitsStr(myText[index], index, val);
    }

void findNumInAllStrings(char * myText [], int len) {
	int i;
	for (i = 0; i < len; i++)
		findNumInStr(myText, len, i);
    }
