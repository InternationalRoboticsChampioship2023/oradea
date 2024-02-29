/* Servo motor with Arduino example code. Position and sweep. More info: https://www.makerguides.com/ */

// Include the servo library:
#include "Servo.h"

// Create a new servo object:
Servo myservo;

// Define the servo pin:
#define servoPin 9

void setup() {
  // Attach the Servo variable to a pin:
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(data);
    myservo.write(data.toInt());
  }
  
}
