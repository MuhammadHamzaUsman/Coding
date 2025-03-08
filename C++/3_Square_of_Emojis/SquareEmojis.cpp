#include<iostream>
using namespace std;

int main() 
{
    int width = 10, height = 10;
    int x_end =  width - 1, y_end = height - 1;
    int x_start = width - x_end , y_start = height - y_end;
    for(int y = 0 ; y <= height ; y++)
    {
        for(int x = 0 ; x <= width ; x++)
        {
            if((x >= x_start && x <= x_end && y >= y_start && y <= y_end) && ((x == x_start || x == x_end) || (y == y_start || y == y_end)))
            {
                cout << "🟫";
            }
            else
            {
                cout << "⬛ ";
            }
        }
        cout << endl;
    }
    return 0;
}