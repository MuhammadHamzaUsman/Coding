#include<stdio.h>
int add(int a, int b)
{
    return a+b;
}
void main()
{
    int a, b;
    printf("Enter A :");
    scanf("%d", &a);
    printf("Enter B :");
    scanf("%d", &b);
    printf("Sum : %d\nAns : %d", add(a,b), mul(a,b));
}
