#include <Wire.h>
double error=0 , angle_double =0 ;
int adress;
int angle =0 ;
void corrections_begin(int adrr){
  adress = adrr;
  Wire.begin();
  Wire.beginTransmission(adress);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  calc_error();
}

int get_angle(double elapsedTime){
  double angle_read;
  Wire.beginTransmission(adress);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(adress,4,true);
  angle_read=(Wire.read()<<8|Wire.read())/131.0;
  angle_read = angle_read -error; //-1*1.43
  angle_double= angle_double + angle_read * elapsedTime;
  angle = (int)angle_double;
  return angle;
}

void calc_error(){
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
