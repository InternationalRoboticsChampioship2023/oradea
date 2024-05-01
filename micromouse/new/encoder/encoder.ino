/*
 * The purpose of this code is to count the ouput pulses or 
 * the encoder outputs as you rotate the Motor shaft. You can run the 
 * same code on the Arduino Uno, Arduino Nano, Arduino Mega, etc.
 * https://www.codeproject.com/Articles/732646/Fast-digital-I-O-for-Arduino
 * dummy pins2_arduino.h to "eightanaloginputs" folder for pro mini
 */
#define EncoderS 12 // pin2 of the Arduino
#define EncoderD 13 // pin 3 of the Arduino
// these two pins has the hardware interrupts as well. 

int Count_pulsesS = 0;
int Count_pulsesD = 0;
void setup() {
Serial.begin(9600); // activates the serial communication
pinMode(EncoderS,INPUT); // sets the Encoder_output_A pin as the input
pinMode(EncoderD,INPUT); // sets the Encoder_output_B pin as the input
attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
attachInterrupt(digitalPinToInterrupt(EncoderD),DC_MotorD,RISING);
}
 
void loop() {
  Serial.print(Count_pulsesS);
  Serial.print('\t');
  Serial.print(Count_pulsesD);
  Serial.print('\t');
  Serial.print(millis());
  Serial.println();
}
 
void DC_MotorS(){
  int ES = 16;
  if(digitalRead(ES)==HIGH){
    Count_pulsesS--; 
  }else{
    Count_pulsesS++; 
  }
  
}
void DC_MotorD(){
  int ED = 17;
  if(digitalRead(ED)==HIGH){
    Count_pulsesD++; 
  }else{
    Count_pulsesD--;
  }
}
