// creare labirint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

struct cell_walls {
    bool left;
    bool up;
    bool right;
    bool down;
};

cell_walls maze[16][16] = {
{1,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,1,0},
{1,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,0,1, 0,0,1,1}
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
        //cout << "Exploring cell: (" << x << ", " << y << ")" << endl;
        best_route.push_back({ x, y });
        // Choose the neighboring cell with the next lowest cost
        if ((x > 0 && dist_maze[x - 1][y] == dist_maze[x][y] - 1)&&maze[x][y].up == 0) {
            //cout << "Selected neighbor: (" << x - 1 << ", " << y << ")" << endl;
            x--;
        }
        else if ((y > 0 && dist_maze[x][y - 1] == dist_maze[x][y] - 1)&& maze[x][y].left == 0) {
            //cout << "Selected neighbor: (" << x << ", " << y - 1 << ")" << endl;
            y--;
        }
        else if ((x < 15 && dist_maze[x + 1][y] == dist_maze[x][y] - 1) && maze[x][y].down == 0) {
            //cout << "Selected neighbor: (" << x + 1 << ", " << y << ")" << endl;
            x++;
        }
        else if ((y < 15 && dist_maze[x][y + 1] == dist_maze[x][y] - 1) && maze[x][y].right == 0) {
            //cout << "Selected neighbor: (" << x << ", " << y + 1 << ")" << endl;
            y++;
        }
        else {
            // No valid neighboring cell found
            //cout << "Error: No valid neighboring cell found from (" << x << ", " << y << ")" << endl;
            return {}; // Return an empty vector indicating failure
        }
    }

    // Add the last cell (current cell) to the best route
    best_route.push_back({ x, y });

    // Reverse the route to get it in correct order
    reverse(best_route.begin(), best_route.end());

    return best_route;
}

int main()
{
    int x, y;
    cell_walls cell;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cout << maze[i][j].left << "," << maze[i][j].up << "," << maze[i][j].right << "," << maze[i][j].down << ", ";
        }
        cout << endl;
    }
    while (1) {
        cin >> x >> y;
        cin >> cell.left;
        cin >> cell.up;
        cin >> cell.right;
        cin >> cell.down;
        maze[x][y] = cell;
        if (x > 0) {
            maze[x - 1][y].down = cell.up;
        }
        if (x < 16) {
            maze[x + 1][y].up = cell.down;
        }
        if (y > 0) {
            maze[x][y-1].right = cell.left;
        }
        if (y<16) {
            maze[x][y+1].left = cell.right;
        }
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                cout << maze[i][j].left << "," << maze[i][j].up << "," << maze[i][j].right << "," << maze[i][j].down << ", ";
            }
            cout << endl;
        }

        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                dist_maze[i][j] = INT16_MAX;
                mdrumuri[i][j] = -1;
            }
        }
        floodfill(7, 7, 0);
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

        vector<pair<int, int>> best_route = findBestRoute(2, 2);
        cout << "Best route:\n";
        for (int i = best_route.size() - 1; i >= 0; --i) {
            cout << "(" << best_route[i].first << ", " << best_route[i].second << ") ";
        }
        cout << endl;

        vector<int> directions;
        for (int i = best_route.size() - 1; i > 0; i--) {
            if (best_route[i - 1].first < best_route[i].first) {
                directions.push_back(1);
            }
            else if (best_route[i - 1].first > best_route[i].first) {
                directions.push_back(3);
            }
            else if (best_route[i - 1].second > best_route[i].second) {
                directions.push_back(2);
            }
            else if (best_route[i - 1].second < best_route[i].second) {
                directions.push_back(0);
            }
        }
        for (int i = 1; i < directions.size(); i++) {
            if (directions[i - 1] == directions[i]) {
                cout << "m180"<<endl;
            }
            else {
                cout << "m180" << endl;
                cout << "r" << directions[i]<<endl;
            }
        }
        cout << "m180";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
