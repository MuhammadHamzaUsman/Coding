#include<stdio.h>
void main()
{
    int n1, n2, choice;
    printf("Enter two numbers : ");
    scanf("%d%d", &n1, &n2);
    printf("1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\nEnter choice : ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1 :
            printf("Result : %d", n1+n2);
            break;
        case 2 :
            printf("Result : %d", n1-n2);
            break;
        case 3 :
            printf("Result : %d", n1*n2);
            break;
        case 4 :
            if(n1>n2)
            {
                printf("Result : %d", n1/n2);
            }
            else
                printf("Result : %d", n2/n1);
            break;
        default :
            printf("Wrong Choice");
    }

}
