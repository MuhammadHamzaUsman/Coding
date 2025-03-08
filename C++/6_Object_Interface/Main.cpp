#include<iostream>
#include"Class.h"
using namespace std;

int main()
{
    Date d1(12,01,2025);
    d1.display();
    d1.setDate(-90);
    d1.setDate(90);
    d1.setMonth(-90);
    d1.setMonth(90);
    d1.setYear(-90);
    d1.display();
    d1.setDate(9);
    d1.setMonth(9);
    d1.setYear(2024);
    d1.display();
    return 0;
}