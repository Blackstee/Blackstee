#include<math.h>

double calc (int n, int m)
{
    int n1 = n, m1 = m;                //������� ����
    int i, j;                          //������� ���������
    double x = 0, Z = 0;               //���� ����������
    if (n1 <= 0 || m1 <= 0)
        return 0;
    for (i = 1; i <= n1; i++)
    {
        for (j = 1; j <= m1; j++)
        {
            Z += pow(j,2);
        }
         x += sin ((2.0 * M_PI)/(i + 1.0)) * cos (Z);
    }
    return (double) x;
}
