#include<stdio.h>
void main()
{
    int n1, sum, sub, mul, choice;
    float n2, div;
    printf("1.Sum\n2.Subtract\n3.Multiplication\n4.Division\nEnter your choice :");
    scanf("%d", &choice);
    if(choice==1)
    {
        printf("Enter first number :");
        scanf("%d", &n1);
        printf("Enter second number :");
        scanf("%f", &n2);
        sum = n1+n2;
        printf("Ans : %d", sum);
    }
    else if(choice==2)
    {
        printf("Enter first number :");
        scanf("%d", &n1);
        printf("Enter second number :");
        scanf("%f", &n2);
        sub = n1-n2;
        printf("Ans : %d", sub);
    }
    else if(choice==3)
    {
        printf("Enter first number :");
        scanf("%d", &n1);
        printf("Enter second number :");
        scanf("%f", &n2);
        mul = n1*n2;
        printf("Ans : %d", mul);
    }
    else if(choice==4)
    {
        printf("Enter first number :");
        scanf("%d", &n1);
        printf("Enter second number :");
        scanf("%f", &n2);
        div = n1/n2;
        printf("Ans : %.2f", div);
    }
    else
    {
        printf("Invalid choice");
    }
}

