#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void fillRand1(int arr[], int size)    //[1..99]
{
    srand(time(NULL));
    int i;
    for(i = 0; i < size; i++)
        arr[i] = rand()%99;
}
int checkRand1(int arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(arr[i] > 99 || arr[i] < 1)
            return 0;
    }
    return 1;
}
float meanValue(int arr[], int size)   //seredne arifmetichne
{
    int i;
    double ser = 0.0;
    for(i = 0; i < size; i++)
    {
      ser += arr[i];
    }
    ser = ser/(double)size;
    return ser;
}
int maxValue(int arr[], int size)     //max
{
    int i;
    int max = arr [0];
    for(i = 0; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}
int meanIndex(int arr[], int size)      //index pershogo najblizchogo do serednogo
{
    int i;
    int index = 0;
    double ser = 0.0;
    double delta = abs((double)arr[0]-ser);
    for(i = 0; i < size; i++)
    {
      ser += arr[i];
    }
    ser = ser/(double)size;
    for(i = 1; i < size; i++)
    {
        if(abs((double)arr[i] - ser) < delta)
        {
            delta = abs((double)arr[i] - ser);
            index = i;
        }

    }
    return index;
}
int maxIndex(int arr[], int size)       //index pershogo max
{
    int i;
    int max = arr[0];
    int index = 0;
    for(i = 1; i < size; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            index = i;
        }
    }
    return index;
}
int maxOccurance(int arr[], int size)   //najchastishe, max
{
     int i;
     int k;
     int number = arr[0];
     int frequency;
     int max_frequency = 1;
     for (i = 0; i < (size); i++)
     {
         frequency = 1;
         for(k = i + 1; k < size; k++)
         {
             if(arr[i] == arr[k])
                frequency ++;
         }
         if (frequency >= max_frequency)
         {
                 max_frequency = frequency;
                 if (arr[i] > number)
                 number = arr[i];
         }
      }
      return number;
}
int diff(int arr1[], int arr2[], int res[], int size) //(riznitsa == 0) {1}, (!= 0) {0}
{
     int i;
     for(i = 0; i < size; i++)
     {
        res[i] = arr1[i] - arr2[i];
        if (res[i] != 0)
          return 0;
     }
     return 1;
}
void sub(int arr1[], int arr2[], int res[], int size) //risnitsa
{
     int i;
     for(i = 0; i < size; i++)
        res[i] = arr1[i] - arr2[i];
}
int gteq(int arr1[], int arr2[], int size)            //(greater or equals) {1} else {0}
{
     int i;
     for(i = 0; i < size; i++)
        if (arr1[i] < arr2[i])
        return 0;
     return 1;
}
void lor(int arr1[], int arr2[], int res[], int size) //logical OR
{
     int i;
     for(i = 0; i < size; i++)
        res[i] = arr1[i] || arr2[i];
}
