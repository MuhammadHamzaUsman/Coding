#include<stdio.h>
void main ()
{
    int choice;
    float l, w, h, triangle, parallelogram, trapezium, rhombus;
    printf("1.Triangle\n2.Parallelogram\n3.Rhombus\n4.Trapezium\nEnter your choice :");
    scanf("%d", &choice);
    if(choice==1)
    {
        printf("Enter length :");
        scanf("%f", &l);
        printf("Enter width :");
        scanf("%f", &w);
        triangle = (l*w)/2;
        printf("Area : %.2f", triangle);
    }
    else if(choice==2)
    {
        printf("Enter length :");
        scanf("%f", &l);
        printf("Enter width :");
        scanf("%f", &w);
        parallelogram = l*w;
        printf("Area : %.2f", parallelogram);
    }
    else if(choice==3)
    {
        printf("Enter length :");
        scanf("%f", &l);
        printf("Enter width :");
        scanf("%f", &w);e
        rhombus = (l*w)/2;
        printf("Area : %.2f", rhombus);
    }
    else if(choice==4)
    {
        printf("Enter length :");
        scanf("%f", &l);
        printf("Enter width :");
        scanf("%f", &w);
        printf("Enter heigth :");
        scanf("%f", &h);
        trapezium = ((l+w)/2)*h;
        printf("Area : %.2f", trapezium);
    }
    else
        printf("Invalid choice");
}
