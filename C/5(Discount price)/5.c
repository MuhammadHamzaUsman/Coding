
#include<stdio.h>
void main()
{
    int price, discount, discount_price, final_price;
    printf("Enter original price of shirt :");
    scanf("%d", &price);
    printf("Enter discount percentage :");
    scanf("%d", &discount);
    discount_price = (price*discount)/100;
    final_price = price- discount_price;
    printf("Original price : %dRs\n", price);
    printf("Discount on price : %dRs\n", discount_price);
    printf("Price after discount : %dRs", final_price);
}
