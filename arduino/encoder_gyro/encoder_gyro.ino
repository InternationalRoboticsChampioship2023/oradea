#include<Wire.h>

const int MPU_addr=0x68;
double GyZ, GyZError,z;
int angle;
float motor_angle;
float transform = 0.33333333; //counter is 54 at 180 degrees rotation
float elapsedTime, currentTime, previousTime;
 
#define output2A 2//interupt pin
#define output2B A0
#define M2speed 6
#define M2a 8
#define M2b 9

int counter = 0;  
int motor_speed = 90; 

void setup() { 
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  pinMode (output2A,INPUT);
  pinMode (output2B,INPUT);
  pinMode (M2speed,OUTPUT);
  pinMode (M2a,OUTPUT);
  pinMode (M2b,OUTPUT);
   
  Serial.begin (9600);
  // Reads the initial state of the outputA
  attachInterrupt(digitalPinToInterrupt(output2A),Encoder2,RISING); 
} 
void loop() { 
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true);
  GyZ=(Wire.read()<<8|Wire.read())/131.0;
  GyZ = GyZ -1.43; //-1*rezult from calc_error()
  z= z+GyZ*elapsedTime;
  angle = (int)z;
  motor_angle= (int)(counter*0.3);
  Serial.print(angle);
  Serial.print('\t');
  Serial.print(motor_angle);
  Serial.println();

  if(motor_angle<angle){
    digitalWrite(M2a, HIGH);
    digitalWrite(M2b, LOW);
    analogWrite (M2speed, motor_speed);
  }else if(motor_angle>angle){
    digitalWrite(M2a, LOW);
    digitalWrite(M2b, HIGH);
    analogWrite (M2speed, motor_speed);
  }else{
    digitalWrite(M2a, LOW);
    digitalWrite(M2b, LOW);
    analogWrite (M2speed, motor_speed);     
  }
}


void Encoder2(){
  int b = digitalRead(output2B);
  if(b > 0){
    counter++;
  }
  else{
    counter--;
  }
}
