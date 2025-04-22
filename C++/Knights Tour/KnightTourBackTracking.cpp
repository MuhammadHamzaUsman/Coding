#include<iostream>
#include<fstream>
#include<vector>
#include<array>
using namespace std;

int main()
{
    knightTourBackTracking(0,0);
    return 0;
}

int function = 0;
fstream outfile("C:\\Users\\Dell\\Documents\\VSCODE\\C++\\tglog.txt");

const size_t BOARD_SIZE = 8;
enum class MOVE_STATUS {
    TOUR_COMPLETE = 1,
    VALID_MOVE = 2,
    END_REACHED = 3
};
const array<array<int, 2>, 8> KNIGHTS_MOVE = {{
    {+2, -1}, // right up
    {+1, -2}, // up right
    {-1, -2}, // up left
    {-2, -1}, // left up
    {-2, +1}, // left down
    {-1, +2}, // down left
    {+1, +2}, // down right
    {+2, +1}  // right down
}};
vector<array<int, 2>> moves_made = {};

int numberOfLegalMoves(int, int, const vector<array<int, 2>> &);
bool isLegalMove(int, int, const vector<array<int, 2>> &);
bool isCellEmpty(int, int, const vector<array<int, 2>> &);
bool isOnBoard(int, int);
bool isTourComplete(const vector<array<int, 2>> &);
void displayVector(const vector<array<int, 2>> &);
void writevector(const vector<array<int, 2>> &);
void displayChessBoard(const vector<array<int, 2>> &);
string numberToString(int number);
MOVE_STATUS knightTourBackTrackingEngine(int, int);
MOVE_STATUS knightTourBackTracking(int, int);

MOVE_STATUS knightTourBackTracking(int x, int y)
{
    array<int, 2> temp = {0,0};
    :: moves_made.push_back(temp);
    MOVE_STATUS result = knightTourBackTrackingEngine(0, 0);
    cout << "\n\n\n";
    displayVector(:: moves_made);   
    return result;
}

MOVE_STATUS knightTourBackTrackingEngine(int x, int y)
{
    // displayChessBoard(:: moves_made);
    // cout << "\n" << ++:: function;
    // writevector(:: moves_made);
    // :: outfile << "fun in\n";
    if(isTourComplete(:: moves_made))
    {
        // cout << "\n" << --:: function;
        // :: outfile << "func out: tour comp\n";
        return MOVE_STATUS :: TOUR_COMPLETE;
    }
    else
    {
        if(numberOfLegalMoves(x, y, :: moves_made) == 0)
        {
            // cout << "\n" << --:: function;
            // :: outfile << "func out: no legal move\n";
            return MOVE_STATUS :: END_REACHED;
        }
        else
        {
            for(auto move : :: KNIGHTS_MOVE)
            {
                int temp_x = x + move[0];
                int temp_y = y + move[1];
                if(isLegalMove(temp_x, temp_y, :: moves_made))
                {
                    // :: outfile << "x: " << x << " y:" << y << " tx: " << temp_x << " ty:" << temp_y << "\n";
                    moves_made.push_back({{temp_x, temp_y}});
                    MOVE_STATUS temp_result = knightTourBackTrackingEngine(temp_x, temp_y);
                    if(temp_result == MOVE_STATUS :: END_REACHED)
                    {
                        :: moves_made.pop_back();
                    }
                    else if(temp_result == MOVE_STATUS :: TOUR_COMPLETE)
                    {
                        // cout << "\n" << --:: function;
                        // :: outfile << "func out tour comp for\n";
                        return MOVE_STATUS :: TOUR_COMPLETE;
                    }
                }
            }
        }
    }
    // cout << "\n" << --:: function;
    // :: outfile << "func out: end\n";
    return MOVE_STATUS :: END_REACHED;
}

void displayVector(const vector<array<int, 2>> &vec)
{
    for(auto move : vec)
    {
        cout << "\n{x: " << move[0] << " y: " << move[1] << "}, ";
    }
}   

bool isTourComplete(const vector<array<int, 2>> &moves_made)
{
    // :: outfile << "|moves made: " << moves_made.size() << "|\n";
    if(moves_made.size() == BOARD_SIZE * BOARD_SIZE)
    {
        return true;
    }

    return false;
}

