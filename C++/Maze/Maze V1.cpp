#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<random>
#include<vector>
#include<array>
#include<ctime>
#include<cmath>
using namespace std;

enum class States
{
    NODES = -1,
    WALL = 0,
    START = 1,
    END = 2,
    PATH = 99
};

int randomOddNumber(int, int, default_random_engine &);
int randomEvenNumber(int, int, default_random_engine &);
double pointDist(array<int, 2>, array<int, 2>);
array<array<int, 2>, 2> getMazeStartEnd(const vector<vector<char>> &);
array<int, 2> randomBranchNode(array<int, 2>, int, int, default_random_engine &, int, int);
void displayMaze(const vector<vector<char>> &, int);
void displayMazeViewDist(const vector<vector<char>> &, array<array<int, 2>, 2>, array<int, 2>, string, string, string, char);
vector<vector<char>> generateMaze(int, int, int, int);
void writeToFile(const vector<vector<char>> &, int);
void drawPath(vector<vector<States>> &, array<int, 2>, array<int, 2>, bool, bool);
bool playMaze(vector<vector<char>>, array<array<int, 2>, 2>, array<array<int, 2>, 2>, int, int, int, char, char, bool);
array<array<int, 2>, 2> displayMazeFog(const vector<vector<char>> &, array<array<int, 2>, 2>, array<int, 2>, int, int, string, string, char);
void recurssiveMazeTraveseEngine(vector<vector<char>> &, int, int, int, int, int, int, int, array<array<int, 2>, 2>, int, int, char, char, bool, string, string, string);
void recurssiveMazeTravese(vector<vector<char>>, int, int, int, int, int, array<array<int, 2>, 2>, int, int, int, char, char, bool);
void menu();

int main()
{
    menu();
    return 0;
}

double pointDist(array<int, 2> start, array<int, 2> end)
{
    return sqrt(pow(start[0] - end[0], 2) + pow(start[1] - end[1], 2));
}

void displayMaze(const vector<vector<char>> &maze, int col_width)
{
    string output = "";
    string empty_col = "";

    for(int i = 1; i < col_width; i++)
    {
        empty_col += " ";
    }

    cout << "\033[0;0H";

    for(const vector<char> &row : maze)
    {
        for(char col : row)
        {
            output = output + col + empty_col;
        }
        output += "\n";
    }

    cout << output;
}

