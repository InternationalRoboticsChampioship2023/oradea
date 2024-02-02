#include<Wire.h>
 
const int MPU_addr=0x68;
double GyZ, GyZError,z;
int angle;
float elapsedTime, currentTime, previousTime;
void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0x00);
Wire.endTransmission(true);
Serial.begin(9600);
//calc_error(); //uncoment to calculate Zaxis error
}
void loop(){
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
  Serial.print(angle);
  Serial.println();
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