bool isOnBoard(int x, int y)
{
    if((x >= 0 && x < BOARD_SIZE) && (y >= 0 && y < BOARD_SIZE))
    {
        return true;
    }

    return false;
}

bool isCellEmpty(int x, int y, const vector<array<int, 2>> &moves_made)
{
    for(auto move : moves_made)
    {
        if(move[0] == x && move[1] == y)
        {
            return false;
        }
    }

    return true;
}

bool isLegalMove(int x, int y, const vector<array<int, 2>> &moves_made)
{
    if(isCellEmpty(x, y, moves_made) && isOnBoard(x, y))
    {
        return true;
    }

    return false;
}

int numberOfLegalMoves(int x, int y, const vector<array<int, 2>> &moves_made)
{
    int legal_moves = 0;

    for(auto move : ::KNIGHTS_MOVE)
    {
        int temp_x = x + move[0];
        int temp_y = y + move[1];
        if(isLegalMove(temp_x, temp_y, moves_made))
        {
            legal_moves++;
        }
    }

    return legal_moves;
}

void writevector(const vector<array<int, 2>> &vec)
{
    for(auto move : vec)
    {
        // :: outfile << "\n{x: " << move[0] << " y: " << move[1] << "}, ";
    }
}

void displayChessBoard(const vector<array<int, 2>> &vec)
{
    array<array<int, BOARD_SIZE>, BOARD_SIZE> board = {};

    cout << "\033[1;0H";

    for(size_t cord_index = 0; cord_index < vec.size(); cord_index++)
    {
        const array<int, 2> &cord = vec[cord_index];
        board[cord[1]][cord[0]] = cord_index + 1;
    }

    string output = "";
    for(const auto &row : board)
    {
        for(int col : row)
        {
            if(col < 10)
            {
                output = output + '0' + numberToString(col) + "  ";
            }
            else
            {
                output = output + numberToString(col) + "  ";
            }
        }
        output += "\n";
    }

    cout << output;
}

string numberToString(int number)
{
    string result = "";
    if(number > 0)
    {
        while(number > 0)
        {
            result.insert(result.begin(), number % 10 + '0');
            number /= 10;
        }
        return result;
    }
    else
    {
        return "0";
    }
        
}

// first answer
// took very long time 
// {x: 4 y: 3}, 
// {x: 3 y: 1}, 
// {x: 1 y: 0},
// {x: 0 y: 2},
// {x: 2 y: 1},
// {x: 0 y: 0},
// {x: 1 y: 2},
// {x: 0 y: 4}, 
// {x: 1 y: 6},
// {x: 3 y: 7},
// {x: 5 y: 6}, 
// {x: 7 y: 7},
// {x: 6 y: 5},
// {x: 5 y: 7}, 
// {x: 7 y: 6},
// {x: 6 y: 4},
// {x: 7 y: 2},
// {x: 6 y: 0}, 
// {x: 5 y: 2}, 
// {x: 4 y: 0}, 
// {x: 6 y: 1},
// {x: 7 y: 3},
// {x: 5 y: 4}, 
// {x: 7 y: 5},
// {x: 6 y: 7}, 
// {x: 4 y: 6},
// {x: 2 y: 7},
// {x: 0 y: 6}, 
// {x: 1 y: 4},
// {x: 3 y: 5},
// {x: 4 y: 7}, 
// {x: 6 y: 6},
// {x: 7 y: 4},
// {x: 5 y: 5}, 
// {x: 3 y: 6},
// {x: 1 y: 7},
// {x: 0 y: 5},
// {x: 2 y: 4},
// {x: 0 y: 3}, 
// {x: 1 y: 1},
// {x: 3 y: 0},
// {x: 2 y: 2},
// {x: 4 y: 1}, 
// {x: 2 y: 0}, 
// {x: 0 y: 1},
// {x: 1 y: 3},
// {x: 3 y: 2}, 
// {x: 5 y: 1},
// {x: 7 y: 0},
// {x: 6 y: 2},
// {x: 5 y: 0},
// {x: 4 y: 2}, 
// {x: 2 y: 3},
// {x: 1 y: 5},
// {x: 0 y: 7}, 
// {x: 2 y: 6},
// {x: 3 y: 4},
// {x: 5 y: 3},
// {x: 4 y: 5},
// {x: 3 y: 3},
// {x: 2 y: 5},
// {x: 4 y: 4},
// {x: 6 y: 3},
// {x: 7 y: 1},