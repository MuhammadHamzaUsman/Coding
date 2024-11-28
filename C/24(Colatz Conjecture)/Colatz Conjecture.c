#include<stdio.h>
#include<conio.h>
#include<dos.h>
void main()
{
    unsigned long int x = 1;
    int max = 2, m_max = 0 , m_iteration = 1 , iteration = 1, loop_limit = 1 , reset = 49;
    for(int x = 1 ; x <= 10 ; x++)
    // reset == 49
    {
        max = 0 , iteration = 1 ;
        //printf("Enter number : ");
        //scanf("%d", &x);
        for(int i=1;loop_limit < 2;i++)
        {
            iteration += 1;
            if(max<x)
            {
                max = x;
            }
            printf("Colatz[%lu]= ", x);
            if(x%2==1)
            {
                x = 3*x+1;
            }
            else if(x%2==0)
            {
                x = x/2;
            }
            printf("%lu\n", x);
            if(x==1)
            {
                //printf("Iterations : %d\nLargest number : %d\n", iteration-1, max);
                loop_limit += 1;
            }
        }
        //printf("RESET");
        //reset = getch();
        system("cls");
        loop_limit = 1;
        if(m_iteration < iteration)
        {
            m_iteration = iteration;
        }
        if(m_max < max)
        {
            m_max = max;
        }
    }
}
