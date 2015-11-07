#include<math.h>
#include<stdlib.h>
#include<stdio.h>


double calc (int n, int m)
{
    int i, j;                          //¬водимо л≥чильники
    double x = 0, Z = 0;               //«м≥нн≥ результату
    if (n <= 0 || m <= 0)
        return 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            Z += pow(j,2);
        }
         x += sin ((2.0 * M_PI)/(i + 1.0)) * cos (Z);
    }
    return x;
}
