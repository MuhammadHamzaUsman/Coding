#include<stdio.h>
void main ()
{
    char a, c;
    for(int i=2;i>1;i++)
    {
        a = '0';
        printf("Enter question : ");
        scanf(" %c", &a);
        if(rand()%2==1)
        {
            printf("Answer : Yes\n");
            getch();
        }
        else
        {
            printf("Answer : No\n");
            getch();
        }
        printf("Quit : Q\nEnter choice : ");
        scanf(" %c", &c);
        if(c=='Q')
        {
            i = 0;
        }
        system("cls");
    }
}
