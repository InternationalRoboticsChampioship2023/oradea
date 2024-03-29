// A6, A7 do not support digial funcitons =>pulseIn does not work

int trigPin = 9;    // Trigger
int echoS = A3;    // Echo
int echoC = A1;
int echoD = A0;
float SensorS,SensorC,SensorD;
 
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
  SensorS = dist_sensor(echoS);
  SensorC = dist_sensor(echoC);
  SensorD = dist_sensor(echoD);
  Serial.print(SensorS);
  Serial.print(" - ");
  Serial.print(SensorC);
  Serial.print(" - ");
  Serial.print(SensorD);
  Serial.println();
}

float dist_sensor(int echoPin){
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 10000);
  delay(5);
  return duration*0.0343/2;
}