vector<vector<char>> generateMaze(int point_start, int point_end, int maze_width, int maze_height)
{
    // maze only generate and test nodes which are odd to ensure no two paths are right next to each other

    // for generating random nodes on maze 
    // no of nodes will be selected randomly from range (point_start to point_end)
    default_random_engine engine(time(0)); 
    uniform_int_distribution<int> dist(point_start, point_end);

    // 2d Array that stores maze
    vector<vector<States>> maze = {};

    // no of nodes that will be generated and stored in vector nodes
    int no_nodes = dist(engine);
    vector<array<int, 2>> nodes;

    // intializing maze
    for(size_t y = 0; y < maze_height; y++)
    {
        vector<States> temp;
        for (size_t x = 0; x < maze_width; x++)
        {
            temp.push_back(States :: WALL);
        }
        maze.push_back(temp);
    }

    // maximum and minimum distance that a node can generate away from its previous one
    const int MIN_DIST = 2;
    const int MAX_DIST = 6;

    // condition for testing cardinal directions for
    // 1: while generating braches to test which direction is does not have path
    // 2. while finding which nodes does not have any path to connected them
    const size_t no_of_tests = 4;
    array<array<int, 2>, no_of_tests> test_conditions = {
        {
            {1, 0},
            {0, -1},
            {-1, 0},
            {0, 1}
        }
    };
    
    // start will always be on left, only its y position can be changed
    array<int, 2> start = {0, randomOddNumber(1, maze_height - 1, engine)};
    // end will always be on right, only its y position can be changed
    array<int, 2> end = {maze_width - 1, randomOddNumber(1, maze_height - 1, engine)};
    // placing start and end on maze
    maze[start[1]][start[0]] = States :: START;
    maze[end[1]][end[0]] = States :: END;
    // adding start to nodes, so that maze starts from start
    nodes.push_back(start);

    int node_max_dist = 0;
    int point_x_min;
    int point_y_min;
    int point_x_max;
    int point_y_max;

    // generates random nodes, ensure that they do not excced MAX_DIST and add them to maze and nodes
    for(int i = 0; i < no_nodes; i++)
    {
        // generating random range for odd nodes
        node_max_dist = randomEvenNumber(MIN_DIST, MAX_DIST, engine);
        point_x_max = nodes[i][0] + node_max_dist;
        point_x_min = nodes[i][0] - node_max_dist;
        point_y_max = nodes[i][1] + node_max_dist;
        point_y_min = nodes[i][1] - node_max_dist;

        // ensuring they are in bounds

        point_x_max = (point_x_max > maze_width - 1) ? maze_width - 1 : point_x_max;
        point_x_min = (point_x_min < 1) ? 1 : point_x_min;
        point_y_max = (point_y_max > maze_height - 1) ? maze_height - 1 : point_y_max;
        point_y_min = (point_y_min < 1) ? 1 : point_y_min;

        array<int, 2> point = {randomOddNumber(point_x_min, point_x_max, engine), randomOddNumber(point_y_min, point_y_max, engine)};

        // placing on maze
        maze[point[1]][point[0]] = States :: NODES;
        // adding to vector nodes
        nodes.push_back(point);
    }

    cout << "      Points Generated\n";
    
    // connects all random points genrated with above in order of thier generation then connects end to nearest Path
    
    for(int i = 0; i < nodes.size(); i++)
    {
        // start_node: node from which Path will starts
        // end_nod: node at which path will end
        // format: [x position, y position]
        array<int, 2> start_node = nodes[i]; 
        // setting end_node to node next in vector from start_node
        // enusring it does not address out of bounds
        array<int, 2> end_node = nodes[(i + 1 < nodes.size() ? i + 1 : i)];
        // decides wether(50% chance of each case)
        // o: path will first go vertical then horizontal
        // 0: path will go first horizontal then vertical
        bool first_vertical = dist(engine) % 2;
        
        // if starting or ending point do not move vertical first as it will set border to Path
        if(start_node[0] == start[0] || start_node[1] == start[1])
        {
            first_vertical = false;
        }

        // last Path can overlap with any Path 
        /* vertical Path was exsisting and horizontal was one that was being drawn through it
            # # . # # #
            . . . . . .
            # # . # # #
        */ 
        // other will stop two steps before Path and will continue from right next node with exsisting Path as
        /* vertical Path was exsisting and horizontal was one that was being drawn through it
            # # . # # #
            . . . # . .
            # # . # # #
        */

        drawPath(maze, start_node, end_node, first_vertical, false);
    }

    cout << "      Points Connected\n";

    // for each node generate branches from it to direction that does not have exsisting Paths 
    for(size_t node_index = 1; node_index < nodes.size(); node_index++)
    {
        // node from which branch will start
        array<int, 2> node = nodes[node_index];

        // find which direction does not have Paths and drwa random branch to it
        for(size_t test = 0; test < no_of_tests; test++)
        {
            // x and y position of node in direction to test
            int x = node[0] + test_conditions[test][0] * 2;
            int y = node[1] + test_conditions[test][1] * 2;

            // ensuring that postions are not of bounds
            if(x < 0)
                x = 0;
            else if(x > maze_width - 1)
                x = maze_width - 1;
            
            if(y < 0)
                y = 0;
            else if(y > maze_height - 1)
                y = maze_height - 1;

            // if Path is in this direction continue to next direction
            // else genrates random node and draw Path to it creating a branch
            if(maze[y][x] == States :: PATH)
                continue;
            else
            {
                array<int, 2> branch_node = randomBranchNode(node, 4, 4, engine, maze_width, maze_height); // test these to find which works best
                drawPath(maze, node, branch_node, (randomEvenNumber(0, 2, engine) == 0), false);
                node = branch_node;
                branch_node = randomBranchNode(node, 4, 4, engine, maze_width, maze_height); // test these to find which works besr
                drawPath(maze, node, branch_node, (randomEvenNumber(0, 2, engine) == 0), false);
            }   
        }
    }

    cout << "      Branches Created\n";

    // test all odd nodes to find which does not have Path to them and draw a Path to them and a branch from it
    for(int y = 1; y <= maze_height - 2; y += 2)
    {
        for(int x = 1; x <= maze_width - 2; x += 2)
        {
            // count number of blocked spaces ie nodes that have Walls
            int no_of_blocked_spaces = 0;
            for(size_t test = 0; test < no_of_tests; test++)
            {
                if(maze[y + test_conditions[test][1]][x + test_conditions[test][0]] == States :: WALL)
                    no_of_blocked_spaces++;
            }

            // if no_of_blocked_spaces are nearest Path and connect to it 
            if(no_of_blocked_spaces == 4)
            {
                // for creating a branch from node that does not have Path connecting to it
                array<int, 2> branch_node;
                // node that does not have Path connecting to it
                array<int, 2> node = {x, y};
                // node to test for its dsitance
                array<int, 2> test_node = {};

                // calculating diagnol distancea and adding small value to ensure it is largest
                double minimum_distance = sqrt((maze_width * maze_width) + (maze_height * maze_height)) + 2;
                // it will store distance from node to test_node
                double distance = 0;

                // it will start from node and test all node in consectrich squares from it
                // these gives rnges of sqqaure to test
                int y_start = y, y_end = y;
                int x_start = x, x_end = x;

                while(distance < minimum_distance)
                {
                    // incre/decrements y by 2 so that only odd node are tested  and enusriing that ranges are in bounds same for x
                    y_start -= 2;
                    y_start = (y_start < 1) ? 1 : y_start;
                    y_end += 2;
                    y_end = (y_end > maze_height - 2) ? maze_height - 2 : y_end;

                    x_start -= 2;
                    x_start = (x_start < 1) ? 1 : x_start;
                    x_end += 2;
                    x_end = (x_end > maze_width - 2) ? maze_width - 2 : x_end;

                    // test all nodes in ranges that are path and find shortest distance
                    for(int y_test = y_start; y_test <= y_end; y_test += 2)
                    {
                        for(int x_test = x_start; x_test <= x_end; x_test += 2)
                        {
                            // if test nodes is Path
                            if(maze[y_test][x_test] == States :: PATH)
                            {
                                test_node = {x_test, y_test};
                                // find distance to it
                                distance = pointDist(node, test_node);
                                
                                // if distance is greater than previous smallest distance break because we are testing in conctric squares
                                if(distance > minimum_distance)
                                    break;

                                // if distance is less then randomly create a branch(30%)
                                if(distance < minimum_distance && randomEvenNumber(0, 18, engine) <= 4)
                                {
                                    branch_node = {x_test, y_test};
                                    minimum_distance = distance;
                                }   
                            }
                        }
                        
                        if(distance > minimum_distance)
                            break;
                    }
                }

                drawPath(maze, branch_node, node, (randomEvenNumber(0, 2, engine) == 0), false);

                // generate 3 random branches and connect them to node
                for(int i = 0; i < 3; i++)
                {
                    branch_node = randomBranchNode(node, 4, 4, engine, maze_width, maze_height);
                    drawPath(maze, node, branch_node, (randomEvenNumber(0, 2, engine) == 0), false);
                }
            }
        }
    }

    cout << "Non Reachable Spaces Removed\n";

    // for last node
    // if on last node start from top left of maze and find nearest node which path and set it to start node
    // nearest_node is node which will store node nearest to end
    // calculating diagnol distancea and adding small value to ensure it is largest
    array<int, 2> nearest_node;
    double smallest_dist = sqrt((maze_width * maze_width) + (maze_height * maze_height)) + 2;

    for(int y = maze_height - 2; y >= 0; y--)
    {
        for(int x = maze_width - 2; x >= 0 ; x--)
        {
            // node to find distance to test
            array<int, 2> test_node = {x, y};
            
            // if test node is Path
            if(maze[test_node[1]][test_node[0]] == States :: PATH)
            {
                // distance of test node
                double points_dist = pointDist(end, test_node);
                
                // if points_dist smaller then set smallest_dist to it 
                // and nearest_node to test_node
                if(points_dist < smallest_dist)
                {
                    smallest_dist = points_dist;
                    nearest_node = test_node;
                }
            }    
        }
    }
    // it will draw a path directt from end to nearest node that is Path
    drawPath(maze, end, nearest_node, false, true);

    cout << "       End Connected\n";

    // convert maze from States datatype to char datatype
    
    vector<vector<char>> maze_output;
    
    for(int y = 0; y < maze_height; y++)
    {
        vector<char> temp;
        for(int x = 0; x < maze_width; x++)
        {   
            States col = maze[y][x];

            if(col == States :: WALL)
                temp.push_back('#');
            else if(col == States :: PATH)
                temp.push_back('.');
        }
        maze_output.push_back(temp);
    }

    cout << "\t  Converted";
    
    return maze_output;
}

