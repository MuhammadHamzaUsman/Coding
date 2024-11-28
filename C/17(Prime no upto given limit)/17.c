#include<stdio.h>
void main ()
{
    int n;
    printf("Enter limit :");
    scanf("%d", &n);
    printf("Prime Numbers:\n");
    for(int i = 2; i<=n; i++)
    {
        for(int j =1;j<=1;j++)
        {

        }
        if(n%i==0)
        {
            printf("No : %d\n", i);
        }
    }
}
