#include<stdio.h>
void main ()
{
    int int2, choice;
    float int1, sum ,sub, div, mul;
    printf("Enter integer 1 :");
    scanf("%f", &int1);
    printf("Enter integer 2 :");
    scanf("%d", &int2);
    printf("1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\nEnter your choice :");
    scanf("%d", &choice);
    if(choice==1)
    {
        sum = int1+int2;
        printf("Ans : %f", sum);
    }
    else if(choice==2)
    {
        sub = int1-int2;
        printf("Ans : %f", sub);
    }
    else if(choice==3)
    {
        mul = int1*int2;
        printf("Ans : %f", mul);
    }
    else if(choice==4)
    {
        div = int1/int2;
        printf("Ans : %f", div);
    }
    else
      printf("Invalid choice");
}
