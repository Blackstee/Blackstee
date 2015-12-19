#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <conio.h>

typedef struct
{
    char name [40];
    int cost;
} food;


void PosColor(int x, int y, int color)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    SetConsoleCursorPosition(hConsole, coord);
}
void printname (food * pVar)
{
    printf("    %s\n", pVar -> name);
}
void printcost (food * pVar)
{
    printf("%i\n", pVar -> cost);
}

/*char read (){
    FILE * fp2;
    char str [15];
    int i;
    fp2 = fopen("addeddishes.txt", "w");
    if (fp2 == NULL){
        int a = 0;
        return a;
    }
    fgets (str, 100, fp2);
    fclose (fp2);
    return str;
}*/
void dishess (int ingr, int dish, int forreck, int ingred [], int dishes [], int fordish, char c[]){
    int  i, curX, curY, r, z, b;
    char moves, chars[20];
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int yellow_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int wow_low_text_green = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_INTENSITY;
    int wow_text = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int blue_text_green = FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int wow_low_text_yel = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED;
    PosColor (15, 2, yellow_text);
    printf ("Enter 'q' to sort by price");
    //puts (read ());
    PosColor (35, 14, wow_low_text_yel);
    printf ("DISHES:");
    food ex = {"d", 0};
    food dis[6] =           {{"Rice with fish", 80},
                          {"Fried potatoes with steak", 75},
                          {"Salad(tom., cuc. and par.)", 18},
                          {"Boiled potatoes and chop", 65},
                          {"Buckwheat and chop", 60},
                          {"Pasta and steak", 75}};
    for (i  = 0; i < 6; i ++){
        PosColor (12, i + 15, blue_text_green);
        printname(&dis[i]);
        PosColor (50, i + 15, blue_text_green);
        printcost(&dis[i]);
    }
    //char l = read ();
    //PosColor (12, 21, blue_text_green);
    //printf ("%s", l);
    i = 0;
    PosColor (34, 33, wow_text);
    printf (" Added dishes:");
    PosColor (39, 35, wow_text);
    printf ("%s", c);
    PosColor(73, 15, yellow_text);
    printf("--->");
    PosColor(3, 15, yellow_text);
    printf("<---");
    PosColor (12, i + 15, wow_low_text_green);
    printname(&dis[i]);
    PosColor (50, i + 15, wow_low_text_green);
    printcost(&dis[i]);
    if (fordish != 0) {
        forreck = forreck + fordish;
        dish++;
    }
    while (1) {
    moves = getch ();
    PosColor (12, i + 15, blue_text_green);
    printname(&dis[i]);
    PosColor (50, i + 15, blue_text_green);
    printcost(&dis[i]);
    switch (moves){
         case 'w': if (i == 0)
                    i = 5;
                   else
                    i--;
                   break;
         case 's': if (i == 5)
                    i = 0;
                   else
                    i++;
                   break;
         case 13: PosColor(35, 35 + dish, wow_text);
                  printname(&dis[i]);
                  forreck = forreck + dis[i].cost;
                  dishes [dish] = dis [i].cost;
                  dish++;
                  break;
         case 'd':PosColor(0, 0, 0);
                  for (curX = 0; curX < 80; curX++)
                  for (curY = 0; curY < 33; curY++){
                    PosColor (curX, curY, 0);
                    printf (" ");
                  }
                  initmenu(2, ingr, dish, forreck, ingred, dishes, fordish, c);
                  break;
         case 'a':for (curX = 0; curX < 80; curX++)
                  for (curY = 0; curY < 33; curY++){
                    PosColor (curX, curY, 0);
                    printf (" ");
                  }
                  initmenu(0, ingr, dish, forreck, ingred, dishes, fordish, c);
                  break;
          case 'q':
              for  (curX = 12; curX < 49; curX++)
              for (curY = 15; curY < 21; curY++ ){
                PosColor(curX, curY, green);
                printf (" ");
              }
              for (z = 0; z < 6; z++) {
                     for (r = 0; r < 5-z; r++) {
                     if (dis[r].cost > dis[r+1].cost) {
                        ex = dis [r];
                        dis[r] = dis[r+1];
                        dis[r+1] = ex;
                        }
                      }
                    }
                        for (i  = 0; i < 5; i ++){
        PosColor (12, i + 15, blue_text_green);
        printname(&dis[i]);
        PosColor (50, i + 15, blue_text_green);
        printcost(&dis[i]);
    }
                    break;
    }
    PosColor (12, i + 15, wow_low_text_green);
    printname(&dis[i]);
    PosColor (50, i + 15, wow_low_text_green);
    printcost(&dis[i]);
    }

}

