#include "arduino2.h" 
#define EncoderS 2 // pin2 of the Arduino
#define pi 3.14159265;
int Count_pulsesS = 0,pulsesRev=120, desired_pulses;
float dist = 2.0, wheel_diam=9.1106;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // activates the serial communication
  pinMode2(EncoderS,INPUT); // sets the Encoder_output_A pin as the input
  //pinMode2(EncoderD,INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
  //attachInterrupt(digitalPinToInterrupt(EncoderD),DC_MotorD,RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  desired_pulses = (dist/wheel_diam)*pulsesRev;
  if(Count_pulsesS<desired_pulses){
    Serial.print(Count_pulsesS);
    Serial.print('\t');
    Serial.print(millis());
    Serial.println();
  }else{
    Serial.print("ok");
    Serial.print('\t');
    Serial.print(millis());
    Serial.println();
  }
  
}

void DC_MotorS(){
  Count_pulsesS++; 
}
