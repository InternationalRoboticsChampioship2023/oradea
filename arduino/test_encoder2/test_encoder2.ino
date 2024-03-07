#include "arduino2.h" 
/*
 * The purpose of this code is to count the ouput pulses or 
 * the encoder outputs as you rotate the Motor shaft. You can run the 
 * same code on the Arduino Uno, Arduino Nano, Arduino Mega, etc.
 * https://www.codeproject.com/Articles/732646/Fast-digital-I-O-for-Arduino
 * dummy pins2_arduino.h to "eightanaloginputs" folder for pro mini
 */
#define Encoder_output_A 2 // pin2 of the Arduino
#define Encoder_output_B A0 // pin 3 of the Arduino
// these two pins has the hardware interrupts as well. 
 
int Count_pulses = 0;
void setup() {
Serial.begin(9600); // activates the serial communication
pinMode2(Encoder_output_A,INPUT); // sets the Encoder_output_A pin as the input
pinMode2(Encoder_output_B,INPUT); // sets the Encoder_output_B pin as the input
attachInterrupt(digitalPinToInterrupt(Encoder_output_A),DC_Motor_Encoder,RISING);
}
 
void loop() {
  Serial.println("Result: ");
  Serial.println(Count_pulses); 
}
 
void DC_Motor_Encoder(){
  int b = digitalRead2(Encoder_output_B);
  Count_pulses++;
}