int randomOddNumber(int lower_limit, int upper_limit, default_random_engine &engine)
{
    uniform_int_distribution<int> dist(lower_limit, upper_limit);
    int number = dist(engine);

    number = (number % 2) ? number : number - 1;
    return number;
}

int randomEvenNumber(int lower_limit, int upper_limit, default_random_engine &engine)
{
    uniform_int_distribution<int> dist(lower_limit, upper_limit);
    int number = dist(engine);

    number = (number % 2) ? number + 1 : number;
    return number;
}

void drawPath(vector<vector<States>> &maze, array<int, 2> start_node, array<int, 2> end_node, bool first_vertical, bool can_overlap)
{
    // move in both direction
    for(int k = 0; k < 2; k++)
    {
        if(first_vertical)
        {
            // find wether it is wether up or down 
            // +ive for down
            // -ive for up
            int diff = end_node[1] - start_node[1];
            
            // if diffrence is not zero convert diff to 1/-1
            if(diff != 0)
                diff /= abs(diff);
                
            // loop until both have have same y postion
            while(end_node[1] != start_node[1])
            {
                // if next node is not path or Path can overlap
                if(maze[start_node[1] + diff][start_node[0]] != States :: PATH || can_overlap)
                {
                    // set node to Path
                    maze[start_node[1]][start_node[0]] = States :: PATH;
                }
                // update y postion to check for next node
                start_node[1] += diff;
            }
            
            // set corner to Path
            maze[start_node[1]][start_node[0]] = States :: PATH;
            // set to false so it can now draw horizontal path
            first_vertical = false;
        }
        else // same as above but for x / horizontal Path
        {
            int diff = end_node[0] - start_node[0];
            
            if(diff != 0)
                diff /= abs(diff);
                
            while(end_node[0] != start_node[0])
            {
                if(maze[start_node[1]][start_node[0] + diff] != States :: PATH || can_overlap)
                {
                    maze[start_node[1]][start_node[0]] = States :: PATH;
                }
                start_node[0] += diff;
            }
            
            maze[start_node[1]][start_node[0]] = States :: PATH;
            first_vertical = true;
        }
    }
}

