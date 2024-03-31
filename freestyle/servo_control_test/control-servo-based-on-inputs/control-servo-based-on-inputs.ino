#include <Servo.h>

Servo gripper;  // create servo object to control a servo
Servo fb; // forward backwards servo
Servo sj; //up, down servo
Servo dir; //car steering
int gripper_pos = 0;    // variable to store the servo position
int fb_pos = 180;
int sj_pos = 180;
byte acceleration=0;
byte steering=90;
void setup() {
  gripper.attach(3);  // attaches the servo on pin 9 to the servo object
  fb.attach(5);
  sj.attach(6);
  //dir.attach();
  Serial.begin(9600);
  

}
void cadran1(){
// dai in spate dreapta
//dupa mergi otara in fata pana iti ajunge in c5
//verifici daca a ajuns in c5
/*
dir.write(0);
analogWrite(acc_pin ,100);
digitalWrite(dir_pin, 1);//front
*/
}
void cadran2(){
  //mergi putin in fata pana ajungi in c5
  //verifici daca a ajuns in c5
  /*
dir.write(90);
analogWrite(acc_pin ,100);
digitalWrite(dir_pin, 1); //fornt
*/
}
void cadran3(){
  //dai putin in spate stanga
  //verifici daca a ajuns in c5
  /*
dir.write(180);
analogWrite(acc_pin ,100);
digitalWrite(dir_pin, 1);//front
*/
}
void cadran4(){
  //same like cadran1 doar ca mersul este de o distanta mai mica
   //verifici daca a ajuns in c5
     /*
dir.write(180);
analogWrite(acc_pin ,100);
digitalWrite(dir_pin, 0);//back
*/
}
void cadran5(){
  gripper.write(170);
  fb.write(fb_pos);
  sj.write(sj_pos);
  delay(1000);

  while(fb_pos > 80){
    fb.write(fb_pos);
    fb_pos--;
    delay(15);
  }
  delay(1000);

  gripper.write(50);
  delay(1000);

  while(fb_pos<150 || sj_pos>50){
    fb.write(fb_pos);
    sj.write(sj_pos);
    if(fb_pos!=150)fb_pos++;
    if(sj_pos!=50)sj_pos--;
    delay(15);
  }
  delay(1000);

  
  while(fb_pos<100 || sj_pos>160){
    fb.write(fb_pos);
    sj.write(sj_pos);
    if(fb_pos!=100)fb_pos--;
    if(sj_pos!=160)sj_pos++;
    delay(15);
  }
  delay(1000);

  gripper.write(170);
  delay(1000);

  while(fb_pos<100 || sj_pos<160){
    fb.write(fb_pos);
    sj.write(sj_pos);
    if(fb_pos!=100)fb_pos--;
    if(sj_pos!=160)sj_pos++;
    delay(15);
  }
  delay(1000);


  while(fb_pos<180 || sj_pos<180){
    fb.write(fb_pos);
    sj.write(sj_pos);
    if(fb_pos!=180)fb_pos++;
    if(sj_pos!=180)sj_pos++;
    delay(15);
  }
}
void cadran6(){
  //same like cadran3 doar ca dist parcursa e mai mica
   //verifici daca a ajuns in c5
     /*
dir.write(0);
analogWrite(acc_pin ,100);
digitalWrite(dir_pin, 0);//back
*/
}



void loop() {
   if (Serial.available() > 0) {
    String cadran = Serial.readStringUntil('\n');
    //Serial.print("cadran: ");
    //Serial.println(cadran);
    delay(1000);
   if(cadran=="c1"){
    cadran1();
    
   }
    if(cadran=="c2"){
    cadran2();
  
   }
    if(cadran=="c3"){
    cadran3();
   
   }
    if(cadran=="c4"){
    cadran4();
    
   }
    if(cadran=="c5"){
    cadran5();
     
   }
    if(cadran=="c6"){
    cadran6();
     
   }
   
    
  }

}
