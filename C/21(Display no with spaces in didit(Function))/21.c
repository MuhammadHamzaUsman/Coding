#include<stdio.h>
int digit(int a)
{
    int c=1,v=1,r=1;
    for(int i=10;i<a;i=i*10)
    {
        if(a/i>0)
        {
            c=c+1;
        }
    }
    printf("%d\n", c);
    for(int i1=1;i1<c;i1++)
    {
        v=(v*10);
    }
    printf("%d\n", v);
    digit2 (v,a);
}
