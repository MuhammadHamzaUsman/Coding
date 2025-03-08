#include<iostream>
#include"Object.h"
using namespace std;

int main()
{
    Name name("Hamza", "Usman");
    cout << name.full_name();
    cout << name.full_name("Hamza");
    return 0;
}