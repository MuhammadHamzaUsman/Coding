#include<iostream>
#include<iomanip>
#include<random>
#include<vector>
#include<array>
#include<ctime>
#include<cmath>
using namespace std;

// size of maze
const size_t board_size = 34;
double pointDist(array<int, 2>, array<int, 2>);
void displayMaze(const array<array<char, board_size>, board_size> &);
array<array<char, board_size>, board_size> generateMaze(int, int);

int main()
{
    // no of points generated on maze range(start-end)
    int start = 75;
    int end = start;
    for(int i = 0; i < 10; i++)
    {
        displayMaze(generateMaze(start, end));
        cin.get();
    }
    cout << "\033[1;0H" << endl;
    return 0;
}

double pointDist(array<int, 2> start, array<int, 2> end)
{
    return sqrt(pow(start[0] - end[0], 2) + pow(start[1] - end[1], 2));
}

void displayMaze(const array<array<char, board_size>, board_size> &maze)
{
    cout << "\033[1;0H" << endl;
    string output = "";

    for(const auto &row : maze)
    {
        for(const auto &col : row)
        {
            // cout << setw(2) << col << " ";

            // if(col == 0)
            //     output += "# ";
            // else if(col == 99)
            //     output += ". ";

            output = output + col + "  ";
        }

        // cout << "\n";
        output += "\n";
    }

    cout << output;
}

