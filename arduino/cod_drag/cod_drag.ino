#include <QTRSensors.h>



const int maxspeed=255;


const int enB=3;  //stanga
const int m1pin1=4;
const int m1pin2=5;

const int m2pin1=7;
const int m2pin2=8;
const int enA = 9;  //dreapta

int M1_minumum_speed=80;
int M2_minumum_speed=80;


const int KP=2 ;
const int KD=5 ;

#define TIMEOUT 2500 ; // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN 2 ;


QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];


int lastError = 0;
int  last_proportional = 0;
int integral = 0;



void setup() {
  calibrare();
  qtr.setTypeAnalog();
 qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5,A6,A7}, SensorCount);
 qtr.setEmitterPin(2);
 pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(m1pin1, OUTPUT);
	pinMode(m1pin2, OUTPUT);
	pinMode(m2pin1, OUTPUT);
	pinMode(m2pin2, OUTPUT);
  
motors(0,0);

}

void loop() {
  
int position = qtr.readLineBlack(sensorValues); 
  int error = position - 2000;
  
int motorSpeed = KP * error + KD * (error - lastError);
lastError = error;
  
int leftMotorSpeed = M1_minumum_speed + motorSpeed;
int rightMotorSpeed = M2_minumum_speed - motorSpeed;
  
// set motor speeds using the two motor speed variables above
motors(leftMotorSpeed, rightMotorSpeed);

}






void motors(int motor1speed,int motor2speed){
if(motor1speed>maxspeed){
motor1speed=maxspeed;
}

if(motor2speed>maxspeed){
  motor2speed=maxspeed;
}
if (motor1speed < 0) motor1speed = 0; 
  if (motor2speed < 0) motor2speed = 0; 
 


  //merge in fata motorul stanga daca m1pin1 high iar m1pin2 low, altfel daca viteza este 0 se bloceaza
  analogWrite(enB, motor1speed);
 digitalWrite(m1pin1, HIGH);
	digitalWrite(m1pin2, LOW);

//merge in fata motorul dreapta daca m2pin1 high iar m2pin2 low, altfel daca viteza este 0 se bloceaza
 analogWrite(enA, motor2speed);
 digitalWrite(m2pin1, HIGH);
	digitalWrite(m2pin2, LOW);


}






void calibrare() {

  
  for (int i = 0; i < 400; i++)  // the calibration will take a few seconds
  {
    qtr.calibrate();
    delay(20);
  }
}
