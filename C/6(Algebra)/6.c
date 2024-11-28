#include<stdio.h>
void main()
{
    int x, y, z;
    printf("Enter x :");
    scanf("%d", &x);
    printf("Enter z :");
    scanf("%d", &z);
    y = x+(3*z)/2+z*z*z+x/z;
    printf("Ans is : %d ", y);
}
