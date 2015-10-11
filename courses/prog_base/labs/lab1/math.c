#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(double, double, double);

int main() {
    double xval = 6, yval = -5, zval = 47;
    double result;
int t = cos(M_PI/2.0)/(sin(M_PI/2.)+1);

    result = calc(xval, yval, zval);

    printf("%.12f", result);
    return 0;
}
double calc(double x, double y, double z) {

   double a;
   if (x==abs(y) || z==0 ||  sin(x)==0)
   return NAN;
   else a=pow(x,y+1)/pow(x-y,1/z)+y/((9+1)*abs(x+y))+pow(abs(t),0.5);
   return a;
}
