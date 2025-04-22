#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<array>
using namespace std;
// implement backtracking
const size_t BOARD_SIZE = 8;
void displayBoard(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &);
bool isLegalMove(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &, int, int);
int numberOfLegalMoves(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &, int, int);
bool tourComplete(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &);
int lookAhead(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &, const array<array<int, BOARD_SIZE>,BOARD_SIZE> &, int, int);

int main()
{
    array<array<int, BOARD_SIZE>,BOARD_SIZE> board = {};
    array<array<int, BOARD_SIZE>,BOARD_SIZE> accessibility = {
        {
            {2,3,4,4,4,4,3,2},
            {3,4,6,6,6,6,4,3},
            {4,6,8,8,8,8,6,4},
            {4,6,8,8,8,8,6,4},
            {4,6,8,8,8,8,6,4},
            {4,6,8,8,8,8,6,4},
            {3,4,6,6,6,6,4,3},
            {2,3,4,4,4,4,3,2}
        }
    };
    array<int, 8> horizontal = {2, 1, -1, -2, -2, -1, 1, 2};
    array<int, 8> vertical = {-1, -2, -2, -1, 1, 2, 2, 1};
    int current_row = 0;
    int current_col = 0;
    board[current_row][current_col] = 1;
    int move_number;
    int counter = 2; 

    while(counter <= BOARD_SIZE * BOARD_SIZE)
    {
        int best_move = 0;
        int smallest_access = 10;
        for(int move = 0; move < 8; move++)
        {    
            int temp_x = current_col + horizontal[move];
            int temp_y = current_row + vertical[move];
            if(isLegalMove(board, temp_x, temp_y))
            {   
                if(accessibility[temp_y][temp_x] < smallest_access)
                {
                    smallest_access = accessibility[temp_y][temp_x];
                    best_move = move;
                }

                if(accessibility[temp_y][temp_x] == smallest_access)
                {
                    if(lookAhead(accessibility, board, temp_x, temp_y) < lookAhead(accessibility, board, current_col + horizontal[best_move], current_row + vertical[best_move]))
                    {
                        smallest_access = accessibility[temp_y][temp_x];
                        best_move = move;
                    }
                }
            }
        }

        current_col += horizontal[best_move];
        current_row += vertical[best_move];
        board[current_row][current_col] = counter;
        accessibility[current_row][current_col]--;
        counter++;

        if(numberOfLegalMoves(board, current_col, current_row) == 0)
        {
            break;
        }
        displayBoard(board);
    }

    displayBoard(board);
    return 0;
}

void displayBoard(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &array2d)
{
    cout << "\033[1;0H";
    static string numbers = "0123456789";
    string output = "";
    for(auto &row : array2d)
    {
        for(auto col : row)
        {
            if(col < 10)
            {
                output = output + "0" + numbers[col] + " ";
            }
            else
            {
                output = output + numbers[col / 10] + numbers[col % 10] + " ";
            }
        }
        output += "\n";
    }

    cout << output << endl;
}

bool isLegalMove(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &board, int x, int y)
{
    if((x >= 0 && x < :: BOARD_SIZE) && (y >= 0 && y < :: BOARD_SIZE))
    {
        if(board[y][x] == 0)
        {
            return true;
        }
    }
    return false;
}

int numberOfLegalMoves(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &board, int x, int y)
{
    static array<int, 8> horizontal = {2, 1, -1, -2, -2, -1, 1, 2};
    static array<int, 8> vertical = {-1, -2, -2, -1, 1, 2, 2, 1};
    int legal_moves = 0;

    for(size_t move = 0; move < 8; move++)
    {
        int temp_x = x + horizontal[move];
        int temp_y = y + vertical[move];
        if(isLegalMove(board, temp_x, temp_y))
        {
            legal_moves++;
        }
    }

    return legal_moves;
}

bool tourComplete(const array<array<int, BOARD_SIZE>,BOARD_SIZE> &board)
{
    for(auto &row : board)
    {
        for(int col : row)
        {
            if(col == 0)
            {
                return false;
            }
        }
    }
    return true;
}

int lookAhead(const array<array<int, BOARD_SIZE>, BOARD_SIZE> &accessibility, const array<array<int, BOARD_SIZE>, BOARD_SIZE> &board, int x, int y)
{
    array<int, 8> horizontal = {2, 1, -1, -2, -2, -1, 1, 2};
    array<int, 8> vertical = {-1, -2, -2, -1, 1, 2, 2, 1};
    int smallest_access = 10;
    for(int move = 0; move < 8; move++)
    {    
        int temp_x = x + horizontal[move];
        int temp_y = y + vertical[move];
        if(isLegalMove(board, temp_x, temp_y))
        {   
            if(accessibility[temp_y][temp_x] < smallest_access)
            {
                smallest_access = accessibility[temp_y][temp_x];
            }
        }
    }

    return smallest_access;
}