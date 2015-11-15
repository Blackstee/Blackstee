#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

void ConsoleColor(int curColPos)
{
    int color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(curColPos == 0)
        color = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    else if(curColPos == 1)
        color = BACKGROUND_RED | BACKGROUND_GREEN| BACKGROUND_INTENSITY;
    else if(curColPos == 2)
        color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole, color);
}

COORD Left (COORD pos, int border)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1)
    {
        int curColPos;
        if (pos.X == border)
            break;
        SetConsoleCursorPosition(hConsole, pos);
        curColPos = abs((pos.X - pos.Y) % 3);
        if(pos.Y > pos.X)
            curColPos = 2 - abs((pos.X - pos.Y - 2) % 3);
        ConsoleColor(curColPos);
        printf("*");
        Sleep(10);
        pos.X--;
    }
    return pos;
}
COORD Up (COORD pos, int border)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1)
    {
        int curColPos;
        if (pos.Y == border)
            break;
        SetConsoleCursorPosition(hConsole, pos);
        curColPos = abs((pos.X - pos.Y) % 3);
        if(pos.Y > pos.X)
            curColPos = 2 - abs((pos.X - pos.Y - 2) % 3);
        ConsoleColor(curColPos);
        printf("*");
        Sleep(10);
        pos.Y--;
    }
    return pos;

}
COORD Right (COORD pos, int border)
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1)
    {
        int curColPos;
        if (pos.X == border)
            break;
        SetConsoleCursorPosition(hConsole, pos);
        curColPos = abs((pos.X - pos.Y) % 3);
        if(pos.Y > pos.X)
            curColPos = 2 - abs((pos.X - pos.Y - 2) % 3);
        ConsoleColor(curColPos);
        printf("*");
        Sleep(10);
        pos.X++;
    }
    return pos;
}
COORD Down (COORD pos, int border)
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (1)
    {
        int curColPos;
        if (pos.Y == border)
            break;
        SetConsoleCursorPosition(hConsole, pos);
        curColPos = abs((pos.X - pos.Y) % 3);
        if(pos.Y > pos.X)
            curColPos = 2 - abs((pos.X - pos.Y - 2) % 3);
        ConsoleColor(curColPos);
        printf("*");
        Sleep(10);
        pos.Y++;
    }
    return pos;
}
int main()
{
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, leftB, rightB, upB, downB;
    leftB = 11;
    rightB = 67;
    upB = 11;
    downB = 13;
    pos.Y = 12;
    pos.X = 66;
    for (i = 0; i < 12; i++)
    {
        pos = Left (pos, leftB);
        leftB--;
        pos = Up (pos, upB);
        upB--;
        pos = Right (pos, rightB);
        rightB++;
        pos = Down (pos, downB);
        downB++;
    }
        pos = Left (pos, leftB);
        leftB--;
        if (leftB == 0)
      {
        printf("*");
      }
    pos.X = 0;
    pos.Y = 25;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}
