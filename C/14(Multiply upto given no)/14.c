#include<stdio.h>
void main()
{
    int no , no2;
    printf("Enter no :");
    scanf("%d", &no);
    printf("Enter last multiplier :");
    scanf("%d", &no2);
    for(int x=1;x<=no2;x++)
    {
        printf("%dx%d=%d\n", no, x, x*no);
    }
}
