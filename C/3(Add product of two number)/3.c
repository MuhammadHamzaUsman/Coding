#include<stdio.h>
#include<math.h>
void main()
{
    int a, b , c , d, e, f;
    printf("Enter a :");
    scanf("%d", &a);
    c = a*a;
    printf("Enter b :");
    scanf("%d", &b);
    d = b*b;
    e = 2*a*b;
    printf("%d+%d+%d \n", c, e, d);
    f = c+d+e;
    printf("%d", f);
}

