#include<stdio.h>
void main()
{
    int choice;
    float volume;
    printf ("Find volume\n");
    printf ("1.Cube\n2.Cylinder\n3.Sphere\nEnter your choice:");
    scanf ("%d" , &choice);
    if (choice == 1)
    {
    float length;
    printf("Enter length: ");
    scanf ("%f",&length);
    volume = length*length*length;
    printf("volume is %f", volume);
    }
    else if (choice == 2)
    {
    float length1, radius1;
    printf("Enter length:");
    scanf ("%f",&length1);
    printf("Enter radius:");
    scanf ("%f",&radius1);
    volume = 3.142*radius1*radius1*length1;
    printf("volume is %f", volume);
    }
    else if (choice == 3)
    {
    float radius;
    printf("Enter radius: ");
    scanf ("%f",&radius);
    volume = 3.142*radius*radius*radius;
    printf("volume is %f", volume);
    }
    else
         printf("Invalid Choice");
}