/*void writenewdish (int k, int maxcount, food *dis)
{
    int i;
    FILE * hr;
    hr = fopen  ("addeddishes.dat", "wb");
    for (i = 0; i < maxcount; i++){
        if (k == 1){
            fwrite ((char*)&dis[i], sizeof (food), 1, hr);
        }
    }
    fclose (hr);
}

void readnewdish (food * dis){
    FILE * hr;
    hr = fopen ("addeddishes.dat", "rb");
    if (hr == NULL)
        return;
    fseek(hr, 0, SEEK_END);
    int length = ftell (hr);
    fseek (hr, 0, SEEK_SET);
    fread (dis, length, 1, hr);
    fclose (hr);
}*/

void write(char c[], int fordish){
    FILE * fp1;
    fp1 = fopen("addeddishes.txt", "w");
    fputs (c, fp1);
    fprintf (fp1, "%i", fordish);
    fclose (fp1);
}

void ingredient (int ingr, int dish, int forreck, int ingred [], int dishes [], int fordish, char c []){
    int i, curX, curY;
    char moves;
    int red_text = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int green_text = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int wow_low_text_yel = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED;
    int yellow_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int wow_text = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int wow_low_text_green = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_INTENSITY;
    int blue_text_green = FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    PosColor (6, 1, yellow_text);
    printf ("Enter 'n' to make new dish");
    food ing[15] =       {{"Tomatoes", 8},
                          {"Carrot", 5},
                          {"Beet", 5},   //svekla
                          {"Cucumbers", 5}, //ogurci
                          {"Zucchini", 4}, //kabachki
                          {"Parsley", 5}, //petrushka
                          {"Boiled potatoes", 25},
                          {"Fried  potatoes", 30},
                          {"Baked potatoes", 27},
                          {"Buckwheat", 20}, //grechka
                          {"Pasta", 30},
                          {"Rice", 30},
                          {"Steak", 45},//stejk
                          {"Chop", 40}, //otbivnaya
                          {"Fish", 50}};
    for (i  = 0; i < 15; i ++){
        PosColor (12, i + 15, blue_text_green);
        printname(&ing[i]);
        PosColor (50, i + 15, blue_text_green);
        printcost(&ing[i]);
    }
    i = 0;
    PosColor (33, 14, wow_low_text_yel);
    printf ("INGREDIENTS:");
    PosColor (12, 33, wow_text);
    printf (" Added ingredients:");
    PosColor(73, 15, yellow_text);
    printf("--->");
    PosColor (12, i + 15, wow_low_text_green);
    printname(&ing[i]);
    PosColor (50, i + 15, wow_low_text_green);
    printcost(&ing[i]);
    while (1) {
    moves = getch ();
    PosColor (12, i + 15, blue_text_green);
    printname(&ing[i]);
    PosColor (50, i + 15, blue_text_green);
    printcost(&ing[i]);
    switch (moves){
         case 'w': if (i == 0)
                    i = 14;
                   else
                    i--;
                   break;
         case 's': if (i == 14)
                    i = 0;
                   else
                    i++;
                   break;
         case 13: PosColor(14, 35 + ingr, wow_text);
                  printname(&ing[i]);
                  forreck  = forreck + ing[i].cost;
                  ingred [ingr] = ing [i].cost;
                  fordish = fordish + ing [i].cost;
                  ingr++;
                  break;
         case 'd':for (curX = 0; curX < 80; curX++)
                  for (curY = 0; curY < 33; curY++){
                    PosColor (curX, curY, 0);
                    printf (" ");
                  }
                  initmenu(1, ingr, dish, forreck, ingred, dishes, fordish, c);
                  break;
         case 'n' :PosColor (6, 1, 0);
             printf ("                               ");
             PosColor (15, 2, green_text);
             printf ("Please, enter the name of new dish >> ");
             PosColor (54, 2, yellow_text);
             gets (c);
             write (c, fordish);
            if (strlen(c) > 15 || strlen (c) < 1){
                PosColor (30, 3, red_text);
                printf ("The name is too short or too long");
                getch();
                for (curX = 54; curX < 80; curX++){
                    PosColor (curX, 2, 0);
                    printf (" ");
                }
                for (curX = 0; curX < 80; curX++){
                    PosColor (curX, 3, 0);
                    printf (" ");
                }
             }
             break;
    }
    PosColor (12, i + 15, wow_low_text_green);
    printname(&ing[i]);
    PosColor (50, i + 15, wow_low_text_green);
    printcost(&ing[i]);
    }
}

void ending (int forreck){
int green_text = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
if (forreck < 0) forreck = 0;
PosColor (35, 8, green_text);
printf ("TO PAY : $%i", forreck);
PosColor (27, 10, green_text);
printf ("THANK YOU FOR VISITING US!");
PosColor (35, 12, green_text);
printf ("COME AGAIN!");
}

