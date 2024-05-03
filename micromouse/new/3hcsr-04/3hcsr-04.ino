//for faster readings use 3 trig pins
//time beetween trig signals on sensor must be >60ms

const int trigPin = 32;
const int echoPinS = 26;
const int echoPinM = 25;
const int echoPinD = 33;


float distanceS, distanceM, distanceD;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinS, INPUT);
  pinMode(echoPinM, INPUT);
  pinMode(echoPinD, INPUT);
  Serial.begin(115200);
}

void loop() {
  distanceS = get_sensor(echoPinS);
  distanceM = get_sensor(echoPinM);
  distanceD = get_sensor(echoPinD);
  Serial.print(distanceS);
  Serial.print(",");
  Serial.print(distanceM);
  Serial.print(",");
  Serial.print(distanceD);
  Serial.println("");
  //delay(100);
}

int get_sensor(int pin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float d;
  d = pulseIn(pin, HIGH);
  delay(60);
  return(d*.0343)/2;
}
