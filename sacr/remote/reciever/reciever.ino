//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
 #include "CytronMotorDriver.h"

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "02204";

Servo dirServo;
CytronMD motor(PWM_DIR, 3, 2);  // PWM = Pin 3, DIR = Pin 4.

int dir, acc,timeout = 0;
bool reverse = false;
bool gripSecvence = false;
void setup()
{
  while (!Serial);
    Serial.begin(9600);
    
  dirServo.attach(10);
  dirServo.write(90);
  motor.setSpeed(0);
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if(Serial.available()>0){
    String data = Serial.readStringUntil('\n');
    if(data!=NULL){
      grip();
    }
  }
  if (radio.available())
  {
    timeout = 0;
    char msg[11] = {0};
    radio.read(&msg, sizeof(msg));
    if(sizeof(msg)!=11){
      exception(2);
    }
    
    if(msg[3]!='.' || (msg[7]!='.' ||msg[9]!='.')){
      exception(1);//bad msg
    }
    acc = 0;
    dir=0;
    reverse = msg[8]-'0';
    gripSecvence = msg[10]-'0';
    if(gripSecvence == 1){
      dirServo.write(90);
      motor.setSpeed(0);
      grip();
    }else{
      for(int i =0;i<=2;i++){
        acc= acc*10+ (msg[i]-'0');
      }
      for(int i =4;i<=6;i++){
        dir= dir*10+ (msg[i]-'0');
      }
      if((acc<0 || acc > 255)||(dir<0||dir>180)){
        exception(3);
      }
      dirServo.write(dir);
      if(reverse == 0){
        motor.setSpeed(acc);
      }else{
        motor.setSpeed(-acc);
      }
    }
  }else{
    timeout++;
    if(timeout>1500){
      exception(0);
      dirServo.write(90);
      motor.setSpeed(0);
    }
  }
}


void grip(){
  //grip seqvence
}

void exception(int ex){
  if(ex == 1){
    Serial.println("bad msg");
  }else if(ex == 0){
    Serial.println("no radio available");
  }else if(ex==2){
    Serial.println("incorect msg size");
  }else if(ex==3){
    Serial.println("out of bounds values");
  }
}
