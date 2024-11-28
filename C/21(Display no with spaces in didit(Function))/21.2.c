#include<stdio.h>
int digit2(int v, int a)
{
    int ar[100000], k=0, l=a;
    for(int i=10;i<a;i=i+0)
    {
       ar[k]=a/v;
       printf("%d ", ar[k]);
       a=a%v;
       k=k+1;
       v=v/10;
    }
    printf("%d", l%10);
}
