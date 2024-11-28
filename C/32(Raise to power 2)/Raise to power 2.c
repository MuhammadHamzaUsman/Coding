#include<stdio.h>
void main()
{
    int product = 1;
    for(int i = 0 ; i <= 6 ; i++)
    {
        printf("%d\t%d\n", i, product);
        product *= 2;
    }
}