array<int, 2> randomBranchNode(array<int, 2> node, int lower_limit, int upper_limit, default_random_engine &engine, int maze_width, int maze_height)
{
    // generate how far along x will random branch end
    int x_diff = randomEvenNumber(lower_limit, upper_limit, engine);
    // randomlt decide(50%) wether it will go right(+ive) or left (-ive)
    x_diff = (randomEvenNumber(0, 2, engine) == 0) ? -x_diff : x_diff;
    // set branch_x position to node x position + x_diff
    int branch_x = node[0] + x_diff;

    // if brach_x is out of bounds set it to 1 less than bounds
    if(branch_x < 1)
        branch_x = 1;
    if(branch_x > maze_width - 2)
        branch_x = maze_width - 2;

    // generate how far along y will random branch end
    int y_diff = randomEvenNumber(lower_limit, upper_limit, engine);
    // randomlt decide(50%) wether it will go down(+ive) or ip (-ive)
    y_diff = (randomEvenNumber(0, 2, engine) == 0) ? -y_diff : y_diff;
    // set branch_y position to node y position + xy_diff
    int branch_y = node[1] + y_diff;

    // if brach_x is out of bounds set it to 1 less than bounds
    if(branch_y < 1)
        branch_y = 1;
    if(branch_y > maze_height - 2)
        branch_y = maze_height - 2;

    // return in format: [x position, y position]
    array<int, 2> branch = {branch_x, branch_y};
    return branch;
}

array<array<int, 2>, 2> getMazeStartEnd(const vector<vector<char>> &maze)
{
    // start_x is 0 as maze will always start from left
    int start_x = 0;
    // end_y is maze_width -1 as maze will always end in right
    int end_x = maze[0].size() - 1;
    // starting y position
    int start_y;
    // ending  y postion
    int end_y;

    // loop through all rows
    for(size_t row = 0; row < maze.size(); row++)
    {
        // if than row's start has Path in it set it than that row is starting y postion
        if(maze[row][start_x] == '.')
        {
            start_y = row;
        }
        // if than row's start has Path in it set it than that row is starting x postion
        if(maze[row][end_x] == '.')
        {
            end_y = row;
        }
    }

    // return in format [starting[x, y], ending[x, y]]
    return {{{start_x, start_y}, {end_x, end_y}}};
}

bool playMaze(vector<vector<char>> maze, array<array<int, 2>, 2> start_end, array<array<int, 2>, 2> view_distance, int WIDTH, int HEIGTH, int col_width, char path_symbol, char player_symbol, bool isViewDistMode)
{
    enum GameState {
        CONTINUE = 2,
        WIN = 1,
        LOSE = 0
    };

    int maze_width = maze[0].size();
    int maze_heigth = maze.size();
    int player_x = start_end[0][0];
    int player_y = start_end[0][1];
    int x_diff;
    int y_diff;
    char user_input = ' ';
    GameState game = CONTINUE;

    maze[player_y][player_x] = player_symbol; // atr
    string empty_col = "";
    string col_padding = "";
    string bar = "";
    for(int i = 0; i < col_width; i++)
    {
        empty_col += " ";
        bar += "-";
        if(i < col_width - 1)
        {
            col_padding += " ";
        }
    }
    if(isViewDistMode)
        displayMazeViewDist(maze, view_distance, {player_x, player_y}, empty_col, col_padding, bar, path_symbol);
    else
    {
        view_distance = {0, 0, 0, 0}; 
        view_distance = displayMazeFog(maze, view_distance, {player_x, player_y}, WIDTH, HEIGTH, col_padding, bar, path_symbol);
    }
    
    while(game == CONTINUE)
    {
        x_diff = 0;
        y_diff = 0;
        
        user_input = getch();
        
        if(user_input == 'w')
        {
            if(player_y - 1 > -1)
                y_diff = -1;
            else
                y_diff = 0;
        }
        else if(user_input == 's')
        {
            if(player_y + 1 < maze_heigth)
                y_diff = 1;
            else
                y_diff = 0;
        }
        else if(user_input == 'a')
        {
            if(player_x - 1 > -1)
                x_diff = -1;
            else
                x_diff = 0;
        }
        else if(user_input == 'd')
        {
            if(player_x + 1 < maze_width)
                x_diff = 1;
            else
                x_diff = 0;
        }
        else if(user_input == 'm')
        {
            game = LOSE;
        }
        
        if(maze[player_y + y_diff][player_x + x_diff] == '.')
        {
            maze[player_y][player_x] = '.';
            maze[player_y + y_diff][player_x + x_diff] = player_symbol;
            player_y += y_diff;
            player_x += x_diff;
            
            if(player_x == start_end[1][0] && player_y == start_end[1][1])
            {
                game = WIN;
            }
        }    
        
        if(isViewDistMode)
            displayMazeViewDist(maze, view_distance, {player_x, player_y}, empty_col, col_padding, bar, path_symbol);
        else
            view_distance = displayMazeFog(maze, view_distance, {player_x, player_y}, maze_width, maze_heigth, col_padding, bar, path_symbol);
    }
    return (game == WIN);
}

