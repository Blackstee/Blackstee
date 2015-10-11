#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int satisfies(int, int, int);

int main() {
    int aval = 0, bval = 0, cval = 0;
    int resultVal;

    resultVal = satisfies(aval, bval, cval);

    printf("%i", resultVal);
    return 0;
}

int satisfies(int a, int b, int c) {
   int result, modmin, sum2, min, max;
   if (a<0 && b<0 && c<0)
   {if (a<=b && a<=c)
   {modmin=abs(a);
   sum2=b+c;}
      else {
            if (b<=c && b<=a)
            {modmin=abs(b);
            sum2=a+c;}
                else
                    {modmin=abs(c);
                    sum2=a+b;}}
    if (sum2<-256 && (int)(log2(modmin))%1==0 && modmin<256)
    result=1;
    else
        if ((abs(sum2)-modmin)<16 || abs(sum2)<16)
            result=1;
}
 if (a>=0 && b>=0 && c>=0)
 {
     if (a>b && a>c)
        max=a;
     else
        {if (b>a && b>c)
        max=b;
        else
            max=c;
     }
    if (a<b && a<c)
        min=a;
    else
    {
        if (b<a && b<c)
            min=b;
        else min=c;
    }
    if (pow(max,min)<32767 && pow(max,min)>-32768)
     result=1;
     else
        result = 0;
    }
else {if (a<0 && a>-256 && b>=0 && c>=0)
            result=1;
    else {
        if (a>=0 && b>-256 && b<0 && c>=0)
                result=1;
        else {
                if (a>=0 && c>-256 && b>=0 && c<0)
                result=1;

          else {
            if (a<0 && b<0 && 10*(a+b)>-256)
               result=1;
             else {
                if (a<0 && c<0 && 10*(a+c)>-256)
                        result=1;
                 else {
                    if (b<0 && c<0 && 10*(b+c)>-256)
                        result=1;
                        else
                            result=0;
                      }
                  }
               }
            }
       }
    }
   return result;
}
