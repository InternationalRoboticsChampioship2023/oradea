#include <Wire.h>
#include <Servo.h>
 
const int MPU_addr=0x68;
float angle,error;
float kd;
int viteza_st=180, viteza_dr=180;
bool end_line = false;
bool start = false;

Servo stanga;
Servo dreapta;
Servo picior;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  Serial.begin(9600);
  error = calc_error();
  stanga.attach(5);
  stanga.write(0);
  dreapta.attach(6);
  dreapta.write(0);
  picior.attach(3);
  picior.write(90);
}

float dir_read(){
  float GyZ, GyZError,z;
  float elapsedTime, currentTime, previousTime;
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);
  GyZ=(Wire.read()<<8|Wire.read())/131.0 -error; //-1*rezult from calc_error()
  z= z+GyZ*elapsedTime;
  return z;
}

void loop(){
  if(start == true){
    if(end_line == false){
      viteza_st = 180;
      viteza_dr = 180;
      angle = dir_read();
      if(angle>0){
        viteza_st -= kd*angle;
      }else if(angle<0){
        viteza_dr -= kd*angle;
      }
      stanga.write(viteza_st);
      dreapta.write(viteza_dr);
    }else{
      viteza_st=0;
      viteza_dr=0;
      picior.write(80);
    }
  }else{
    viteza_st=0;
    viteza_dr=0;
    picior.write(90);
  }

  if(digitalRead(A0) == HIGH){
    end_line == true;
    viteza_st=0;
    viteza_dr=0;
    picior.write(80);
  }

  if(digitalRead(A1) == HIGH){
    start = true;
  }
}

float calc_error(){
  float sum=0;
  int steps=400;
  for(int i =0;i<steps;i++){
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,2,true);
    sum+=(Wire.read()<<8|Wire.read())/131.0;
  }
  sum = sum/steps;
  Serial.println(sum);
  return sum;
}
