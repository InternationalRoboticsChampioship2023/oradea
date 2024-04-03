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
<<<<<<< HEAD
        if (maze[x][y].up == false && dist_maze[x - 1][y] > dist_maze[x][y] + 1)
=======
        if (maze[x][y].up == false && dist_maze[x-1][y] > dist_maze[x][y] + 1)
        {
            dist_maze[x-1][y] = dist_maze[x][y] + 1;
            recurs(x-1, y);
        }
        if (maze[x][y].left == false && dist_maze[x][y-1] > dist_maze[x][y] + 1)
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58
        {
            dist_maze[x][y-1] = dist_maze[x][y] + 1;
            recurs(x, y-1);
        }
<<<<<<< HEAD
        if (maze[x][y].left == false && dist_maze[x][y - 1] > dist_maze[x][y] + 1)
        {
            dist_maze[x][y - 1] = dist_maze[x][y] + 1;
            recurs(x, y - 1);
        }
        if (maze[x][y].right == false && dist_maze[x][y + 1] > dist_maze[x][y] + 1)
=======
        if (maze[x][y].right == false && dist_maze[x][y+1] > dist_maze[x][y] + 1)
        {
            dist_maze[x][y+1] = dist_maze[x][y] + 1;
            recurs(x, y+1);
        }
        if (maze[x][y].down == false && dist_maze[x+1][y] > dist_maze[x][y] + 1)
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58
        {
            dist_maze[x+1][y] = dist_maze[x][y] + 1;
            recurs(x+1, y);
        }
        if (maze[x][y].down == false && dist_maze[x + 1][y] > dist_maze[x][y] + 1)
        {
            dist_maze[x + 1][y] = dist_maze[x][y] + 1;
            recurs(x + 1, y);
        }
    }
}

<<<<<<< HEAD
int drum[256];
int drum_efic[256];
int length = INT16_MAX;
int cnt_efic = INT16_MAX;

void verif(int i) {
    if (i < length) {
        length = i;
    }
    int cnt = 0;
    for (int j = 1; j < i; j++) {
        if (drum[j] != drum[j - 1]) {
            cnt++;
        }
    }
    if (cnt < cnt_efic) {
        for (int j = 0; j < i; j++) {
            drum_efic[j] = drum[j];
        }
        cnt_efic = cnt;
    }
}


void drum_bun(int x, int y, int i) {
    if (dist_maze[x][y] <= 0) {
        verif(i);
    }
    else {
        if (maze[x][y].up == false && dist_maze[x - 1][y] == dist_maze[x][y] - 1) {
            drum[i] = 1;
            drum_bun(x - 1, y, i + 1);
        }
        if (maze[x][y].left == false && dist_maze[x][y - 1] == dist_maze[x][y] - 1) {
            drum[i] = 0;
            drum_bun(x, y - 1, i + 1);
        }
        if (maze[x][y].right == false && dist_maze[x][y + 1] == dist_maze[x][y] - 1) {
            drum[i] = 2;
            drum_bun(x, y + 1, i + 1);
        }
        if (maze[x][y].down == false && dist_maze[x + 1][y] == dist_maze[x][y] - 1) {
            drum[i] = 3;
            drum_bun(x + 1, y, i + 1);
        }
    }
}





/*
=======
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58
int drum_maze[16][16];
void drum(int x, int y) {
    drum_maze[x][y] = dist_maze[x][y];
    if (maze[x][y].up == false && dist_maze[x - 1][y] == drum_maze[x][y] - 1) {
        drum(x - 1, y);
    }
<<<<<<< HEAD
    if (maze[x][y].left == false && dist_maze[x][y - 1] == drum_maze[x][y] - 1) {
        drum(x, y - 1);
    }
    if (maze[x][y].right == false && dist_maze[x][y + 1] == drum_maze[x][y] - 1) {
        drum(x, y + 1);
=======
    if (maze[x][y].left == false && dist_maze[x][y-1] == drum_maze[x][y] - 1) {
        drum(x, y-1);
    }
    if (maze[x][y].right == false && dist_maze[x][y+1] == drum_maze[x][y] - 1) {
        drum(x, y+1);
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58
    }
    if (maze[x][y].down == false && dist_maze[x + 1][y] == drum_maze[x][y] - 1) {
        drum(x + 1, y);
    }
}
<<<<<<< HEAD
*/
=======
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58

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

    drum_bun(0, 0, 0);
    for (int i = 0; i < length; i++) {
        cout << drum_efic[i] << " ";
    }

<<<<<<< HEAD
    /*
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            drum_maze[i][j] = -1;
        }
    }
    drum_maze[7][7] = 0;
    drum_maze[7][8] = 0;
    drum_maze[8][7] = 0;
    drum_maze[8][8] = 0;
=======
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58
    drum(0, 0);
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cout << drum_maze[i][j] << " ";
<<<<<<< HEAD
            if (drum_maze[i][j] < 0  || drum_maze[i][j] > 9) {
=======
            if (drum_maze[i][j] < 10) {
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << "\n" << endl;
<<<<<<< HEAD
    */
=======
>>>>>>> cac2e18736c09c2f7da9f52c4bca6a1d41d9ce58
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