#include<Wire.h>
 
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
int m_speed = 100;


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
  //calc_error();
}
void loop(){
  Serial.println();
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 2, true);
  GyZ=(Wire.read()<<8|Wire.read())/16.4;
  GyZ = GyZ -1.1; //-1*rezult from calc_error()
  z= z+GyZ*elapsedTime;
  angle = (int)z;
  //Serial.print(angle);
  
  
  if(angle>desired_angle){
    analogWrite(MSV, m_speed);
    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, LOW);
    analogWrite(MDV, m_speed);
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
  }else if(angle<desired_angle){
    analogWrite(MSV, m_speed);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
    analogWrite(MDV, m_speed);
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
  }else{
    analogWrite(MSV, 0);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
    analogWrite(MDV, 0);
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
  }

  if(currentTime>=5000){
    desired_angle=360;
  }
}

void calc_error(){
  double sum = 0;
  delay(2000);
  for(int i = 0;i<2000;i++){
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,6,true);
    GyZError=(Wire.read()<<8|Wire.read())/131.0;
    sum = sum + GyZError;
  }
  sum = sum/2000;
  Serial.println(sum);
  while(1){
    delay(10);
  }
}
