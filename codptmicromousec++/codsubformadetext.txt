#include <iostream>
#include <vector>
#include <climits>

using namespace std;//left, up, right, down
struct cell_walls {
    bool left;
    bool up;
    bool right;
    bool down;
};
/*
int drum_maze[16][16];
void drum(int x, int y) {
    drum_maze[x][y] = dist_maze[x][y];
    if (maze[x][y].up == false && dist_maze[x - 1][y] == drum_maze[x][y] - 1) {
        drum(x - 1, y);
    }
    if (maze[x][y].left == false && dist_maze[x][y - 1] == drum_maze[x][y] - 1) {
        drum(x, y - 1);
    }
    if (maze[x][y].right == false && dist_maze[x][y + 1] == drum_maze[x][y] - 1) {
        drum(x, y + 1);
    }
    if (maze[x][y].down == false && dist_maze[x + 1][y] == drum_maze[x][y] - 1) {
        drum(x + 1, y);
    }
}
*/

cell_walls maze[16][16] = {
{1,1,1,0, 1,1,1,0, 1,1,1,0, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,1,0},
{1,0,1,0, 1,0,1,0, 1,0,0,0, 0,0,1,0, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,0},
{1,0,0,1, 0,0,0,0, 0,0,1,0, 1,0,1,0, 1,0,1,0, 1,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,1,0, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,1,0, 1,0,1,0},
{1,1,0,0, 0,0,1,1, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,0,0,0, 0,0,1,1, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,0, 1,0,1,0},
{1,0,0,0, 0,1,0,1, 0,0,1,1, 1,0,1,0, 1,0,1,0, 1,0,0,0, 0,1,0,1, 0,1,0,0, 0,0,0,1, 0,1,1,0, 1,0,0,1, 0,1,0,1, 0,1,0,1, 0,1,1,0, 1,0,1,0, 1,0,1,0},
{1,0,0,0, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,1,0, 1,0,1,0, 1,1,0,0, 0,0,0,1, 0,1,1,1, 1,0,1,1, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,1,0, 1,0,1,0},
{1,0,1,0, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,0,0, 0,0,0,0, 0,1,1,1, 1,1,0,0, 0,1,1,0, 1,0,0,1, 0,1,0,1, 0,1,0,1, 0,1,1,0, 1,0,1,0, 1,0,1,0},
{1,0,1,0, 1,0,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,1,1, 1,1,0,0, 0,0,1,0, 1,0,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,1,1, 1,0,1,1},
{1,0,1,0, 1,0,1,0, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,1,0, 1,1,1,0, 1,0,0,1, 0,0,1,1, 1,0,0,0, 0,1,0,0, 0,1,0,1, 0,1,0,0, 0,1,0,1, 0,1,0,0, 0,1,1,0},
{1,0,1,0, 1,0,0,1, 0,0,0,1, 0,1,0,1, 0,1,1,0, 1,0,1,0, 1,0,0,0, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,0,1, 0,1,0,0, 0,0,0,0, 0,1,0,1, 0,0,1,0, 1,0,1,0},
{1,0,0,0, 0,1,0,1, 0,1,0,1, 0,1,1,0, 1,0,1,0, 1,0,1,0, 1,0,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,0,1, 0,1,0,1, 0,0,1,0, 1,0,1,0},
{1,0,0,0, 0,1,0,1, 0,1,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,0,1, 0,0,1,0},
{1,0,0,1, 0,1,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,1,0, 1,0,1,0},
{1,1,0,0, 0,0,0,0, 0,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,0,1,1},
{1,0,1,0, 1,0,1,0, 1,0,0,0, 0,0,1,0, 1,0,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,1,0},
{1,0,1,1, 1,0,1,1, 1,0,1,1, 1,0,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,1}
};

int dist_maze[16][16];
int mdrumuri[16][16];
int sz = 16;

void floodfill(int x, int y, int cost) {
    // Base case: out of bounds or the cell has been visited before
    if (x < 0 || x >= sz || y < 0 || y >= sz || dist_maze[x][y] <= cost)
        return;

    // Update distance and recursively visit neighboring cells
    dist_maze[x][y] = cost;

    if (!maze[x][y].up)
        floodfill(x - 1, y, cost + 1);
    if (!maze[x][y].down)
        floodfill(x + 1, y, cost + 1);
    if (!maze[x][y].left)
        floodfill(x, y - 1, cost + 1);
    if (!maze[x][y].right)
        floodfill(x, y + 1, cost + 1);
}



