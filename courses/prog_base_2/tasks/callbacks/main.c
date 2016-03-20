#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

typedef void (*whatCallBack) (int *, int *, int *);
int  randomness (whatCallBack cb, int  sumofnegative);
void oppositeCB (int * number1, int * number2, int * sumofnegative);
void equalsCB (int * number1, int * number2, int * sumofnegative);
int sumofnegativesforop(int number1, int number2, int sumofnegative);
int sumofnegativesforeq (int number1, int number2, int sumofnegative);

int main (void)
{
    srand (time (NULL));
    int sumofnegative = 0;
    puts ("Press any key to stop");
    whatCallBack cb = oppositeCB;
    sumofnegative = randomness(cb, sumofnegative);
    puts ("The result of randomness:");
    printf ("Sum of negative numbers from coincidences: %i\n", sumofnegative);
    puts ("Press any key to exit");
    getch ();
    return EXIT_SUCCESS;
}

int randomness (whatCallBack cb, int sumofnegative)
{
    while (!kbhit())
    {
    int number1 = rand()%200 - 100;
    Sleep(2);
    int number2 = rand()%200 - 100;
    if (number1 == number2)
        {
        whatCallBack cb = equalsCB;
        sumofnegative = sumofnegativesforeq (number1, number2, sumofnegative);
        cb (number1, number2, sumofnegative);
        }
        else if (abs(number1) == abs (number2))
                {
                whatCallBack cb = oppositeCB;
                sumofnegative = sumofnegativesforop (number1, number2, sumofnegative);
                cb (number1, number2, sumofnegative);
                }
                else puts ("No equals or opposites");
    }
    getch ();
    return sumofnegative;
}

void oppositeCB (int * number1, int * number2, int * sumofnegative)
{
    printf ("The opposite numbers: %i and %i\n", number1, number2);
}

void equalsCB (int * number1, int * number2, int * sumofnegative)
{
    printf ("The equal numbers: %i and %i\n", number1, number2);
}

int sumofnegativesforop (int number1, int number2, int sumofnegative)
{
    if (number2 < 0)
       sumofnegative += number2;
       else sumofnegative += number1;
    return sumofnegative;
}
int sumofnegativesforeq (int number1, int number2, int sumofnegative)
{
    sumofnegative += 2*number1;
    return sumofnegative;
}
