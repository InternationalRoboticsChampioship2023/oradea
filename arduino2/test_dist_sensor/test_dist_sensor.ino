// A6, A7 do not support digial funcitons =>pulseIn does not work

int trigPin = 9;    // Trigger
int echoS = A3;    // Echo
int echoC = A6;
int echoD = A7;
long duration;
float RightSensor,FrontSensor,LeftSensor,distance;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoS, INPUT);
  pinMode(echoC, INPUT);
  pinMode(echoD, INPUT);
}
 
void loop() {
  SonarSensor(trigPin, echoS);
  RightSensor = distance;
  SonarSensor(trigPin, echoC);
  LeftSensor = distance;
  SonarSensor(trigPin, echoD);
  FrontSensor = distance;

  Serial.print(LeftSensor);
  Serial.print(" - ");
  Serial.print(FrontSensor);
  Serial.print(" - ");
  Serial.println(RightSensor);
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}
