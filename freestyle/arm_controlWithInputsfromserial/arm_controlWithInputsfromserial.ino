#include <Servo.h>
#define gripperpin 3
#define servo1pin 5
#define servo2pin 6
#define servo3pin 9
Servo gripper;
Servo bm1;
Servo bm2;
Servo base;
int baseval=0;
int mijloc=0;
int gripperval=0;
int difmijloc=180;
const int maxpos=180;
const int minpos=50;
void setup() {
  gripper.attach(gripperpin);
base.attach(servo3pin);
bm1.attach(sevo1pin);
bm2.attach(servo2pin);
Serial.begin(9600);
gotorestpos();
}

void gotorestpos(){

while(baseval!=90){
if(baseval>90) {baseval--;}
else{
basevall++;
}
base.write(baseval);
}
delay(20);

while(mijloc!=90){
if(mijloc>90) {mijloc--;}
else{
mijloc++;
}
bm1.write(mijloc);
bm2.write(90+mijloc);
}
delay(20);

  gripper.write(minpos);
}






void catchobj(){
  //daca intra in functie inseamna ca a detectat ceva ce poate apuca
 
  gripper.write(maxpos); //deshid gripperul
 
 while(baseval>0){
  basevall--;
  base.write(baseval);//duc baseul la 0 
 }
 delay(20);
  

while(mijloc>0){
  mijloc --;
  bm1.write(mijloc);  //duc bm1 la 0
bm2.write(difmijloc-mijloc);//duc bm2 la 180
}
delay(20);

gripper.write(minpos); // duc gripper la 0 aka inchis
  
while(baseval<90){
  baseval++;
  base.write(baseval);//duc base inapoi la 90
}
delay(20);

while(mijloc<180){
  mijloc++;
   bm1.write(mijloc);  // duc bm1 la 180
bm2.write(difmijloc-mijloc);// duc bm2 la 0
}
 gripper.write(maxpos);// deshid gripper aka maxpos / 180
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
