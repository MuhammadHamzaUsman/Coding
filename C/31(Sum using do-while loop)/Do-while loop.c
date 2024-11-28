#include<stdio.h>
void main()
{
    int i = 1,total = 0 ,n;
    do
    {
        printf("Exit : 0-15\nEnter number : ");
        scanf("%d", &n);
        total = total + n;
        i++;
    }while(n <= 0 || n >=15);
    printf("Sum : %d", total);
}
