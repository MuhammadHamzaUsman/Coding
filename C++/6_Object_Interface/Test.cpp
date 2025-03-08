#include<iostream>
using namespace std;

int main()
{
    unsigned int pass = 0, fail = 0;
    int input;
    cout << "Result: \n\tPass: 1\n\tFail: 2\n";
    cout << "Enter Result/Quit(-1): ";
    cin >> input;
    while(input != -1)
    {
        if(input == 1)
        {
            pass++;
        }
        else if (input == 2)
        {
            fail++;
        }
        cout << "Enter Result/Quit(-1): ";
        cin >> input;
    }
    cout << "Pass: " << pass << "\nFail: " << fail;
    if(pass > 8)
    {
        cout << "\nBonus to instructor!";
    }
}