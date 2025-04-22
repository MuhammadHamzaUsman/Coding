#include<iostream>
#include<iomanip>
#include<vector>
#include<array>
using namespace std;

// recurssive Maze Solving
void recurssiveMazeTraveseEngine(vector<vector<char>> &, int, int, int, int, int, int, int);
void recurssiveMazeTravese(vector<vector<char>> &, int, int, int, int, int);
void displayMaze(const vector<vector<char>> &);
vector<vector<char>> maze = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
    {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
    {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '#', '#', '#', '.', '#', '.', '.'},
    {'#', '#', '.', '#', '.', '.', '.', '#', '.', '#', '.', '#'},
    {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
    {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

int main()
{
    recurssiveMazeTravese(:: maze, 0,2, 11,4, 0);
    return 0;
}


void recurssiveMazeTravese(vector<vector<char>> &maze, int start_x, int start_y, int end_x, int end_y, int direction)
{
    displayMaze(maze);
    cin.get();
    maze[start_y][start_x] = '>';
    recurssiveMazeTraveseEngine(maze, start_x, start_y, end_x, end_y, start_x, start_y, direction);
}

void recurssiveMazeTraveseEngine(vector<vector<char>> &maze, int start_x, int start_y, int end_x, int end_y, int current_x, int current_y, int direction)
{
    static array<int, 4> move_x = {1, 0, -1, 0};
    static array<int, 4> move_y = {0, -1, 0, 1};
    if(!(current_x == end_x && current_y == end_y))
    {
        int test_direction = direction - 1;
        if(test_direction < 0)
            test_direction = 3;

        for(int i = 0; i < move_x.size(); i++)
        {
            int temp_x = current_x + move_x[test_direction];
            int temp_y = current_y + move_y[test_direction];
            char test_cell = maze[temp_y][temp_x];

            if(test_cell == '.' || test_cell == '>' || test_cell == '<')
            {
                if(test_cell == '>')
                    maze[temp_y][temp_x] = '<';
                else if(test_cell == '<' || test_cell == '.')
                    maze[temp_y][temp_x] = '>';
                
                displayMaze(maze);
                recurssiveMazeTraveseEngine(maze, start_x, start_y, end_x, end_y, temp_x, temp_y, test_direction);
                break;
            }

            test_direction = ++test_direction % 4;
        }
    }
}

void displayMaze(const vector<vector<char>> &maze)
{
    cout << "\033[2;0H";
    string output = "";

    for(const auto &row : maze)
    {
        for(char col : row)
        {
            output = output + col + "  ";
        }
        output += "\n";
    }

    cout << output;
}
