#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define COLOR 36
#define BLACK 0

void PosColor(int x, int y, int color);

int main(void)
{
    int wow_text = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    int green = FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN |BACKGROUND_RED | BACKGROUND_INTENSITY;
    int white =  BACKGROUND_BLUE | BACKGROUND_GREEN |BACKGROUND_RED | BACKGROUND_INTENSITY;
    int i = 50, j = 75, speed = 1, point = 0, n = 1, number = 0, move, l, k, x, y, pause;
    int matrix[100][150];
    PosColor(3, 2, green);
    printf("Please, set the size of your console 120X150 and press any key");
    getch();
    move = 2;
    for (y = 0; y < 100; y++)
      for (x = 0; x < 150; x++)
        {
        PosColor(x, y, white);
        printf(" ");
        }
    PosColor(3, 2, green);
    printf("Please, enter the number (1 - 10) to change the speed; enter 's' to choose iteration; <Enter> to stop or to continue; <Esc> to exit.");
    matrix[i][j] = COLOR;
 while(1){
       if (kbhit())
    switch(getch()){
    case '1': speed = 1;
            break;
    case '2': speed = 2;
            break;
    case '3': speed = 4;
            break;
    case '4': speed = 8;
            break;
    case '5': speed = 16;
            break;
    case '6': speed = 32;
            break;
    case '7': speed = 64;
            break;
    case '8': speed = 128;
            break;
    case '9': speed = 256;
            break;
    case 13: getch();
            break;
    case 27: exit(0);
            break;
    case 's': PosColor(3, 3, green);
              printf("Please, enter the number of iteration>> ");
              scanf("%i", &number);
              PosColor(3, 3, white);
              printf("                                             ");
             break;
       }
    if (i == 100 || i == 0 || j == 150 ||  j == 0)
        break;
    if (point < number)
        pause = 0;
    else
        pause = 1;
    if (matrix[i][j] == COLOR)
        {
          matrix[i][j] = BLACK;
          PosColor(j, i, wow_text);
          printf("#");
          usleep(pause * 200000 / speed);
          PosColor(j, i, matrix[i][j]);
          printf(" ");
        if (move == 1){
            move = 2;
            i--;
        }
        else
        if(move == 2){
            move = 3;
            j++;
        }
        else
        if(move == 3){
            move = 4;
            i++;
        }
        else
        if (move == 4){
            move = 1;
            j--;
        }
}
     if (matrix[i][j] == BLACK)
        {
            matrix[i][j] = COLOR;
            PosColor(j, i, wow_text);
            printf("#");
            usleep(pause * 200000 / speed);
            PosColor(j, i, matrix[i][j]);
            printf(" ");
       if (move == 1){
            move = 4;
            i++;
       }
       else
        if(move == 4){
            move = 3;
            j++;
        }
        else
        if(move == 3){
            move = 2;
            i--;
        }
        else
         if (move == 2){
            move = 1;
            j--;
        }
     }
     point++;
 }
    return EXIT_SUCCESS;
}
void PosColor(int x, int y, int color)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    SetConsoleCursorPosition(hConsole, coord);
}
