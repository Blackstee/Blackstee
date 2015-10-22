#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void fillRand(int mat[4][4])
{
    int i, j;                        //lichiniky

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
           mat [i][j] = rand()%2000 - 1000;
    }
}


void rotateCCW90(int mat[4][4])
{
    int rot [4][4];                  //matrix
    int i, j;                        //lichiniky

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            rot[i][j] = mat[j][3-i];
    }
}


void flipV(int mat[4][4])
{
    int flipV [4][4];                //matrix
    int i, j;                        //lichiniky

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            flipV[i][j] = mat[3-i][j];
    }
}


void transposSide(int mat[4][4])
{
    int transside [4][4];            //matrix
    int i, j;                        //lichiniky

    for (i = 0; i < 4; i++)
    {
    for (j = 0; j < 4; j++)
            transside[i][j] = mat[3-j][3-i];
    }
}
