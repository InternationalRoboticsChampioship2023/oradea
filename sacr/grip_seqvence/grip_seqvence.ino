#include <Servo.h>

Servo mid;  // create servo object to control a servo
Servo base;
int g1 = A0;
int g2 = A1;
int oldstate;

void setup() {
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);
  mid.attach(5);  // attaches the servo on pin 9 to the servo object
  base.attach(6);
  setmid(180);
  setbase(110);
  delay(1000);
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

void loop() {
  delay(1);
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
