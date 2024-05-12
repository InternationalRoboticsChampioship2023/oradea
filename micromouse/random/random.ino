//read the values from the SD card and executes them
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <List.hpp>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

int cell_size = 160;

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

int rotate_speed = 80;
int stop_speed = -20;
int move_speed = 85;
int correction_speed = 30;
int corection_encoder_speed = 70;

struct cell_sesnor{
  bool wallS;
  bool wallM;
  bool wallD;
};

const int trigPin = 32;
const int echoPinS = 26;
const int echoPinM = 25;
const int echoPinD = 33;

int distforwall = 6;

void setup(){
  Serial.begin(115200);
  delay(1000);
  mpu.begin();
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);
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

  pinMode(trigPin, OUTPUT);
  pinMode(echoPinS, INPUT);
  pinMode(echoPinM, INPUT);
  pinMode(echoPinD, INPUT);
}

void loop(){
  cell_sesnor walls = get_walls();
  if(walls.wallS ==  0 && (walls.wallM==1 && walls.wallD==1)){
    di(-1);
  }else if(walls.wallM == 0 && (walls.wallS==1 && walls.wallD==1)){
    di(0);
  }else if(walls.wallD == 0 && (walls.wallM==1 && walls.wallS==1)){
    di(1);
  }else if((walls.wallS == 0 && walls.wallM == 0)&&walls.wallD==1){
    di(random(-1,0));
  }else if((walls.wallM == 0 && walls.wallD==0)&&walls.wallS==1){
    di(random(0,1));
  }else if((walls.wallS==0 && walls.wallD==0
  )&&walls.wallM==1){
    int x=random(0,1);
    if(x==0)x--;
    di(x);
  }else if(walls.wallS == 0 && (walls.wallM==0 && walls.wallD==0)){
    di(random(-1,1));
  }else if(walls.wallS == 1 && (walls.wallM==1 && walls.wallD==1)){
    di(-1);
    di(-1);
  }
}

void di(int i){//-1 ->left, 0->front, 1->right
  desired_angle+=90*i;
    while(real_angle>desired_angle+0.05||real_angle<desired_angle-0.05){
        //Serial.print(real_angle);
        //Serial.print(" ");
        //Serial.println(desired_angle);
        rotate();  
    }
    desired_angle = real_angle;
    if(i!=0){
      motors_stop('r');
      delay(500);
    }
    Count_pulsesS = 0;
    Count_pulsesD = 0;
    avg=0;
    int pls = (cell_size * 110)/diam;
    while(avg!=pls){
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
      delay(500);
}

void motors_stop(char m){
  if(m == 'm'){
    motors(-255*sgn(vs_old),-255*sgn(vd_old));
    delay(move_speed/5);
    motors(stop_speed,stop_speed);
  }else if(m == 'r'){
    //motors(sgn(vs_old)*-255,sgn(vd_old)*-255);
    //delay(rotate_speed/2);
    //motors(sgn(vs_old)*stop_speed,sgn(vd_old)*stop_speed);
    motors(0,0);
  }else{
    motors(stop_speed,stop_speed);
  }
}

cell_sesnor get_walls(){
  cell_sesnor aux;
  float distanceS, distanceM, distanceD;
  distanceS = get_sensor(echoPinS);
  distanceM = get_sensor(echoPinM);
  distanceD = get_sensor(echoPinD);
  if(distanceS < distforwall){//in cell dist from sensor to wall is 3.1cm
    aux.wallS = 1;
  }else{
    aux.wallS = 0;
  }
  if(distanceM < distforwall){
    aux.wallM = 1;
  }else{
    aux.wallM = 0;
  }
  if(distanceD < distforwall){
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
  delay(1);
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
