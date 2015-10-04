#include <math.h>
int exec(int op, int a, int b) {
   int result;
   int t;
   if (op < 0)
    {a = t;
     a = b;
     b = t;}
   switch(abs(op))
   {
   case 0: result = -a;
   break;
   case 1: result = a + b;
   break;
   case 2: result = a - b;
   break;
   case 3: result  = a * b;
   break;
   case 4: if (b == 0)
   return 0;
   else
   result = a / b;
   break;
   case 5: result = abs (a);
   break;
    case 6: result = pow(a,b);
   break;
   case 7:
    case 13:
    case 77: if (b == 0)
    return 0;
    else
    result = a % b;
    break;
   case 8: result = (a<=b)? b:a;
   break;
   case 9: result = (a<=b)? a:b;
   break;
   case 10: switch (abs(b)%8){
                case 0: result = abs (a) * sizeof(char);
                break;
                case 1: result = abs (a) * sizeof(signed char);
                break;
                case 2: result = abs (a) * sizeof(short);
                break;
                case 3: result = abs (a) * sizeof(unsigned int);
                break;
                case 4: result = abs (a) * sizeof(long);
                break;
                case 5: result = abs (a) * sizeof(unsigned long long);
                break;
                case 6: result = abs (a) * sizeof(float);
                break;
                case 7: result = abs (a) * sizeof(double);
                break;
                }
             break;
  case 11: if (a == 1)
  return 0;
  else
  result = roundl((9 + 1) * cos (b * M_PI)/(a - 1));
  break;
  default: if (op < 100)
  result = ( op % abs(a + 1)) + (op % abs (b + 1));
  else
  result = -1;
   }
   return result;
}
