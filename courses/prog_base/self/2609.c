#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
int h,m,code;
float f;
printf("vvedit kod, godiny i hv");
scanf ("%d %d %d", &code, &h, &m);
switch (code)
{
case 44: f=0.44*(h*60+m);
printf("vartist %f", f);
break;
case 37: f=1.05*(h*60+m);
printf("vartist %f", f);
break;
case 666:
printf("vartist 0");
break;
case 1: f=30*(h*60+m);
printf("vartist %f", f);
break;
default: f=1*(h*60+m);
printf("vartist %f", f);
break;
}
return 0;
}