void displayMazeViewDist(const vector<vector<char>> &maze, array<array<int, 2>, 2> view_dist, array<int, 2> player_pos, string empty_col, string col_padding, string bar, char path_symbol)
{
    int maze_width = maze[0].size();
    int maze_heigth = maze.size();

    // view_dist format
    // view_dist[0][0]: no of blocks to left
    // view_dist[0][1]: no of blocks to right
    // view_dist[1][0]: no of blocks to up
    // view_dist[1][1]: no of blocks to down

    // ranges for nodes to bee printed
    int x_start = player_pos[0] - view_dist[0][0];
    int x_end = player_pos[0] + view_dist[0][1];
    int y_start = player_pos[1] - view_dist[1][0];
    int y_end = player_pos[1] + view_dist[1][1];

    // total nodes user can seealong y axis and x axis
    int y_dist = view_dist[1][0] + view_dist[1][1];
    int x_dist = view_dist[0][0] + view_dist[0][1];
    
    // if any is out of bounds set it to bounds
    x_start = (x_start < 0) ? 0 : x_start;
    x_end = (x_end >= maze_width) ? (maze_width - 1) : x_end;
    y_start = (y_start < 0) ? 0 : y_start;
    y_end = (y_end >= maze_heigth) ? (maze_heigth - 1) : y_end;

    // stores total final output
    string output = "";
    // stores top and bottom borders
    string bars = "+";
    // for all x nodes user can see plus his postion 
    for(int i = 0 ; i < x_dist + 1; i++)
    {
        bars += bar;
    }

    // add to final ouput
    bars += "+";
    output = output + bars + "\n";
    
    // if user moves to rows or colums where edges of screen has nothing to show tahn that area is padded with spaces to ensure 
    // border remain same and user remains in center

    // if user is on top and y_dist - y_end is greater than zero than no of rows will be padded
    // y_dist = 4  y_end = 3 then 1 row will be padded 
    // y_dist = 4  y_end = 5 then -1 row will be padded conditon false
    for(int i = 0; i < y_dist - y_end; i++)
    {
        output += "|";
        for(int x = 0; x < x_dist + 1; x++)
        {
            output += empty_col;
        }
        output += "|\n";
    }
    // from y start to y end 
    for(size_t y = y_start; y <= y_end; y++)
    {
        // left border 
        output += "|";

        // if user is on left and x_dist - x_end is greater than zero than no of col will be padded
        // x_dist = 4  x_end = 3 then 1 row will be padded 
        // x_dist = 4  x_end = 5 then -1 row will be padded conditon false
        for(int i = 0; i < x_dist - x_end; i++)
        {
            output += empty_col;
        }
        
        // for normal columns
        for(size_t x = x_start; x <= x_end; x++)
        {
            if(maze[y][x] == '.')
            {
                output = output + path_symbol + col_padding;
            }
            else
            {
                output = output + maze[y][x] + col_padding;
            }
        }

        // condition is to ensure that right padding is for done when left padding will not be added
        if(x_start > view_dist[0][0])
        {
            // if user is on right and x_dist - (x_end - x_start) than no of col will be padded
            // x_end = 20 x_start = 17 x_dist = 4 then 1 col will be padded
            // x_end = 17 x_start = 13 x_dist = 4 then 0 col will be padded
            for(int j = 0; j < x_dist - (x_end - x_start); j++)
            {
                output += empty_col;
            }
        }
        
        // addition of right border
        output += "|\n";
    }
    
    if(y_start > view_dist[1][0])
    {
        // if user is on bottom and y_dist - (y_end - y_start) than no of rows will be padded
        // y_end = 20 y_start = 17 y_dist = 4 then 1 col will be padded
        // y_end = 17 y_start = 13 y_dist = 4 then 0 col will be padded
        for(int y = 0; y < y_dist - (y_end - y_start); y++)
        {
            output += "|";
            for(int x = 0; x < x_dist + 1; x++)
            {
                output += empty_col;
            }
            output += "|\n";
        }
    }

    
    // addition of lower border
    output = output + bars;
    
    // going to top of screen and printing final output
    cout << "\033[0;0H" << output;
}

void writeToFile(const vector<vector<char>> &maze, int file_col_width)
{
    ofstream maze_output("Maze.txt");

    string empty_col = "";
    for(int i = 1; i < file_col_width; i++)
    {
        empty_col += " ";
    }

    if(!maze_output)
    {
        cerr << "\nFile not Found or Error creating file.";
        maze_output.close();
    }
    else
    {
        for(const vector<char> &row : maze)
        {
            for(char col : row)
            {
                maze_output << col << empty_col;
            }
            maze_output << "\n";
        }
        cout << "\nMaze saved successfully.";
    }

    maze_output << "Maze saved successfully.";
    maze_output.close();
}

