#include<Wire.h>
 
const int MPU_addr=0x68;
double AccX, AccY, AccZ, accAngleY, velocity=0,distance;
int angle,desired_angle=0,accY;
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
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  // Calculating Roll and Pitch from the accelerometer data
  //accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) - 1.58; // AccErrorY ~(-1.58)
  accY = int(accAngleY*9.8);
  //Serial.print(accAngleY);
  //Serial.print(" ");
  Serial.print(accY);
  Serial.println();
}