int ifitis (int index, int k, int deleted[k]){
int a = 0;
int i;
for (i = 0; i < k; i++){
    if (index == deleted[i]){
        a = 1;
        return a;
    }
if (a == 0)
        return a;
}
}
void reckoning  (int ingr, int dish, int forreck, int ingred[],  int dishes [], int fordish, char c[]){
    int wow_text = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int green_text = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int i, curX, curY;
    char moves;
    int red = BACKGROUND_RED | BACKGROUND_INTENSITY;
    int red_text = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int yellow_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    PosColor (35, 15, wow_text);
    printf("RECKONING:");
    printf ("%i", forreck);
    PosColor (14, 18, green_text);
    printf ("Here is the list of added ingredients and dishes.");
    PosColor (20, 21, green_text);
    printf ("Please, enter the '-' in front of the food");
    PosColor (25, 24, green_text);
    printf ("you would like to delete");
    PosColor (7, 26, yellow_text);
    printf ("*          **          *   *********             ***        ***");
    PosColor (7, 27, yellow_text);
    printf (" *        *  *        *    *                      *          *");
    PosColor (7, 28, yellow_text);
    printf ("  *      *    *      *     *********              *          *");
    PosColor (7, 29, yellow_text);
    printf ("   *    *      *    *      *                      *          *");
    PosColor (7, 30, yellow_text);
    printf ("    *  *        *  *       *                      *          *");
    PosColor (7, 31, yellow_text);
    printf ("     **          **        *********               **********");
    PosColor (47, 26, red);
    printf (" ");
    PosColor (51, 26, red);
    printf (" ");
    PosColor (46, 27, red);
    printf ("   ");
    PosColor (50, 27, red);
    printf ("   ");
    PosColor (46, 28, red);
    printf ("       ");
    PosColor (47, 29, red);
    printf ("     ");
    PosColor (48, 30, red);
    printf ("   ");
    PosColor (49, 31, red);
    printf (" ");
    PosColor (5, 35, red_text);
    printf ("-");
    for (curY  = 36; curY < ingr + 35; curY++){
        PosColor (5, curY, yellow_text);
        printf ("-");
    }
    for (curY = 35; curY < dish + 35; curY++){
        PosColor (70, curY, yellow_text);
        printf ("-");
    }
    i = 0;
    int f = 0, l = 0, m = 0;
    int deleted1 [ingr];
    int deleted2 [dish];
    int click = 0;   //click = 0 if ingr; click = 1 if dish
    curX = 5;
    while (1){
    moves = getch();
    if (f == 0){
    PosColor (curX, i + 35, yellow_text);
    printf ("-");
    }
    switch (moves)
    {
    case 's':
        if (f == 0){
        if ((click == 0 && i == ingr - 1)|| (click == 1 && i == dish - 1))
             i = 0;
        else i++;
        if (click == 0) curX = 5;
        else curX = 70;
        if ((click == 0 && ifitis (i, l, deleted1) == 0)||(click == 1 && ifitis (i, m, deleted2) == 0) ){
        PosColor (curX, 35 + i, red_text);
        printf ("-");
        }}
        break;
    case 'w':
        if (f == 0){
        if (click == 0 && i == 0)
             i = ingr - 1; else
             if (click == 1 && i == 0)
                i = dish - 1;
        else i--;
        if (click == 0) curX = 5;
        else curX = 70;
        if ((click == 0 && ifitis (i, l, deleted1) == 0)||(click == 1 && ifitis (i, m, deleted2) == 0) ){
        PosColor (curX, 35 + i, red_text);
        printf ("-");
        }
        }
        break;
    case 'd':
        if (f == 0){
            if (click == 0){
            click = 1;
            curX = 70;
            i = 0;
            if ((click == 0 && ifitis (i, l, deleted1) == 0)||(click == 1 && ifitis (i, m, deleted2) == 0) ){
            PosColor (curX, i + 35, red_text);
            printf ("-");
            }
        } else {
            PosColor (65, 15, red_text);
            printf ("FINISH?");
            f = 1;
        }
        }
        break;
    case 'a':
        if (f == 1) {
            f = 0;
            for (curX = 65; curX < 75; curX++){
                PosColor (curX, 15, 0);
                printf (" ");
            }
            curX = 70;
        } else {
        if (click == 1){
            click = 0;
            curX = 5;
            i = 0;
            if ((click == 0 && ifitis (i, l, deleted1) == 0)||(click == 1 && ifitis (i, m, deleted2) == 0) )
            {
            PosColor (curX, i + 35, red_text);
            printf("-");
            }
        } else initmenu (1, ingr, dish, forreck, ingred, dishes, fordish, c);
        }
        break;
   case 13:
        if (f == 0) {
                PosColor (curX, 35 + i, 0);
                printf (" ");
                PosColor (curX + 1, 35 + i, red_text);
                printf ("Deleted");
                if (click == 0){
                        deleted1[l] = i;
                        l++;
                        forreck = forreck - ingred [i];
                        }
                else {deleted2 [m] = i;
                m++;
                forreck = forreck - dishes [i];
                }
                PosColor (45, 15,0);
                printf ("        ");
                PosColor (45, 15, red_text);
                printf ("%i", forreck);
        } else {
            PosColor (0, 0, 0);
            system ("cls");
            ending (forreck);
        }
        break;
    }
}
}
void initmenu(int l, int ingr, int dish, int forreck, int ingred [], int dishes[], int fordish, char c[]){
    int curX, curY;
    int wooow_text = FOREGROUND_BLUE | FOREGROUND_GREEN |FOREGROUND_INTENSITY;
    int wow_low_text_green = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_INTENSITY;
    int blue_text_green = FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int wow_low_text = FOREGROUND_BLUE | FOREGROUND_RED;
    int wow_text = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int yellow = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int wow_low_text_yel = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED;
	for (curX = 10; curX < 70; curX++)
        for (curY = 5; curY < 10 ; curY++){
        PosColor (curX, curY, yellow);
        puts(" ");
        }
     for (curX = 9; curX < 71; curX++){
        PosColor(curX, 4, wow_text);
        printf("*");
     }
     for (curX = 9; curX < 71; curX++){
        PosColor(curX, 10, wow_text);
        printf("*");
     }
     for (curY = 5; curY < 10; curY++){
        PosColor(9, curY, wow_text);
        printf("*");
     }
     for (curY = 5; curY < 10; curY++){
        PosColor(70, curY, wow_text);
        printf("*");
     }
     PosColor (30, 7,  wow_low_text_yel);
     printf ("INTERACTIVE  MENU");
     if (l == 2)
        reckoning(ingr, dish, forreck, ingred, dishes, fordish, c);
     for (curX = 10; curX < 70; curX++)
     for(curY = 12; curY < 31; curY++){
        PosColor(curX, curY, green);
        printf (" ");
     }
     for (curX = 9; curX < 71; curX++){
        PosColor(curX, 11, wooow_text);
        printf("*");
     }
     for (curX = 9; curX < 71; curX++){
        PosColor(curX, 31, wooow_text);
        printf("*");
     }
     for (curY = 12; curY < 31; curY++){
        PosColor(9, curY, wooow_text);
        printf("*");
     }
     for (curY = 12; curY < 31; curY++){
        PosColor(70, curY, wooow_text);
        printf("*");
     }
     PosColor (12, 16, blue_text_green);
     if (l == 0)
        ingredient(ingr, dish, forreck, ingred, dishes, fordish, c);
     if (l == 1)
        dishess (ingr, dish, forreck, ingred, dishes, fordish, c);
}