array<array<int, 2>, 2> displayMazeFog(const vector<vector<char>> &maze, array<array<int, 2>, 2> view_dist, array<int, 2>player_pos, int WIDTH, int HEIGTH, string col_padding, string bar, char path_symbol)
{
    int maze_width = maze[0].size();
    int maze_heigth = maze.size();

    // view_dist format
    // view_dist[0][0]: no of blocks to left
    // view_dist[0][1]: no of blocks to right
    // view_dist[1][0]: no of blocks to up
    // view_dist[1][1]: no of blocks to down

    // fisrt time it is centerd around user
    // in case of odd Dimesion one is add to ensure that total colums remain same otherwise 
    // due to integer division one columns would not be counted
    if(view_dist[0][0] + view_dist[0][1] + view_dist[1][0] + view_dist[1][1] == 0)
        view_dist = {{{player_pos[0] - WIDTH / 2, (player_pos[0] + (WIDTH % 2 == 0 ? WIDTH / 2 : WIDTH / 2 + 1))}, 
                    {player_pos[1] - HEIGTH / 2, (player_pos[1] + (HEIGTH % 2 == 0 ? HEIGTH / 2: HEIGTH / 2 + 1))}}};

    // if user get in range of 3 blocks of left edge move pov to left so user remains on screen
    // else if user get in range of 3 blocks of right edge move pov to right so user remains on screen
    if(player_pos[0] < view_dist[0][0] + 3)
    {
        view_dist[0][0] -= 1;
        view_dist[0][1] -= 1;
    }
    else if(player_pos[0] >= view_dist[0][1] - 3)
    {
        view_dist[0][0] += 1;
        view_dist[0][1] += 1;
    }
    // if user get in range of 3 blocks of top edge move pov to top so user remains on screen
    // else if user get in range of 3 blocks of down edge move pov to down so user remains on screen
    if(player_pos[1] < view_dist[1][0] + 3)
    {
        view_dist[1][0] -= 1;
        view_dist[1][1] -= 1;
    }
    else if(player_pos[1] >= view_dist[1][1] - 3)
    {
        view_dist[1][0] += 1;
        view_dist[1][1] += 1;
    }

    // if view_dist[0][0] is less than bounds than 
    // add it to view_dist[0][1] to keep no of blocks displayed equal to width
    // (in this case as less than 0 is -ive than we subtract it as it would be addition)
    // (1 - (-1) = 2) 
    // and set view_dist[0][0] to bounds
    // if view_dist[0][1] is greater than bounds than 
    // subtract overflow from view_dist[0][0] to keep no of blocks displayed equal to width 
    // and set view_dist[0][1] to bounds 
    // for bound checking check orignal dimension but for correction use display dimension
    if(view_dist[0][0] < 0)
    {
        view_dist[0][1] -= view_dist[0][0];
        
        if(view_dist[0][1] > maze_width)
            view_dist[0][1] = WIDTH;
        
        view_dist[0][0] = 0;
    }
    
    if(view_dist[0][1] > maze_width)
    {
        int overflow = view_dist[0][1] - maze_width;
        view_dist[0][0] -= overflow;
        
        if(view_dist[0][0] < 0)
            view_dist[0][0] = 0;

        view_dist[0][1] = maze_width;
    }

    // same as for x-axis above
    if(view_dist[1][0] < 0)
    {
        view_dist[1][1] -= view_dist[1][0];

        if(view_dist[1][1] > maze_heigth)
            view_dist[1][1] = HEIGTH;
        
        view_dist[1][0] = 0;
    }
    
    if(view_dist[1][1] > maze_heigth)
    {
        int overflow = view_dist[1][1] - maze_heigth;
        view_dist[1][0] -= overflow;

        if(view_dist[1][0] < 0)
            view_dist[1][0] = 0;

        view_dist[1][1] = maze_heigth;
    }

    string bars = "+";

    for(int x = view_dist[0][0]; x < view_dist[0][1]; x++)
    {
        bars += bar;
    }

    bars += "+";

    string output = "";
    output += bars;
    output += "\n";
   
    for(size_t y = view_dist[1][0]; y < view_dist[1][1]; y++)
    {
        output += "|";
        for(size_t x = view_dist[0][0]; x < view_dist[0][1]; x++)
        {
            if(maze[y][x] == '.')
            {
                output = output + path_symbol + col_padding;
            }
            else
            {
                output = output + maze[y][x] + col_padding;
            }
        }
        output += "|\n";
    }
    output += bars;

    cout << "\033[0;0H" << output;

    return view_dist;
}

