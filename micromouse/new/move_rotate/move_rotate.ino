//read the values from the SD card and executes them
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
int stop_speed = -45;
int move_speed = 110;
int correction_speed = 40;



struct instruction{
  char mode;
  int value;//in mm(no negative values) or degrees
};
List<instruction> instruct;

void setup(){
  Serial.begin(115200);
  if(!SD.begin(5)){
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }
  
  readFile(SD, "/instruct.txt");

  mpu.begin();
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
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

void loop(){
  if(instruct.getSize()!=0){
    Serial.print(instruct[0].mode);
    if(instruct[0].mode == 'm'){
      Serial.print(instruct[0].value);
      Count_pulsesS = 0;
      Count_pulsesD = 0;
      avg=0;
      int pls = (instruct[0].value * 110)/diam;
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
      vs = stop_speed;
      vd = stop_speed;
      motors_stop('m');
      instruct.removeFirst();
      delay(1000);
      


      
    }else if(instruct[0].mode=='r'){
      Serial.print(instruct[0].value);
      desired_angle+=instruct[0].value;
      while((int)real_angle!=(int)desired_angle){
        Serial.print(real_angle);
        Serial.print(" ");
        Serial.println(desired_angle);
        vs=0;
        vd=0;
        rotate();
        motors(vs, vd);
      }
      vs = stop_speed;
      vd = stop_speed;
      motors_stop('r');
      instruct.removeFirst();
      delay(1000);
    }
    Serial.println();
  }else{
    motors_stop('s');
    Serial.print("done");
    Serial.println();
  }
}

void motors_stop(char mode){
  if(mode == 'm'){
    motors(-255*sgn(vs_old),-255*sgn(vs_old));
    delay(move_speed/5);
    motors(stop_speed,stop_speed);
  }else if(mode == 'r'){
    motors(sgn(vs_old)*-255,sgn(vs_old)*-255);
    delay(rotate_speed/5);
    motors(sgn(vs_old)*stop_speed*-1,sgn(vs_old)*stop_speed*-1);
  }else{
    motors(0,0);
  }
}

void rotate(){
  get_angle(real_angle);
  if((int)real_angle>(int)desired_angle){
    vs -=rotate_speed;
    vd+=rotate_speed;
  }else if((int)real_angle<(int)desired_angle){
    vd-=rotate_speed;
    vs+=rotate_speed;
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

void readFile(fs::FS &fs, const char * path){
  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    while(1){
      ;
    }
  }
  
  if(file.available()){
    instruction aux;
    int a=0;
    bool neg=false;
    char x;
    x=file.read();
    while(x!='e'){
      if(x!=13){
        aux.mode = x;
        a=0;
        x=file.read();
        if(x=='-'){
          neg = true;
          x=file.read();
        }
        while(x!=13){
          a=a*10+(x-'0');
          x=file.read();
        }
        if(neg == true){
          a=-a;
          neg = false;
        }
        aux.value = a;
      }else{
        instruct.add(aux);
        aux.mode = 0;
        aux.value=0;
        file.read();
        x=file.read();
      }
    }
  }
  file.close();
  for(int i=0;i<instruct.getSize();i++){
    Serial.print(instruct[i].mode);
    Serial.print(instruct[i].value);
    Serial.println();
  }
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}
