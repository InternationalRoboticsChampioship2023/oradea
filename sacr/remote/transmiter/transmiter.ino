//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int accPin = A0;
int dirPin = A1;
int acc_int;
int dir_int;
int reversePin = A2;
int gripSecvencePin = A3; 
char acc_char[3];
char dir_char[3];
char msg[11]; 

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "02204";

void setup()
{
  Serial.begin(9600);
  
  pinMode(accPin, INPUT);
  pinMode(dirPin, INPUT);
  pinMode(reversePin, INPUT);
  pinMode(gripSecvencePin, INPUT);
  
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  
  //Set module as transmitter
  radio.stopListening();
  
}
void loop()
{
  msg[3]='.';
  acc_int = map(analogRead(accPin), 0, 1023, 0, 255);
  for(int i=2;i>=0;i--){
    msg[i] = (acc_int%10)+'0';
    acc_int/=10;
  }
  dir_int = map(analogRead(dirPin), 0, 1023, 0, 180);
  for(int i=2;i>=0;i--){
    msg[i+4] = (dir_int%10)+'0';
    dir_int/=10;
  }
  msg[7] = '.';
  msg[8] = digitalRead(reversePin) + '0';
  msg[9] = '.';
  msg[10] = digitalRead(gripSecvencePin) + '0';
  //Serial.println(msg);
  //Send message to receiver
  Serial.println(msg);
  radio.write(&msg, sizeof(msg));
  
}
