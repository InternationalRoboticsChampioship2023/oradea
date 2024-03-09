#include<Wire.h>
 
const int MPU_addr=0x68;
float GyZ, GyZError,z, error;
int angle;
float elapsedTime, currentTime, previousTime;
void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0x00);
Wire.endTransmission(true);
Serial.begin(9600);
error = calc_error();
}
void loop(){
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);
  GyZ=(Wire.read()<<8|Wire.read())/131.0 -error; //-1*rezult from calc_error()
  z= z+GyZ*elapsedTime;
  angle = (int)z;
  Serial.print(angle);
  Serial.print("     ");
  Serial.print(GyZ);
  Serial.print("     ");
  Serial.print(millis ());
  Serial.println();
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
