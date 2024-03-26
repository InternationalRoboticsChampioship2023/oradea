#include<Wire.h>
#include <SPI.h>
#include <SD.h>
#include <List.hpp>
#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))
 
const int MPU_addr=0x68;
float error, z;
int desired_angle;
bool rotate_set=false, encoder_set = false;
float elapsedTime, currentTime, previousTime;
float sensitivity = 65.5; //modify if changing sensitivity

#define EncoderS 2 // pin2 of the Arduino
#define EncoderD 3 // pin 3 of the Arduino
#define MSV 5
#define MS1 A2
#define MS2 4
#define MDV 6
#define MD1 8
#define MD2 7
int m_speed = 100, corection_speed = 30, rotate_speed=100, stop_speed = -45;
int Count_pulsesS = 0, pulsesS;
int Count_pulsesD = 0, pulsesD;

int ms_speed, md_speed, ms_old=0, md_old=0;
float diam = 91.1;

File myFile;
char x;
struct instruction{
  char mode;
  int value;//in mm or degrees
};
List<instruction> instruct;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x18);                  //Set the register bits as 00011000 (+/- 16g full scale range)
  Wire.endTransmission(true);        //just to be sure it doesnt affect the other registers

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x08);                   // Set the register bits as 00011000 (2000deg/s full scale)
  Wire.endTransmission(true);         ///check sensitivity if chang here
  
  error = calc_error();
  pinMode(EncoderS,INPUT); // sets the Encoder_output_A pin as the input
  pinMode(EncoderD,INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderD),DC_MotorD,RISING);
  pinMode(MSV, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MDV, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  SD.begin(10);
  myFile = SD.open("steps.txt", FILE_READ);
  if(myFile.available()){
    instruction aux;
    int a=0;
    bool neg=false;
    x=myFile.read();
    while(x!='e'){
      if(x!=13){
        aux.mode = x;
        a=0;
        x=myFile.read();
        if(x=='-'){
          neg = true;
          x=myFile.read();
        }
        while(x!=13){
          a=a*10+(x-'0');
          x=myFile.read();
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
        myFile.read();
        x=myFile.read();
      }
    }
  }
  myFile.close();

  for(int i=0;i<instruct.getSize();i++){
    Serial.print(instruct[i].mode);
    Serial.print(instruct[i].value);
    Serial.println();
  }
}
void loop(){
  ms_speed = 0;
  md_speed = 0;
  pulsesS = Count_pulsesS;
  pulsesD = Count_pulsesD;
  if(instruct.getSize()!=0){
    Serial.print(instruct[0].mode);
    if(instruct[0].mode == 'm'){
      correction();
      if(encoder_set == false){
        Count_pulsesS=0;
        Count_pulsesD=0;
        pulsesS = 0;
        pulsesD = 0;
        encoder_set = true;
      }
      Serial.print(instruct[0].value);
      if(move_dist(instruct[0].value)==1){
        encoder_set = false;
        stop_m(instruct[0].mode);
        instruct.removeFirst();
        delay(1000);
      }


      
    }else if(instruct[0].mode=='r'){
      if(rotate_set == false){
        desired_angle+=instruct[0].value; 
        rotate_set = true;
      }
      Serial.print(desired_angle);
      if(rotate()==1){
        rotate_set=false;
        stop_m(instruct[0].mode);
        instruct.removeFirst(); 
        delay(1000);
      }
    }
  motors(ms_speed, md_speed);
  ms_old = ms_speed;
  md_old = md_speed;
  Serial.println();
  }else{
    motors(0,0);
    Serial.print("done");
    Serial.println();
  }
  
}


void stop_m(char mode){
  if(mode == 'm'){
    motors(-255,-255);
    delay(m_speed/10);
    motors(stop_speed,stop_speed);
  }else if(mode == 'r'){
    motors(sgn(ms_old)*-255,sgn(md_old)*-255);
    delay(rotate_speed/10);
    motors(sgn(ms_old)*stop_speed*-1,sgn(md_old)*stop_speed*-1);
  }else{
    motors(0,0);
  }
}

int rotate(){
  int agl= get_angle();
  if(agl>desired_angle){
   ms_speed-=rotate_speed;
   md_speed+=rotate_speed;
   return 0;
  }else if(agl<desired_angle){
    ms_speed+=rotate_speed;
    md_speed-=rotate_speed;
    return 0;
  }
  return 1;
}


int move_dist(int val){
  int pls = (val*120)/diam;
  //Serial.print(val);
  //Serial.print("     ");
  if((pulsesS + pulsesD)/2 <pls){
     ms_speed+=m_speed;
     md_speed+=m_speed;
     return 0;
  }
  return 1;
}

void correction(){
  int agl= get_angle();
  if(agl>desired_angle){
   md_speed+=corection_speed;
   ms_speed-=corection_speed;
  }else if(agl<desired_angle){
    md_speed-=corection_speed;
    ms_speed+=corection_speed;
  }
}

void motors(int ms, int md){//ms, md reprezents motors speed
  constrain(ms, -255, 255);
  constrain(md, -255, 255);
  analogWrite(MSV, abs(ms));
  analogWrite(MDV, abs(md));
  if(ms>0){
    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, LOW);
  }else{
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
  }
  if(md>0){
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
  }else{
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
  }
}

int get_angle(){
  float GyZ;  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);
  GyZ=(Wire.read()<<8|Wire.read())/sensitivity -error; //-1*rezult from calc_error()
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  z= z+GyZ*elapsedTime;
  return -((int)z);
}

float calc_error(){
  float sum=0;
  int steps=400;
  for(int i =0;i<steps;i++){
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,2,true);
    sum+=(Wire.read()<<8|Wire.read())/sensitivity;
  }
  sum = sum/steps;
  Serial.println(sum);
  return sum;
}

void DC_MotorS(){
  int ES = A0;
  if(digitalRead(ES)==HIGH){
    Count_pulsesS--; 
  }else{
    Count_pulsesS++; 
  }
  
}
void DC_MotorD(){
  int ED = A1;
  if(digitalRead(ED)==HIGH){
    Count_pulsesD++; 
  }else{
    Count_pulsesD--;
  }
}
