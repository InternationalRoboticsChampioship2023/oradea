#include <Servo.h>
int in1=2;
int in2=3;
int servo1pin=5;
int servo2pin=6;
int servo3pin=9;
Servo bm1;
Servo bm2;
Servo base;
int baseval=0;
int mijloc=0;
int difmijloc=180;
const int base_rest = 90;
const int mijloc_rest = 90;
void setup() {
  Serial.begin(9600);
  base.attach(servo3pin);
  bm1.attach(servo1pin);
  bm2.attach(servo2pin);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  open_gripper();
  gotorestpos();
}

void open_gripper(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(600);//get real time for travel from extremety to extremety
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}


void close_gipper(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(600);//get real time for travel from extremety to extremety
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void move_base(int b){
  while(baseval!=b){
    if(baseval>b) {baseval--;}
    else if(baseval<b){baseval++;}
    base.write(baseval);
    delay(20);
  }
}

void move_mijloc(int m){
  while(mijloc!=m){
    if(mijloc>m) {mijloc--;}
    else if(mijloc<m){mijloc++;}
    bm1.write(mijloc);
    bm2.write(180-mijloc);
    delay(20);
  }
}

void gotorestpos(){
  move_base(base_rest);
  move_mijloc(mijloc_rest);
  open_gripper();
}

void catchobj(){
  //daca intra in functie inseamna ca a detectat ceva ce poate apuca
  move_base(0);
  move_mijloc(0);
  //intinde bratul paralel cu pamantul
  close_gipper();
  move_base(base_rest);
  move_mijloc(180);
  //duce bratul pt descarcare
  open_gripper();
}

void loop() {
 if(Serial.available()>0){
  String data = Serial.readStringUntil('\n');
  if(data!=NULL){
    //a gasit ceva deci incearca sa il apuci
    catchobj();
    gotorestpos();
  }
 }
}
