#include <Wire.h>
double error;
int adress;
void corrections_begin(int adrr){
  adress = adrr;
  Wire.begin();
  Wire.beginTransmission(adress);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
}

int get_angle(double elapsedTime){
  int angle;
  double angle_read;
  Wire.beginTransmission(adress);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(adress,6,true);
  angle_read=(Wire.read()<<8|Wire.read())/131.0;
  angle_read = angle_read -error; //-1*1.43
  angle= (int)(angle_read + angle_read * elapsedTime);
  return angle;
}

void calc_error(){
  double error = 0;
  int reading;
  for(int i = 0;i<2000;i++){
    Wire.beginTransmission(adress);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(adress,6,true);
    reading=(Wire.read()<<8|Wire.read())/131.0;
    error = error + reading;
  }
  error = error/2000;
  return error;
}
