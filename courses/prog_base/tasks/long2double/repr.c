
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main (){
    long long a; //number
    short L, i;  //i - lichilnyk, L - znak
    double M, R; // M - mantisa, R - result
    int E;       // E - exponenta
    a = 4620000000000000000;
    if ((a>>63)==0){
        L = 0;
        E = (a>>52);
    }
    else {
        L=1;
        E = abs((a>>52)+1);
    }
    for (i = 51; i >= 0; --i) {
        M+=(((a>>i)&1)*(pow(2, i - 52)));
    }
    if ((E == 2047) &&  (M!=0.0)) return printf ("R = NaN");
    if ((E == 2047) && (M == 0.0) && (L == 1) )return printf ("R = -Infinity");
    if ((E == 2047) && (M == 0.0) && (L == 0))return printf ("R = Infinity");
    if ((E > 0) && (E <2047)) {R = (pow(-1,L)* pow(2,E-1023)*(1+M));
                printf("%.20llf", R);}
    if ((E == 0) && (M !=0.0)) {R = (pow(-1, L)* pow(2, -1022)*(M));
                    printf("%.325llf", R);}
    if ((E == 0) && (M == 0.0) && (L == 1))return printf("R = -0");
    if ((E == 0) && (M == 0.0) && (L == 0)) return printf ("R = 0");

}
