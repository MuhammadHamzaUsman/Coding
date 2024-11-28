#include<stdio.h>
void main()
{
    int op, sp;
    float l, p, lp, pp;
    printf("Enter original price :");
    scanf("%d", &op);
    printf("Enter sale price :");
    scanf("%d", &sp);
    if(sp>op)
        {
           p = sp-op;
           pp = p/op*100;
           printf("Profit : %.0f\nProfit percentage : %.2f", p, pp);
        }
    else if(sp<op)
        {
           l = op-sp;
           lp = l/op*100;
           printf("Loss : %.0f\nLoss percentage : %.2f", l, lp);
        }
}
