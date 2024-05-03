#include <List.hpp>
//left, up, right, down
struct cell_walls {
    bool left;
    bool up;
    bool right;
    bool down;
};

struct br{//best_route
  int first;
  int second;
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


List<br> best_route;
void findBestRoute(int start_x, int start_y) {
    // If the starting point has cost 0, return directly

    // Explore the best route and store it into a vector
    int x = start_x, y = start_y;
    while (dist_maze[x][y] > 0) {
        //cout << "Exploring cell: (" << x << ", " << y << ")" << endl;
        br aux;
        aux.first = x;
        aux.second =y;
        best_route.addFirst(aux);
        // Choose the neighboring cell with the next lowest cost
        if (x > 0 && dist_maze[x - 1][y] == dist_maze[x][y] - 1) {
            //cout << "Selected neighbor: (" << x - 1 << ", " << y << ")" << endl;
            x--;
        }
        else if (y > 0 && dist_maze[x][y - 1] == dist_maze[x][y] - 1) {
            //cout << "Selected neighbor: (" << x << ", " << y - 1 << ")" << endl;
            y--;
        }
        else if (x < 15 && dist_maze[x + 1][y] == dist_maze[x][y] - 1) {
            //cout << "Selected neighbor: (" << x + 1 << ", " << y << ")" << endl;
            x++;
        }
        else if (y < 15 && dist_maze[x][y + 1] == dist_maze[x][y] - 1) {
            //cout << "Selected neighbor: (" << x << ", " << y + 1 << ")" << endl;
            y++;
        }//carefull for no solution exception
    }

    // Add the last cell (current cell) to the best route
    br aux;
    aux.first = x;
    aux.second =y;
    best_route.addFirst(aux);

    // Reverse the route to get it in correct order
    //reverse(best_route.begin(), best_route.end());
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
            Serial.print(dist_maze[i][j]);
            Serial.print(" ");
            if (dist_maze[i][j] < 10) {
                Serial.print(" ");
            }
            
        }
        Serial.println();
    }
    Serial.println();
    findBestRoute(0, 0);
    Serial.print("Best route:\n");
    for (int i = best_route.getSize() - 1; i >= 0; --i) {
        Serial.print("(");
        Serial.print(best_route[i].first);
        Serial.print(", ");
        Serial.print(best_route[i].second);
        Serial.print(") ");
    }
    Serial.println();

    List<int> directions;
    for (int i = best_route.getSize()-1; i >0; i--) {
        if (best_route[i - 1].first < best_route[i].first) {
            directions.add(1);
        }
        else if (best_route[i - 1].first > best_route[i].first) {
            directions.add(3);
        }
        else if (best_route[i - 1].second > best_route[i].second) {
            directions.add(2);
        }
        else if (best_route[i - 1].second < best_route[i].second) {
            directions.add(0);
        }
    }
    int cnt = 1;
    for (int i = 1; i < directions.getSize(); i++) {
        if (directions[i - 1] == directions[i]) {
            cnt++;
        }
        else {
            Serial.print("m");
            Serial.print(cnt*160);
            Serial.println();
            cnt = 1;
            if (directions[i - 1] < (directions[i] - 1) % 4) {
                Serial.println("r90");
            }
            else if (directions[i - 1] > (directions[i] - 1) % 4) {
                Serial.println("r-90");
            }
        }
    }
    Serial.print("m160");

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  main();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
