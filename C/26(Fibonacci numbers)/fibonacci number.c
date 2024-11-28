#include<stdio.h>
void main()
{
    int n1 = 0, n2 = 1, no, limit;
    printf("Enter the limit : ");
    scanf("%d", &limit);
    for(int i = 1 ; i <= limit ; i = no)
    {
        no = n1 + n2;
        n2 = n1;
        n1 = no;
        if(no < limit)
            printf("%d\n", no);
    }
}
