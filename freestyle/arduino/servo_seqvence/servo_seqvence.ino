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
int sj_pos = 0;
void setup() {
  gripper.attach(3);  // attaches the servo on pin 9 to the servo object
  fb.attach(5);
  sj.attach(6);
}

void loop() {
  fb.write(fb_pos);
  sj.write(sj_pos);
  for (gripper_pos = 50; gripper_pos <= 170; gripper_pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    gripper.write(gripper_pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
