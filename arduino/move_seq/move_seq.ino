/*
IMPORTANT NOTES

at end of the line there are 2 caracters CR, LF (13, 10)

end document with blank line (last line to have te 2 caracters mentioned above)
*/

#include<Wire.h>
#include <SPI.h>
#include <SD.h>

File myFile;
char x, prevx;
bool mode_sel=false, isExecuting=false, progend=false;
int mode, value=0;
 
const int MPU_addr=0x68;
double GyZ, GyZError,z;
int angle,desired_angle=0;
float elapsedTime, currentTime, previousTime;

#define MSV 5
#define MS1 A2
#define MS2 4
#define MDV 6
#define MD1 8
#define MD2 7
int m_speed = 70;
int rotation_speed=70;
int ms_speed=0, md_speed=0;

#define EnSA 2 // pin2 of the Arduino
#define EnSB A0
#define EnDA 3 // pin2 of the Arduino
#define EnDB A1
int pulses=0,a;
double wheel_circ = 9.11, rev;
int pulsesRev;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x18);                   // Set the register bits as 00011000 (2000deg/s full scale)
  Wire.endTransmission(true);
  
  pinMode(MSV, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MDV, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  Serial.begin(9600);
  pinMode(EnSA,INPUT); // sets the Encoder_output_A pin as the input
  pinMode(EnSB,INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(EnSA),MSEn,RISING);
  SD.begin(10);
  myFile = SD.open("test.txt", FILE_READ);
  //calc_error();
  delay(1000);
  
}

void MSEn(){
  a = digitalRead(EnSB);
  if(a > 0){
    pulses++;
  }
  else{
    pulses--;
  }
}

void motors(int ms, int md){ // dir=1=> high
  if(ms<0){
    digitalWrite(MS1, 1);
    digitalWrite(MS2, 0);
  }else{
    digitalWrite(MS1, 0);
    digitalWrite(MS2, 1);
  }
  if(md<0){
    digitalWrite(MD1, 1);
    digitalWrite(MD2, 0);
  }else{
    digitalWrite(MD1, 0);
    digitalWrite(MD2, 1);
  }
  analogWrite(MSV, abs(ms));
  analogWrite(MDV, abs(md));
  //return 1 for completion
  //retuns 0 for in progress
}
int move_dist(double dist){//in cm
  rev = dist/wheel_circ;
  pulsesRev = int(rev*120);//102 pulses/rev for encoder
  if(pulsesRev > pulses){
    ms_speed=-1*m_speed;
    md_speed=-1*m_speed;
  }else if(pulsesRev < pulses){
    ms_speed=m_speed;
    md_speed=m_speed;
  }else{
    ms_speed=0;
    md_speed=0;
    delay(200);
    return 1;
  }
  corect_dir();
  return 0;
}

int rotate(int agl){
  desired_angle = agl;
  if(angle == desired_angle){
    delay(200);
    return 1;
  }
  corect_dir();
  return 0;
}

void corect_dir(){
  previousTime = currentTime;      
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 2, true);
  GyZ=(Wire.read()<<8|Wire.read())/16.4;
  GyZ = GyZ -1.6; //-1*rezult from calc_error()
  z= z+GyZ*elapsedTime;
  angle = (int)z;
  if(angle>desired_angle){
    ms_speed-=50;
    md_speed+=50;
  }else if(angle<desired_angle){
    ms_speed+=50;
    md_speed-=50;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myFile.available() && isExecuting == false){
    x=myFile.read();
    if(x=='_'){
      Serial.print(prevx);
      Serial.print("mode");
      mode_sel=true;
      mode=prevx-'0';
      value=0;
    }else if(int(x)==13){
      mode_sel=false;
      isExecuting=true;
      myFile.read();
      Serial.print(value);
        Serial.println("value");
    }else if (x=='a'){
      progend = true;
    }else{
      if(mode_sel == true){
        value =value*10+((int)x-48);
      }
    }
    prevx=x;
  }

  if(mode == 1){
    if(move_dist(value)==1){
      isExecuting = false;
      pulses=0;
    }
  }
  if(mode == 2){
    if(rotate(value)==1){
      isExecuting = false;
      pulses=0;
    }
  }

  if(progend==true){
    motors(0,0);
    while(1){
      ;
    }
  }
  Serial.print(mode);
  Serial.print(value);
  Serial.print(isExecuting);
  Serial.println();
  motors(ms_speed, md_speed);
}