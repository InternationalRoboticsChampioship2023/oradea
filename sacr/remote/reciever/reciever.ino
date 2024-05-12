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

Servo mid;  // create servo object to control a servo
Servo base;
int g1 = A0;
int g2 = A1;
bool grp = 1;
void setup(){
  while (!Serial);
    Serial.begin(9600);
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);
  mid.attach(5);  // attaches the servo on pin 9 to the servo object
  base.attach(6);
  setmid(180);
  setbase(110);
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
      seq_grip();
    }
  }
  if (radio.available())
  {
    timeout = 0;
    char msg[11] = {0};
    radio.read(&msg, sizeof(msg));
    Serial.println(msg);
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
    if(gripSecvence == 0){
      grp = 1;
    }
    if(gripSecvence == 1 && grp != 0){
      dirServo.write(90);
      motor.setSpeed(0);
      seq_grip();
      grp  = 0;
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


void seq_grip(){
  grip(0);//open
  delay(150);
  grip(-1);//limbo
  setbase(110);
  setmid(180);
  delay(1000);
  setbase(70);
  grip(1);
  delay(1000);
  setbase(110);
  setmid(0);
  grip(0);
  delay(150);
  grip(-1);
  delay(1000);
  setmid(180);
}

void grip(int state){
  if(state == 1){
    digitalWrite(g1, HIGH);
    digitalWrite(g2, LOW);
  }else if(state == 0){
    digitalWrite(g1, LOW);
    digitalWrite(g2, HIGH);
  }else if(state == -1){
    digitalWrite(g1, LOW);
    digitalWrite(g2, LOW);
  }
}


void setmid(int agl){
  int angle = mid.read();
  while(angle != agl){
    if(angle > agl){
      angle--;
    }
    if(angle < agl){
      angle++;
    }
    mid.write(angle);
    delay(10);
  }
}

void setbase(int agl){
  int angle = base.read();
  while(angle != agl){
    if(angle > agl){
      angle--;
    }
    if(angle < agl){
      angle++;
    }
    base.write(angle);
    delay(10);
  }
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