vector<pair<int, int>> findBestRoute(int start_x, int start_y) {
    // If the starting point has cost 0, return directly
    if (dist_maze[start_x][start_y] == 0) {
        return { {start_x, start_y} };
    }

    // Explore the best route and store it into a vector
    vector<pair<int, int>> best_route;
    int x = start_x, y = start_y;
    while (dist_maze[x][y] > 0) {
        cout << "Exploring cell: (" << x << ", " << y << ")" << endl;
        best_route.push_back({ x, y });
        // Choose the neighboring cell with the next lowest cost
        if (x > 0 && dist_maze[x - 1][y] == dist_maze[x][y] - 1) {
            cout << "Selected neighbor: (" << x - 1 << ", " << y << ")" << endl;
            x--;
        }
        else if (y > 0 && dist_maze[x][y - 1] == dist_maze[x][y] - 1) {
            cout << "Selected neighbor: (" << x << ", " << y - 1 << ")" << endl;
            y--;
        }
        else if (x < 15 && dist_maze[x + 1][y] == dist_maze[x][y] - 1) {
            cout << "Selected neighbor: (" << x + 1 << ", " << y << ")" << endl;
            x++;
        }
        else if (y < 15 && dist_maze[x][y + 1] == dist_maze[x][y] - 1) {
            cout << "Selected neighbor: (" << x << ", " << y + 1 << ")" << endl;
            y++;
        }
        else {
            // No valid neighboring cell found
            cout << "Error: No valid neighboring cell found from (" << x << ", " << y << ")" << endl;
            return {}; // Return an empty vector indicating failure
        }
    }

    // Add the last cell (current cell) to the best route
    best_route.push_back({ x, y });

    // Reverse the route to get it in correct order
    reverse(best_route.begin(), best_route.end());

    return best_route;
}


vector<string> generateMovementInstructions(const vector<pair<int, int>>& best_route) {
    vector<string> instructions;

    // Start generating movement instructions from the second last point to the first point
    for (size_t i = best_route.size() - 1; i > 0; --i) {
        int curr_x = best_route[i].first;
        int curr_y = best_route[i].second;
        int next_x = best_route[i - 1].first;
        int next_y = best_route[i - 1].second;

        // Calculate the change in x and y coordinates
        int dx = next_x - curr_x;
        int dy = next_y - curr_y;

        // Generate movement instruction based on the change in coordinates
        if (dx == 1) {
            instructions.push_back("Move forward");
        }
        else if (dx == -1) {
            instructions.push_back("Move backward");
        }
        else if (dy == 1) {
            instructions.push_back("Move right");
        }
        else if (dy == -1) {
            instructions.push_back("Move left");
        }
        else {
            instructions.push_back("Invalid movement");
        }
    }

    return instructions;
}







int main()
{

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            dist_maze[i][j] = INT16_MAX;
            mdrumuri[i][j] = -1;
        }
    }
    floodfill(7,7,0);
    floodfill(7, 8, 0);
    floodfill(8, 7, 0);
    floodfill(8, 8, 0);
    dist_maze[7][7] = 0;
    dist_maze[7][8] = 0;
    dist_maze[8][7] = 0;
    dist_maze[8][8] = 0;
    mdrumuri[7][7] = 0;
    mdrumuri[7][8] = 0;
    mdrumuri[8][7] = 0;
    mdrumuri[8][8] = 0;
    
    
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cout << dist_maze[i][j] << " ";
            if (dist_maze[i][j] < 10) {
                cout << " ";
            }
            
        }
        cout << endl;
    }
    cout << "\n" << endl;
    vector<pair<int, int>> best_route = findBestRoute(0, 0);
    cout << "Best route:\n";
    for (int i = best_route.size() - 1; i >= 0; --i) {
        cout << "(" << best_route[i].first << ", " << best_route[i].second << ") ";
    }
    cout << endl;
    vector<string> instructions = generateMovementInstructions(best_route);

    // Display the movement instructions
    cout << "Movement Instructions:" << endl;
    for (const string& instruction : instructions) {
        cout << instruction << endl;
    }


}


