#include <iostream>

using namespace std;//left, up, right, down
struct cell_walls {
    bool left;
    bool up;
    bool right;
    bool down;
};

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
int sz = 16;

void recurs(int x, int y) {
    if ((x >= 0 && x < 16) && (y >= 0 && y < 16)) {
        if (maze[x][y].up == false && dist_maze[x-1][y] > dist_maze[x][y] + 1)
        {
            dist_maze[x-1][y] = dist_maze[x][y] + 1;
            recurs(x-1, y);
        }
        if (maze[x][y].left == false && dist_maze[x][y-1] > dist_maze[x][y] + 1)
        {
            dist_maze[x][y-1] = dist_maze[x][y] + 1;
            recurs(x, y-1);
        }
        if (maze[x][y].right == false && dist_maze[x][y+1] > dist_maze[x][y] + 1)
        {
            dist_maze[x][y+1] = dist_maze[x][y] + 1;
            recurs(x, y+1);
        }
        if (maze[x][y].down == false && dist_maze[x+1][y] > dist_maze[x][y] + 1)
        {
            dist_maze[x+1][y] = dist_maze[x][y] + 1;
            recurs(x+1, y);
        }
    }
}

int drum_maze[16][16];
void drum(int x, int y) {
    drum_maze[x][y] = dist_maze[x][y];
    if (maze[x][y].up == false && dist_maze[x - 1][y] == drum_maze[x][y] - 1) {
        drum(x - 1, y);
    }
    if (maze[x][y].left == false && dist_maze[x][y-1] == drum_maze[x][y] - 1) {
        drum(x, y-1);
    }
    if (maze[x][y].right == false && dist_maze[x][y+1] == drum_maze[x][y] - 1) {
        drum(x, y+1);
    }
    if (maze[x][y].down == false && dist_maze[x + 1][y] == drum_maze[x][y] - 1) {
        drum(x + 1, y);
    }
}

int main()
{

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            dist_maze[i][j] = INT16_MAX;
        }
    }
    dist_maze[7][7] = 0;
    dist_maze[7][8] = 0;
    dist_maze[8][7] = 0;
    dist_maze[8][8] = 0;
    recurs(7, 7);
    recurs(7, 8);
    recurs(8, 7);
    recurs(8, 8);
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


    drum(0, 0);
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cout << drum_maze[i][j] << " ";
            if (drum_maze[i][j] < 10) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << "\n" << endl;
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