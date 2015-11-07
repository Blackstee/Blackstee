#include<math.h>
#include<stdio.h>
#include<stdlib.h>
 enum operation{empty, Break, Return, pop, Continue, repeat};

int run(int moves[], int movesLen, int res[], int resLen)
{
movesLen = 4;
resLen = movesLen;
int i = 0;
int j = 0;
int currentState = 0;
int currentMove;
int Numbersinres = 0;
int breakquestion;
int resNumbers;

int operation[4][4] = {
    {1, repeat, 8, Break},
    {pop, 2, empty, 5},
    {6, Continue, 3, pop},
    {empty, 7, empty, 4}
};
int state[4][4] = {
    {1, 1, 0, empty},
    {3, 2, empty, 1},
    {2, 1, 3, 0},
    {empty, 3, empty, 0}
};

while (1)
{
    switch (moves[j])
    {
        case 11: currentMove = 0;
        break;
        case 19: currentMove = 1;
        break;
        case 29: currentMove = 2;
        break;
        case 209: currentMove = 3;
        break;
        default: breakquestion = 1;
        break;
    }
        if (breakquestion == 1)
            break;
switch (operation[currentState][currentMove])
			{
			case Break:
				breakquestion = 1;
				break;
			case pop:
				if (i>0)
				{
					res[i - 1] = 0;
					i--;
					j++;
					currentState = state[currentState][currentMove];
					break;
				}
				else
				{
					breakquestion = 1;
					break;
				}
			case repeat:
				currentState = state[currentState][currentMove];
				break;
			case Continue:
				j++;
				currentState = state[currentState][currentMove];
				break;
			default:
				res[i] = state[currentState][currentMove];
				i++;
				j++;
				currentState = state[currentState][currentMove];
				break;
			}
			if (breakquestion == 1)
				break;
	}
	for (i = 0; i < resLen; i++)
	{
		if (res[i] != 0)
			resNumbers++;
	}

	return resNumbers;
}
