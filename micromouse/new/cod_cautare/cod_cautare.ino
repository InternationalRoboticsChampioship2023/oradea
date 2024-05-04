#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <List.hpp>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

const float RTD = 57.2957795;

Adafruit_MPU6050 mpu;
float desired_angle=0, real_angle=0;
float currentTime, previousTime;
sensors_event_t a, g, temp; 
float error=0;

int ms1=4;
int ms2=13;
int md1=16;
int md2=17;
#define EncoderS 34 
#define EncoderD 36
int Count_pulsesS = 0;
int Count_pulsesD = 0;

int avg;
float diam = 91.1061;
int vs, vd, vs_old, vd_old;

const int freq = 1000;
const int ms1Channel = 0;
const int ms2Channel = 1;
const int md1Channel = 2;
const int md2Channel = 3;
const int resolution = 8;

int rotate_speed = 110;
int stop_speed = -20;
int move_speed = 110;
int correction_speed = 40;
int corection_encoder_speed = 70;

struct cell_walls {
    bool left;
    bool up;
    bool right;
    bool down;
};

struct coord{
  int x;
  int y;
  int dir;//0-left, 1-up, 2-right, 3-down
}poz;

struct br{//best_route
  int first;
  int second;
};

const int trigPin = 32;
const int echoPinS = 26;
const int echoPinM = 25;
const int echoPinD = 33;

int distforwall = 6;

struct cell_sensor{
  bool wallS;
  bool wallM;
  bool wallD;
};

struct instruction{
  char mode;
  int value;//in mm(no negative values) or degrees
};
List<instruction> instruct;

int cell_size = 180;

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
List<br> best_route;

void setup() {
  // put your setup code here, to run once:
  poz.x=0;
  poz.y=0;
  poz.dir = -1;
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinS, INPUT);
  pinMode(echoPinM, INPUT);
  pinMode(echoPinD, INPUT);
  if(!SD.begin(5)){
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }

  mpu.begin();
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  get_error();
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  digitalWrite(ms1, LOW);
  digitalWrite(ms2, LOW);
  digitalWrite(md1, LOW);
  digitalWrite(md2, LOW);
  ledcSetup(ms1Channel, freq, resolution);
  ledcSetup(ms2Channel, freq, resolution);
  ledcSetup(md1Channel, freq, resolution);
  ledcSetup(md2Channel, freq, resolution);
  ledcAttachPin(ms1, ms1Channel);
  ledcAttachPin(ms2, ms2Channel);
  ledcAttachPin(md1, md1Channel);
  ledcAttachPin(md2, md2Channel);
  attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderD),DC_MotorD,RISING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!(poz.x==7||poz.x==8)&&!(poz.y==7&&poz.y==8)){
    maze_work();
  }
  else{
    motors_stop('s');
    floodfill(7, 7, 0);
    floodfill(7, 8, 0);
    floodfill(8, 7, 0);
    floodfill(8, 8, 0);
    dist_maze[7][7] = 0;
    dist_maze[7][8] = 0;
    dist_maze[8][7] = 0;
    dist_maze[8][8] = 0;
    findBestRoute(poz.x,poz.y);
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
      SD.begin(5);
      SD.remove("/steps.txt"); // delete the file if existed
      File file = SD.open("/steps.txt", FILE_WRITE);
      int cnt = 1;
      for (int i = 1; i < directions.getSize(); i++) {
          if (directions[i - 1] == directions[i]) {
              cnt++;
          }
          else {
              file.print("m");
            file.print(cnt*cell_size);
            file.println();
            cnt = 1;
            if (directions[i - 1] < (directions[i] - 1) % 4) {
                file.println("r90");
            }
            else if (directions[i - 1] > (directions[i] - 1) % 4) {
                file.println("r-90");
            }
        }
    }
    file.print("m180");//m cell_size
    file.print("e");
    file.close();
  }
  while(1){
    delay(1);
  }
}

//always put the mouse in the start cell with wall on the left and front
void maze_work(){
  cell_sensor cs = get_walls();
  //generate te walls of the cell;
  if(poz.dir= -1){
    if(cs.wallS == 0){
      //roate 90
      poz.dir = 2;
    }else if(cs.wallM == 0) {
      //rotate 180
      poz.dir = 3;
    }
  }
  if(poz.dir == 0){
    maze[poz.x][poz.y].up == cs.wallD;
    maze[poz.x][poz.y].left = cs.wallM;
    maze[poz.x][poz.y].down == cs.wallS;
  }else if(poz.dir == 1){
    maze[poz.x][poz.y].up = cs.wallM;
    maze[poz.x][poz.y].left = cs.wallS;
    maze[poz.x][poz.y].right = cs.wallD;
  }else if(poz.dir == 2){
    maze[poz.x][poz.y].up = cs.wallS;
    maze[poz.x][poz.y].down = cs.wallD;
    maze[poz.x][poz.y].right = cs.wallM;
  }else if(poz.dir == 3){
    maze[poz.x][poz.y].left = cs.wallD;
    maze[poz.x][poz.y].down = cs.wallM;
    maze[poz.x][poz.y].right = cs.wallS;
  }
  //change the neighbour if possible
  if (poz.x > 0) {
    maze[poz.x - 1][poz.y].down = maze[poz.x][poz.y].up;
  }
  if (poz.x < 16) {
     maze[poz.x + 1][poz.y].up = maze[poz.x][poz.y].down;
  }
  if (poz.y > 0) {
      maze[poz.x][poz.y-1].right = maze[poz.x][poz.y].left;
  }
  if (poz.y<16) {
      maze[poz.x][poz.y+1].left = maze[poz.x][poz.y].right;
  }
  //reset dist_maze;
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < sz; j++) {
        dist_maze[i][j] = INT16_MAX;
    }
  }
  //recalculate dist_maze
  floodfill(7, 7, 0);
  floodfill(7, 8, 0);
  floodfill(8, 7, 0);
  floodfill(8, 8, 0);
  dist_maze[7][7] = 0;
  dist_maze[7][8] = 0;
  dist_maze[8][7] = 0;
  dist_maze[8][8] = 0;
  findBestRoute(poz.x,poz.y);
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
    instruction aux;
      if (directions[0] == directions[1]) {
          move_mouse_search('m',cell_size);
          //aux.mode=='m';
          //aux.value = cell_size;
          //instruct.add(aux);
      }
      else {
        poz.dir = directions[1];
        move_mouse_search('m',cell_size);
        move_mouse_search('r', directions[1]);
          //instruction aux;
          //aux.mode=='m';
          //aux.value = cell_size;
          //instruct.add(aux);
          //aux.mode='r';
          //aux.value=directions[i];
          //instruct.add(aux);
      }
}

