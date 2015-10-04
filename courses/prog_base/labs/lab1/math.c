
#include <math.h>


double calc(double x, double y, double z) {
   double a;
   if (x==abs(y) || z==0 ||  sin(x)==0)
   return NAN;
   else a=pow(x,y+1)/pow(x-y,1/z)+y/((9+1)*abs(x+y))+pow(abs(cos(y)/sin(x)+1),0.5);
   return a;
}