void menu()
{
    int col_width = 3; 
    int file_col_width = 2; 
    array<array<int, 2>, 2> view_distance = {{{2, 2}, {2, 2}}}; 
    char player_symbol = 'o';
    char path_symbol = '.';
    int WIDTH = 10;
    int HEIGTH = 10;
    const double ALPHA = 0.1;
    const double BETA = 1.2;

    char user_input = ' '; 
    string no_purpose = "";

    while(user_input != 'e')
    {
        system("cls");
        cout << " Maze Generator\n\n"
             << "Generate Maze: G\n"
             << "  Settings: S\n"
             << "    Exit: E";

        cin >> user_input;
        
        user_input = tolower(user_input);

        if(user_input == 'g')
        {
            char maze_menu = ' ';
            while(maze_menu != 'e')
            {
                char generate_menu = ' ';
                int maze_width = 0;
                int maze_heigth = 0;

                do
                {
                    system("cls");

                    cout << "Enter Maze Size(Odd values): ";
                    cout << "\n     Enter Width: ";
                    cin >> maze_width;
                    cout << "     Enter Height: ";
                    cin >> maze_heigth;
                    
                    if(cin.fail())
                    {
                        cin.clear();
                        cin.ignore(100 ,'\n');
                    }

                    if((maze_width % 2 == 0) || (maze_heigth % 2 == 0))
                    {
                        maze_width = 0;
                        maze_heigth = 0;
                    }

                }while((maze_width <= 0) || (maze_heigth <= 0) || (cin.fail()));

                int no_points = ALPHA * pow(maze_width * maze_heigth, BETA);
                int no_points_2_per = no_points * 0.02;
                no_points_2_per = no_points_2_per < 2 ? 2 : no_points_2_per;
                int lower_limit_no_points = no_points - rand() % no_points_2_per;
                int higher_limit_no_points = no_points + rand() % no_points_2_per;
                vector<vector<char>> maze = generateMaze(lower_limit_no_points, higher_limit_no_points, maze_width, maze_heigth);

                while(generate_menu != 'e')
                {
                    system("cls");

                    cout << "   View Maze: V\n"
                         << "   Play Maze: P\n"
                         << "   Save Maze: S\n"
                         << "  Traverse Maze: T\n"
                         << "Generate New Maze: G\n"
                         << "     Exit : E";
                    cin >> generate_menu;

                    generate_menu = tolower(generate_menu);

                    if(generate_menu == 'v')
                    {
                        system("cls");
                        if(maze_width > WIDTH)
                        {
                            cout << "Maze can not be printed becuase screen size is less than maze width.\n\t\tMaze is written to Maze.txt file.\n";
                            writeToFile(maze, file_col_width);
                        }
                        else
                        {
                            displayMaze(maze, col_width);
                            char nop;
                            cin >> nop;
                        }
                        cin.ignore(100, '\n');
                        cin.get();
                    }
                    else if(generate_menu == 'p')
                    {
                        char play_menu = 'p';
                        while(play_menu == 'p')
                        {
                            system("cls");

                            char user_option = ' ';
                            bool isViewDistMode = true;

                            do
                            {

                                cout << "User Centerd Display Mode: U\n"
                                     << "Edge Panning Display Mode: E";
                                cin >> user_option;

                                user_option = tolower(user_option);

                                if(user_option == 'u')
                                    isViewDistMode = true;
                                else
                                    isViewDistMode = false;

                            }while(user_option != 'u' && user_option != 'e');

                            system("cls");

                            array<array<int, 2>, 2> start_end = getMazeStartEnd(maze);
                            bool won = playMaze(maze, start_end, view_distance, WIDTH, HEIGTH, col_width, path_symbol, player_symbol, isViewDistMode);

                            system("cls");

                            if(won)
                            {
                                cout << "  You Won!";
                            }
                            else
                            {
                                cout << "  You Lose";
                            }

                            cout << "\nPlay Again: P"
                                 << "\n   Exit: E";
                            cin >> play_menu;
                        }
                    }
                    else if(generate_menu == 's')
                    {
                        system("cls");
                        cout << "If maze have more columns than file text will move to next line.\n\t"
                             << "\t        Saving the maze\n";
                        writeToFile(maze, file_col_width);
                        
                        cin.ignore(100, '\n');
                        cin.get();
                    }
                    else if(generate_menu == 't')
                    {
                        system("cls");

                        bool isViewDistMode = true;
                        char user_option = ' ';

                        do
                        {

                            cout << "User Centerd Display Mode: U\n"
                                    << "Edge Panning Display Mode: E";
                            cin >> user_option;

                            user_option = tolower(user_option);

                            if(user_option == 'u')
                                isViewDistMode = true;
                            else
                                isViewDistMode = false;

                        }while(user_option != 'u' && user_option != 'e');

                        cout << "\nin";
                        array<array<int, 2>, 2> start_end = getMazeStartEnd(maze);
                        cout << "\nin";

                        system("cls");

                        recurssiveMazeTravese(maze, start_end[0][0], start_end[0][1], start_end[1][0], start_end[1][1], 0, view_distance, WIDTH, HEIGTH, col_width, player_symbol, path_symbol, isViewDistMode);
                    }
                    else if(generate_menu == 'g')
                    {
                        break;
                    }
                }
                if(generate_menu == 'e')
                    maze_menu = 'e';
            }
        }
        else if(user_input == 's')
        {  
            char setting_menu = ' ';
            while(setting_menu != 'e')
            {
                system("cls");

                cout << "\t    Settings\n"
                     << "\n\t Column Width(C): " << col_width
                     << "\n\tPlayer Symbol(P): " << player_symbol
                     << "\n\t Path Symbol(R): " << path_symbol
                     << "\n    Column Width in File(F): " << file_col_width
                     << "\n Screen Dimension(S): Panning mode"
                     << "\nView Distance(V): User Centerd Mode"
                     << "\n\t      Exit: E";
                cin >> setting_menu;

                setting_menu = tolower(setting_menu);

                if(setting_menu == 'c')
                { 
                    do{
                        system("cls");
                        cout << "  Column Width: " << col_width
                             << "\nNew Column Width: ";
                        cin >> col_width;
                        
                        if(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(100, '\n');
                        }

                    }while(cin.fail() || col_width <= 1);
                }
                else if(setting_menu == 'p')
                {
                    system("cls");
                    cout << "  Player Symbol: " << player_symbol
                        << "\nNew Player Symbol: ";
                    cin >> player_symbol;
                }
                else if(setting_menu == 'r')
                {
                    system("cls");
                    cout << "  Path Symbol: " << path_symbol
                        << "\nNew Path Symbol: ";
                    cin >> path_symbol;
                }
                else if(setting_menu == 'f')
                {
                    do{
                        system("cls");
                        cout << "  Column Width in File: " << file_col_width
                             << "\nNew Column Width in File: ";
                        cin >> file_col_width;
                        
                        if(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(100, '\n');
                        }

                    }while(cin.fail() || file_col_width < 1);
                }
                else if(setting_menu == 's')
                {
                    char view_dist_menu = ' ';

                    while(view_dist_menu != 'e')
                    {
                        system("cls");

                        cout << "Screen Heigth: " << HEIGTH
                             << "\nScreen Width: " << WIDTH
                             << "\n   Change: C"
                             << "\n    Exit: E";
                        cin >> view_dist_menu;

                        view_dist_menu = tolower(view_dist_menu);

                        if(view_dist_menu == 'c')
                        {
                            do
                            {
                                system("cls");

                                cout << "Enter New Screen Dimension(>= 3):\n\n";
                                cout << "\t  Enter Width: ";
                                cin >> WIDTH;
                                cout << "\t  Enter Height: ";
                                cin >> HEIGTH;

                                if(cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore(100 ,'\n');
                                }

                            }while((WIDTH <= 3) || (HEIGTH <= 3) || (cin.fail()));
                        }
                    }
                }
                else if(setting_menu == 'v')
                {
                    char view_dist_menu = ' ';

                    while(view_dist_menu != 'e')
                    {
                        system("cls");

                        cout << "Number of blocks to Left: " << view_distance[0][0]
                             << "\nNumber of blocks to Right: " << view_distance[0][1]
                             << "\nNumber of blocks to Up: " << view_distance[1][0]
                             << "\nNumber of blocks to Down: " << view_distance[1][1]
                             << "\n\t Change: C"
                             << "\n\t  Exit: E";
                        cin >> view_dist_menu;

                        view_dist_menu = tolower(view_dist_menu);

                        if(view_dist_menu == 'c')
                        {
                            do
                            {
                                system("cls");

                                cout << "Enter New View Distance(>= 1): ";
                                cout << "\n\nNumber of blocks to Left: ";
                                cin >> view_distance[0][0];
                                cout << "Number of blocks to Rigth: ";
                                cin >> view_distance[0][1];
                                cout << "Number of blocks to Up: ";
                                cin >> view_distance[1][0];
                                cout << "Number of blocks to Down: ";
                                cin >> view_distance[1][1];

                                if(cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore(100 ,'\n');
                                }

                            }while((view_distance[0][0] < 1) || (view_distance[0][1] < 1) || (view_distance[1][0] < 1) || (view_distance[1][1] < 1) && (cin.fail()));
                        }
                    }
                }
            }
        }
    }
}