void move_mouse_search(char m, int value){
  if(m == 'm'){
      Count_pulsesS = 0;
      Count_pulsesD = 0;
      avg=0;
      int pls = (value * 110)/diam;
      while(avg!=pls){
        Serial.print(avg);
        Serial.print(" ");
        Serial.println(pls);
        vs = move_speed;
        vd = move_speed;
        if(avg>pls){
          vs=-vs;
          vd=-vd;
        }
        correction();
        motors(vs, vd);
      }
      motors_stop('m');
      delay(1000);
    }else if(m=='r'){
      desired_angle=value*90;
      while(real_angle>desired_angle+0.3||real_angle<desired_angle-0.3){
        Serial.print(real_angle);
        Serial.print(" ");
        Serial.println(desired_angle);
        rotate();  
      }
      motors_stop('r');
      delay(1000);
    }
}

cell_sensor get_walls(){
  cell_sensor aux;
  float distanceS, distanceM, distanceD;
  distanceS = get_sensor(echoPinS);
  distanceM = get_sensor(echoPinM);
  distanceD = get_sensor(echoPinD);
  if(distanceS < 6){//in cell dist from sensor to wall is 3.1cm
    aux.wallS = 1;
  }else{
    aux.wallS = 0;
  }
  if(distanceM < 6){
    aux.wallM = 1;
  }else{
    aux.wallM = 0;
  }
  if(distanceD < 6){
    aux.wallD = 1;
  }else{
    aux.wallD = 0;
  }
  return aux;
}

int get_sensor(int pin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float d;
  d = pulseIn(pin, HIGH);
  delay(60);
  return(d*.0343)/2;
}


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

void findBestRoute(int start_x, int start_y) {
    // If the starting point has cost 0, return directly
    best_route.clear();
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

void motors_stop(char m){
  if(m == 'm'){
    motors(-255*sgn(vs_old),-255*sgn(vd_old));
    delay(move_speed/5);
    motors(stop_speed,stop_speed);
  }else if(m == 'r'){
    motors(sgn(vs_old)*-255,sgn(vd_old)*-255);
    delay(rotate_speed/4);
    motors(sgn(vs_old)*stop_speed,sgn(vd_old)*stop_speed);
  }else{
    motors(stop_speed,stop_speed);
  }
}

void rotate(){
  vs=0;
  vd=0;
  get_angle(real_angle);
  if(real_angle>desired_angle){
    vs -=rotate_speed;
    vd+=rotate_speed;
  }else if(real_angle<desired_angle){
    vd-=rotate_speed;
    vs+=rotate_speed;
  }
  if(real_angle!=desired_angle){
    motors(vs, vd);
  }
}

void correction(){
  get_angle(real_angle);
  if((int)real_angle>(int)desired_angle){
    vs -=correction_speed;
  }else if((int)real_angle<(int)desired_angle){
    vd-=correction_speed;
  }
}

void get_angle(float& yaw){
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  float elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  /* Get new sensor events with the readings */
  mpu.getEvent(&a, &g, &temp);
  yaw -= (g.gyro.z-error) *elapsedTime*RTD ;
}

void motors(int vst, int vdr){
  if(vst >= 0){
    ledcWrite(ms2Channel, vst);
    ledcWrite(ms1Channel, 0);
  }else{
    ledcWrite(ms2Channel, 0);
    ledcWrite(ms1Channel, abs(vst));
  }
  if(vdr >= 0){
    ledcWrite(md2Channel, vdr);
    ledcWrite(md1Channel, 0);
  }else{
    ledcWrite(md2Channel, 0);
    ledcWrite(md1Channel, abs(vdr));
  }
  vs_old = vst;
  vd_old = vdr;
}

void get_error(){
  int steps = 2000;
  mpu.getEvent(&a, &g, &temp);
  for(int i = 0;i<steps;i++){
    error +=g.gyro.z;
  }
  error /=steps;
}

void DC_MotorS(){
  int ES = 35;
  pinMode(ES, INPUT);
  if(digitalRead(ES)==HIGH){
    Count_pulsesS--; 
  }else{
    Count_pulsesS++; 
  }
  avg = (Count_pulsesS + Count_pulsesD)/2;
}
void DC_MotorD(){
  int ED = 39;
  pinMode(ED, INPUT);
  if(digitalRead(ED)==HIGH){
    Count_pulsesD++; 
  }else{
    Count_pulsesD--;
  }
  avg = (Count_pulsesS + Count_pulsesD)/2;
}
