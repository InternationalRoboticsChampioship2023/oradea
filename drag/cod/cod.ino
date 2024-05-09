#include <Wire.h>
#include <Servo.h>
 
const int MPU_addr=0x68;
float angle,error;
float kp=1;
int viteza_st=180, viteza_dr=180;
bool end_line = false;
bool start = false;
float z=0;
//#define startstopbutton A1;
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
  error = 0.0098;//calc_error();
  stanga.attach(5);
  stanga.writeMicroseconds(1000);
  dreapta.attach(6);
  dreapta.writeMicroseconds(1000);
  picior.attach(3);
  picior.write(90); // original 90
  delay(7000);
  pinMode(A1,INPUT);
  start = true;
}

float dir_read(){
  float GyZ;
  float elapsedTime, currentTime, previousTime;
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);
  GyZ=(Wire.read()<<8|Wire.read())/16384.0 -error; //-1*rezult from calc_error()
  z= z+GyZ*elapsedTime;
  return z;
}

void loop(){
  if(digitalRead(2) == LOW){
    end_line == true;
    picior.write(140);
    viteza_st=1000;
    viteza_dr=1000;
    stanga.writeMicroseconds(viteza_st);
    dreapta.writeMicroseconds(viteza_dr);
    while(1){
      ;
    }
  }

  if(digitalRead(A1) == HIGH){
    start = true;
   // Serial.print("Da");
  }
  if(start == true){
    //angle = dir_read();
    if(end_line == false){
      viteza_st = 1100;//modify
      viteza_dr = 1100;
      angle = dir_read();
      if(angle>0){
        viteza_st -= kp*angle;
      }else if(angle<0){
        viteza_dr += kp*angle;
      }
     //Serial.println(angle);
      //Serial.print(",");
      //Serial.print(viteza_st);
      //Serial.print(",");
      //Serial.print(viteza_dr);
      //Serial.print(",");
      //Serial.print(digitalRead(2));
      //Serial.println("");

      if(viteza_st>1100){
        viteza_st=1100;
      }
      if(viteza_dr>1100){
        viteza_dr=1100;
      }
      stanga.writeMicroseconds(viteza_st);
      dreapta.writeMicroseconds(viteza_dr);
    }else{
      //end_line=true;
      viteza_st=1000;
      viteza_dr=1000;
      stanga.writeMicroseconds(viteza_st);
      dreapta.writeMicroseconds(viteza_dr);
      picior.write(140);
    }
  }else{
    //start=false;
    viteza_st=1000;
    viteza_dr=1000;
    stanga.writeMicroseconds(viteza_st);
    dreapta.writeMicroseconds(viteza_dr);
    picior.write(90);
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
    sum+=(Wire.read()<<8|Wire.read())/16384.0;
  }
  sum = sum/steps;
  Serial.println(sum);
  return sum;
}
