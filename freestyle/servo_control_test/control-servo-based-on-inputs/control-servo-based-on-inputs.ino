#include "Servo.h"

Servo servobrat1,servobrat2;//de exemplu:
//servobrat1->cel care schimba unghiul de la care apuca gripperul
//servobrat2 -> duce bratul mai in fata/spate sau chiar il roteste
Servo gripper;
//controleaza daca gheara va strange sau isi va da release

#define servoPin 9
#define servoPin2 10
#define servoPin3 11
#define basicAngle 15
void setup() {
  servobrat1.attach(servoPin);
  servobrat1.attach(servoPin2);
  gripper.attach(servoPin3);
  Serial.begin(9600);
  

}
void cadran1(){
// dai in spate dreapta
//dupa mergi otara in fata pana iti ajunge in c5
//verifici daca a ajuns in c5
}
void cadran2(){
  //mergi putin in fata pana ajungi in c5
  //verifici daca a ajuns in c5
}
void cadran3(){
  //dai putin in spate stanga
  //verifici daca a ajuns in c5
}
void cadran4(){
  //same like cadran1 doar ca mersul este de o distanta mai mica
   //verifici daca a ajuns in c5
}
void cadran5(){
  //cazul cel mai ideal
  //bratul poate apuca obiectele fara prea mari probleme
 // valori idk dar cred ca va fi prob ceva de genu
 /*servobrat2.write(-2*basicAngle);
   servobrat1.write(basicAngle);
   gripper.write(12*basicAngle); in caz ca 180 grade ar reprezenta inchis
   servobrat2.write(4*basicAngle); incepe sa il dea peste cap
   servobrat1.write(-basicAngle);
   gripper.write(0); ii da drumul in cuva
   servobrat2.write(-4*basicAngle); 
    servobrat1.write(2*basicAngle); pentru al duce la poz init
    si asa mai departe pt cate obiecte ar gasi
 */
}
void cadran6(){
  //same like cadran3 doar ca dist parcursa e mai mica
   //verifici daca a ajuns in c5
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
