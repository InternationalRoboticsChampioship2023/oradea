#include<Wire.h>
 
const int MPU_addr=0x68;
float error, z;
int angle;
float elapsedTime, currentTime, previousTime;

#define EncoderS 2 // pin2 of the Arduino
#define EncoderD 3 // pin 3 of the Arduino
#define MSV 5
#define MS1 A2
#define MS2 4
#define MDV 6
#define MD1 8
#define MD2 7
int m_speed = 100;
int Count_pulsesS = 0, pulsesS;
int Count_pulsesD = 0, pulsesD;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
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
}
void loop(){
  angle = get_angle();
  if(angle>0){
    motors(0,m_speed);
  }else if(angle<0){
    motors(m_speed, 0);
  }else{
    motors(0,0);
  }
  Serial.print(angle);
  Serial.print("     ");
  Serial.print(millis ());
  Serial.println();
}

void motors(int ms, int md){//ms, md reprezents motors speed
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
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);
  GyZ=(Wire.read()<<8|Wire.read())/131.0 -error; //-1*rezult from calc_error()
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
    sum+=(Wire.read()<<8|Wire.read())/131.0;
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
