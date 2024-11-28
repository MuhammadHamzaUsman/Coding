#include<stdio.h>
void main()
{
    for(int i = 2; i<=100; i++)
    {
        for(int a =1; a<=10; a++)
        {
            printf("%dx%d=%d\n", i, a, i*a);
        }
        printf("\n");
    }
}
