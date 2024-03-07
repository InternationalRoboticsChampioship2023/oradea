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
bool mode_sel=false;
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
int m_speed = 70, rotation_speed=50, corection_speed=50;
int ms_speed=0, md_speed=0;

#define EnSA 2 // pin2 of the Arduino
#define EnSB A0
//#define EnDA 3 //mot used
//#define EnDB A1 // 
int pulses=0,a;
double wheel_circ = 9.11;

void setup() {
  Serial.begin(9600);
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

  pinMode(EnSA,INPUT); // sets the Encoder_output_A pin as the input
  pinMode(EnSB,INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(EnSA),MSEn,RISING);

  SD.begin(10);
  myFile = SD.open("instruct.txt", FILE_READ);
  
  delay(1000);


  if(myFile.available()){
    while(x!='a'){
      x=myFile.read();
      if(x=='_'){
        mode_sel=true;
        mode=prevx-'0';
        value=0;
      }else if(int(x)==13){
        mode_sel=false;
        if(mode == 1){
          move_dist(value);  
        }else if(mode == 2){
          rotate_agl(value);
        }
        myFile.read();
      }else if (x=='a'){
        break;
      }else{
        if(mode_sel == true){
          value =value*10+((int)x-48);
        }
      }
      prevx=x;
    }
    motors(0, 0);
    while(1){
      ;
    }
  }
}

void move_dist(int x){//x in mm
  pulses = 0;
  double dist = x/10;
  int rev = int((dist/wheel_circ)*120);//120 pulses/wheel rev
  while(rev != pulses){
    if(rev > pulses){
      ms_speed=-1*m_speed;
      md_speed=-1*m_speed;
    }else if(rev < pulses){
      ms_speed=m_speed;
      md_speed=m_speed;
    }
    Serial.print(pulses);
    Serial.print(" ");
    Serial.print(rev);
    Serial.println();
    corect_dir();
    motors(ms_speed, md_speed);
  }
  Serial.println("moved distance");
  motors(0, 0);
  delay(200);
}

void rotate_agl(int x){//x in degres
  desired_angle = x;
  angle = get_angle();
  while(angle!=desired_angle){
    if(angle>desired_angle){
      ms_speed-=rotation_speed;
      md_speed+=rotation_speed;
    }else if(angle<desired_angle){
      ms_speed+=rotation_speed;
      md_speed-=rotation_speed;
    }
    motors(ms_speed, md_speed);
    angle = get_angle();
    Serial.println(angle);
  }
  Serial.println("rotated angle");
  motors(0, 0);
  delay(200);
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
  constrain(ms, -255, 255);
  constrain(md, -255, 255);
  analogWrite(MSV, abs(ms));
  analogWrite(MDV, abs(md));
}

void corect_dir(){
  angle = get_angle();
  if(angle>desired_angle){
    ms_speed-=corection_speed;
    md_speed+=corection_speed;
  }else if(angle<desired_angle){
    ms_speed+=corection_speed;
    md_speed-=corection_speed;
  }
}

int get_angle(){
  detachInterrupt(digitalPinToInterrupt(EnSA));
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
  attachInterrupt(digitalPinToInterrupt(EnSA),MSEn,RISING);
  return (int)z;
}


void loop() {
  // put your main code here, to run repeatedly:

}
