#include <Wire.h>
double error=1.512 , angle_double =0, angle_read;
int adress;
void corrections_begin(int adrr){
  adress = adrr;
  Wire.begin();
  Wire.beginTransmission(adress);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  //calc_error();
  //Serial.println(error);
}

double get_angle(double elapsedTime){
  Wire.beginTransmission(adress);
  Wire.write(0x47);
  if(Wire.endTransmission(false)!=4){
    Wire.requestFrom(adress,2,true);
    angle_read=(Wire.read()<<8|Wire.read())/131.0;
    angle_read = angle_read -error; //-1*1.43
    angle_double= angle_double + angle_read * elapsedTime;
    Serial.println("ok");
    return angle_double;
  }else{
    Serial.println("error 4");
    return 0;
  }
  
}

void calc_error(){
  int reading;
  for(int i = 0;i<4000;i++){
    Wire.beginTransmission(adress);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(adress,6,true);
    reading=(Wire.read()<<8|Wire.read())/131.0;
    error = error + reading;
  }
  error = error/4000;
  return error;
}
