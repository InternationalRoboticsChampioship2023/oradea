/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo gripper;  // create servo object to control a servo
Servo fb;
Servo sj;
// twelve servo objects can be created on most boards

int gripper_pos = 0;    // variable to store the servo position
int fb_pos = 180;
int sj_pos = 180;
void setup() {
  gripper.attach(3);  // attaches the servo on pin 9 to the servo object
  fb.attach(5);
  sj.attach(6);
}

void loop() {
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
  //fb.write(180);
  //sj.write(180);
  
  while(1){
    ;
  }
  delay(2000);
}
