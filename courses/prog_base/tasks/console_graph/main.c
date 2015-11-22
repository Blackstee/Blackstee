#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<math.h>

void PosColor(int x, int y, int color)
{
    COORD coord = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    SetConsoleCursorPosition(hConsole, coord);
}
int main (void)
{
    int col, row, xCPos, yCPos;
    float koef;
    float curX, curY;
    int green = BACKGROUND_GREEN |BACKGROUND_INTENSITY;
    int white = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    int red = BACKGROUND_RED | BACKGROUND_INTENSITY;
    int red_text = FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE |BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
    int green_text = FOREGROUND_GREEN |BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE |BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
    int blue_text = FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE |BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;
    char znak;
    yCPos = 12;
    xCPos = 39;
    koef = 1;
    while (1)
    {
        PosColor (curX, curY, white);
        for (curX = 0; curX < 80; curX ++)
        for (curY = 0; curY < 25; curY++)
            printf(" ");
        for (curX = xCPos, curY = 0; curY < 25; curY++)
        {
            PosColor (curX, curY, blue_text);
            printf ("|");
        }
        for (curX = xCPos, curY = 0; curY < 25; curY = (curY + 1*koef))
        {
            PosColor (curX, curY, blue_text);
            printf ("+");
        }
        for (curX = 0, curY = yCPos; curX < 80; curX++)
        {
            PosColor (curX, curY, blue_text);
            printf ("-");
        }
        for (curX = 0, curY = yCPos; curX < 80; curX = (curX + 1*koef))
        {
            PosColor (curX, curY, blue_text);
            printf ("+");
        }
        for (curX = -40; curX < 40; curX += 0.01)
        {
            curY = - 0.5 * tan(curX / koef + 2) * koef;
            curX += xCPos;
            curY += yCPos;
            if (curX >= 0 && curX < 80 && curY>= 0 && curY < 25)
            {
                PosColor (curX, curY, green);
                printf (" ");
            }
            curX -= xCPos;
            curY -= yCPos;
            curY = -1 * pow ((curX / koef + 3), 3) * koef;
            curX += xCPos;
            curY += yCPos;
            if (curX >= 0 && curX < 80 && curY>= 0 && curY < 25)
            {
                PosColor (curX, curY, red);
                printf (" ");
            }
            curX -= xCPos;
            curY -= yCPos;
        }
        PosColor (0, 0, green_text);
        printf("1. F(x) = 0.5 * tg(x + 2)");
        PosColor (0, 1, red_text);
        printf("2. F(x) = (x + 3)^3)");
        PosColor (0, 2, blue_text);
        printf("Center\n Up = \"w\"      Down = \"s\" \n Right = \"d\"   Left = \"a\"\n\nScale\n  \"+\" or \"-\" ");
        curX = 0;
        curY = 24;
        znak = getch();
        switch(znak)
        {
            case 'w' : yCPos--;
            break;
            case 's' : yCPos++;
            break;
            case 'd' : xCPos++;
            break;
            case 'a' : xCPos--;
            break;
            case '+' : koef = koef * 2;
            break;
            case '-' : koef = koef * 0.5;
            break;
        }
        system("cls");
    }
    return EXIT_SUCCESS;
}
