#include <iostream>
using namespace std;

int main ()
{
    int row = 5;
    int no_of_stars = 1;
    int no_of_spaces = row - 1;
    for(int i = 1;i <= row; i++)
    {
        for(int j = 1; j <= no_of_spaces; j ++)
        {
            cout << " ";
        }
        for(int j = 1; j <= no_of_stars;j ++)
        {
            cout << "*";
        }
        no_of_stars += 2;
        no_of_spaces -= 1;
        cout << endl;
    }
    return 0;
}