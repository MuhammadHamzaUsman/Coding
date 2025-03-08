#include<iostream>
using namespace std;

int main()
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0;x < 10; x++)
        {
            if(x == 0 || x == 9 || y == 0 || y == 9)
            {
                cout << "*";
            }
            else 
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
}