void recurssiveMazeTravese(vector<vector<char>> maze, int start_x, int start_y, int end_x, int end_y, int direction, array<array<int, 2>, 2> view_distance, int WIDTH, int HEIGTH, int col_width, char player_symbol, char path_symbol, bool isViewDistMode)
{
    string empty_col = "";
    string col_padding = "";
    string bar = "";
    for(int i = 0; i < col_width; i++)
    {
        empty_col += " ";
        bar += "-";
        if(i < col_width - 1)
        {
            col_padding += " ";
        }
    }

    
    maze[start_y][start_x] = '>';

    if(isViewDistMode)
        displayMazeViewDist(maze, view_distance, {start_x, start_y}, empty_col, col_padding, bar, path_symbol);
    else
    {
        view_distance = {0, 0, 0, 0}; 
        view_distance = displayMazeFog(maze, view_distance, {start_x, start_y}, WIDTH, HEIGTH, col_padding, bar, path_symbol);
    }
    cin.get();
    recurssiveMazeTraveseEngine(maze, start_x, start_y, end_x, end_y, start_x, start_y, direction, view_distance, WIDTH, HEIGTH, player_symbol, path_symbol, isViewDistMode, empty_col, col_padding, bar);
    
    cin.get();
}

void recurssiveMazeTraveseEngine(vector<vector<char>> &maze, int start_x, int start_y, int end_x, int end_y, int current_x, int current_y, int direction, array<array<int, 2>, 2> view_distance, int WIDTH, int HEIGTH, char player_symbol, char path_symbol, bool isViewDistMode, string empty_col, string col_padding, string bar)
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
                
                if(isViewDistMode)
                    displayMazeViewDist(maze, view_distance, {temp_x, temp_y}, empty_col, col_padding, bar, path_symbol);
                else
                {
                    view_distance = displayMazeFog(maze, view_distance, {temp_x, temp_y}, WIDTH, HEIGTH, col_padding, bar, path_symbol);
                }

                recurssiveMazeTraveseEngine(maze, start_x, start_y, end_x, end_y, temp_x, temp_y, test_direction, view_distance, WIDTH, HEIGTH, player_symbol, path_symbol, isViewDistMode, empty_col, col_padding, bar);
                break;
            }

            test_direction = ++test_direction % 4;
        }
    }
}