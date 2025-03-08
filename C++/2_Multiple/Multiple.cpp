#include<iostream>
using namespace std;

int main() 
{
    int number, multiple;
    cout << "Enter Number: " ;
    cin >> number ;
    cout << "Enter a Number to check it is Multiple of Above: " ;
    cin >> multiple ;
    if (multiple % number == 0)
    {
        cout << number << "x" << multiple / number << "=" << multiple;
    }
    else 
    {
        cout << multiple << " is not multiple of " << number;
    }
    return 0;
}