array<array<char, board_size>, board_size> generateMaze(int point_start, int point_end)
{
    default_random_engine engine(time(0)); 
    uniform_int_distribution<int> dist(point_start, point_end);
    uniform_int_distribution<int> dist_board(1, board_size - 2);
    array<array<int, board_size>, board_size> maze = {};
    int no_nodes = dist(engine);
    vector<array<int, 2>> nodes;
    
    for(auto &row : maze)
    {
        for(int &col : row)
        {
            col = 0;
        }
    }
    
    array<int, 2> start = {0, dist_board(engine)};
    array<int, 2> end = {board_size - 1, dist_board(engine)};
    maze[start[1]][start[0]] = 1;
    maze[end[1]][end[0]] = 2;
    nodes.push_back(start);
    
    for(int i = 0; i < no_nodes; i++)
    {
        array<int, 2> point = {dist_board(engine), dist_board(engine)};
        maze[point[1]][point[0]] = -1;
        nodes.push_back(point);
    }
    
    array<int, 2> start_node = start;
    array<int, 2> best_node;
    vector<array<int, 2>> branches;
    int counter = 0;
    
    for(int i = 0; i < nodes.size(); i++)
    {
        double minimum = 10000;
        for(int j = 0; j < nodes.size(); j++)
        {
            array<int, 2> test_node = nodes[j];
            if(maze[test_node[1]][test_node[0]] == -1)
            {
                double dist_points = pointDist(start_node, test_node);
                if(dist_points < minimum && dist_points > 0)
                {
                    minimum = dist_points;
                    best_node = test_node;
                }
            }
        }
        
        bool first_vertical = dist(engine) % 2;
        array<int, 2> starting_node = end;
        array<int, 2> ending_node;
        
        if(i == nodes.size() - 1)
        {
            double smallest_dist = 1000;
            
            for(int y = 0; y < board_size - 1; y++)
            {
                for(int x = 0; x < board_size - 1; x++)
                {
                    array<int, 2> test_node = {x, y};
                    
                    if(maze[test_node[1]][test_node[0]] == 99)
                    {
                        double points_dist = pointDist(starting_node, test_node);
                        
                        if(points_dist < smallest_dist)
                        {
                            smallest_dist = points_dist;
                            ending_node = test_node;
                        }
                    }    
                }
            }
            
            start_node = end;
            best_node = ending_node;
            first_vertical = false;
        }
        
        if(i == nodes.size() - 2 || start_node[0] == start[0] || start_node[1] == start[1])
        {
            first_vertical = false;
        }
        
        array<int, 2> temp_node = start_node;
        
        for(int k = 0; k < 2; k++)
        {
            if(first_vertical)
            {
                int diff = best_node[1] - start_node[1];
                
                if(diff != 0)
                {
                    diff /= abs(diff);
                }
                    
                while(best_node[1] != start_node[1])
                {
                    int x_left = start_node[0] - 1;
                    int x_right = start_node[0] + 1;
                    int y_ahead = start_node[1] + diff;

                    if(y_ahead < 0 || y_ahead > board_size - 1)
                    {
                        maze[start_node[1]][start_node[0]] = 99;
                    }
                    else
                    {
                        int right_cell = maze[start_node[1]][x_right];
                        int left_cell = maze[start_node[1]][x_left];
                        int next_right_cell = maze[y_ahead][x_right];
                        int next_left_cell = maze[y_ahead][x_left];

                        if(!((right_cell == 99 && next_right_cell == 99) || (left_cell == 99 && next_left_cell  == 99)))
                        {
                            maze[start_node[1]][start_node[0]] = 99;
                        }
                    }
                    start_node[1] += diff;
                }
                
                maze[start_node[1]][start_node[0]] = 99;
                first_vertical = false;
            }
            else
            {
                int diff = best_node[0] - start_node[0];
                
                if(diff != 0)
                {
                    diff /= abs(diff);
                }
                    
                while(best_node[0] != start_node[0])
                {
                    int y_up = start_node[1] - 1;
                    int y_down = start_node[1] + 1;
                    int x_ahead = start_node[0] + diff;

                    if(x_ahead < 0 || x_ahead > board_size - 1)
                    {
                        maze[start_node[1]][start_node[0]] = 99;
                    }
                    else
                    {
                        int up_cell = maze[y_up][start_node[0]];
                        int down_cell = maze[y_down][start_node[0]];
                        int next_up_cell = maze[y_up][x_ahead];
                        int next_down_cell = maze[y_down][x_ahead];

                        if(!((up_cell == 99 && next_up_cell == 99) || (down_cell == 99 && next_down_cell  == 99)))
                        {
                            maze[start_node[1]][start_node[0]] = 99;
                        }
                    }
                    start_node[0] += diff;
                }
                
                maze[start_node[1]][start_node[0]] = 99;
                first_vertical = true;
            }
        }
        
        start_node = temp_node;
        int rnd_brn = dist_board(engine) % 10;
        
        if((rnd_brn != 0 || rnd_brn != 1 || rnd_brn != 2) && counter < 2)
        {
            counter++;
            branches.push_back(best_node);
        }
        else
        {
            counter = 0;
            
            if(branches.size() > 1)
            {
                int index = rand() % branches.size();
                start_node = branches[index];
            }
            else
                start_node = best_node;
                
            branches = {};
        }
    }
    
    for(int y = 0; y < maze.size(); y++)
    {
        for(int x = 0; x < maze.size(); x++)
        {
            int x_start = x - 1;
            int x_end = x + 1;
            int y_start = y - 1;
            int y_end = y + 1;
            int empty_spaces = 0;

            if(x_start < 0)
            {
                x_start = 0;
            }

            if(x_end >= maze.size())
            {
                x_end = maze.size() - 1;
            }

            if(y_start < 0)
            {
                y_start = 0;
            }

            if(y_end >= maze.size())
            {
                y_end = maze.size() - 1;
            }

            for(int y_range = y_start; y_range <= y_end; y_range++)
            {
                for(int x_range = x_start; x_range <= x_end; x_range++)
                {
                    int &space = maze[y_range][x_range];

                    if(x_range == x && y_range == y)
                    {
                        continue;
                    }
                    else
                    {
                        if(space == 99)
                        {
                            empty_spaces++;
                        }
                    }    
                }
            }    
            if(empty_spaces > 6)
            {
                maze[y][x] = 0;
            }
        }
    }
    
    array<array<char, board_size>, board_size> maze_output;
    
    for(int y = 0; y < maze.size(); y++)
    {
        for(int x = 0; x < maze.size(); x++)
        {
            int col = maze[y][x];
            
            if(col == 0)
                maze_output[y][x] = '#';
            else if(col == 99)
                maze_output[y][x] = '.';
        }
    }
    
    return maze_output;
}