void greetings () {
    int curX, curY;
    int green_text_yel = FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int yellow = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int yellow_low = BACKGROUND_GREEN | BACKGROUND_RED;
    int red = BACKGROUND_RED | BACKGROUND_INTENSITY;
    int red_low = BACKGROUND_RED;
    int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    int blue_low = BACKGROUND_BLUE;
    int wow = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int wow_low = BACKGROUND_BLUE | BACKGROUND_RED;
    int wooow = BACKGROUND_BLUE | BACKGROUND_GREEN |BACKGROUND_INTENSITY;
    int wooow_low = BACKGROUND_BLUE | BACKGROUND_GREEN;
    for (curX = 10; curX < 70; curX++)
        for (curY = 5; curY < 15 ; curY++){
        PosColor (curX, curY, yellow);
        puts(" ");
        }
    for (curX = 10; curX < 70; curX++){
        PosColor (curX, 5, wow);
        printf ("*");
        Sleep (3);
    }
    for (curY = 6; curY < 15; curY++){
        PosColor (69, curY, wow_low);
        printf ("*");
        Sleep (3);
    }
    for (curX = 69; curX > 9; curX--){
        PosColor (curX, 14, wow);
        printf ("*");
        Sleep (3);
    }
    for (curY = 13; curY > 5; curY--){
        PosColor (10, curY, wow_low);
        printf ("*");
        Sleep (3);
    }
    PosColor (37, 8, green_text_yel);
    printf("HELLO!");
    PosColor (24, 10, green_text_yel);
    printf("We are presenting the interactive menu!");
    PosColor (34, 12, green_text_yel);
    Sleep(400);
    printf (" . ");
    Sleep(400);
    printf (" . ");
    Sleep(400);
    printf (" . ");
    Sleep(400);
    printf (" . ");
    Sleep(500);
    PosColor(0,0,0);
    system("cls");
    int ingred [100];
    ingred [0] = 0;
    int dishes [25];
    dishes[0] = 0;
    int size = (char) malloc (16);
    char c [size];
    initmenu(0, 0, 0, 0, ingred, dishes, 0, c);
}

int main(void)
{
    greetings();
    return EXIT_SUCCESS;
}
