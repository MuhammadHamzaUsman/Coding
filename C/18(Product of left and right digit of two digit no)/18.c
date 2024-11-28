#include<stdio.h>
void main()
{
    int no, l_no, r_no, product;
    printf("Enter two digit no : ");
    scanf("%d", &no);
    l_no = no/10;
    r_no = no%10;
    product = l_no*r_no;
    printf("Left digit : %d\nRight digit : %d\nProduct : %d", l_no, r_no, product);
}
