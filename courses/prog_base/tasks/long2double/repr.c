double long2double(long long);
int main(){
long long a = 0;
double R;
scanf("%lld", &a);
R = long2double(a);
printf("%.325llf", R);
return 0;
}
double long2double(long long a)
{
    long long E = 0;    // Exponenta
    short L, i;         //i - lichilnyk, L - znak
    double M = 0;       // mantissa
    double Mnorm = 0;   // mantissa u normalizovanomu
    double R = 0;       //resultat
    long long num = a;  //chislo
    int n = -52;        //stepin

    //znahodjennya znaku
    if (((num>>63)&1)== 0)
        L = 0;
        else
        L =1;
    //znahodjennya exponenti
    E = num >> 52;
    E = 0x00000000000007FF & E;

    //znahodjennya mantissi
    for (i = 0; i <= 51; i++) {
        M+=(((num>>i)&1)*(pow((double)2,n)));
        n++;
    }
    //znahodjennya mantissi u normalizovanomu viglyadi
    Mnorm = M + 1.0;

    if ((E == 2047) &&  (M!=0.0)) return NAN;
    if ((E == 2047) && (M == 0.0) && (L == 1))return -INFINITY;
    if ((E == 2047) && (M == 0.0) && (L == 0))return INFINITY;
    //Normalizovane
    if ((E > 0) && (E <2047)) {R = (pow((double)-1,L)* pow((double) 2, (double) (E-1023))*Mnorm); return (double) R;}
    //Denormalizovane
    if ((E == 0) && (M != 0)) {R = (pow((double)-1, L)* pow((double) 2, -1022)*M); return (double) R;}
    if ((E == 0) && (M == 0.0) && (L == 1))return -0.0;
    if ((E == 0) && (M == 0.0) && (L == 0)) return 0.0;
}
