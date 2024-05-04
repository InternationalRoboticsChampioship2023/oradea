//for faster readings use 3 trig pins
//time beetween trig signals on sensor must be >60ms

const int trigPin = 32;
const int echoPinS = 26;
const int echoPinM = 25;
const int echoPinD = 33;


float distanceS, distanceM, distanceD;
bool wallS, wallM, wallD;
int distforwall = 6;

struct cell{
  bool wallS;
  bool wallM;
  bool wallD;
};

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
  if(distanceS < 6){//in cell dist from sensor to wall is 3.1cm
    wallS = 1;
  }else{
    wallS = 0;
  }
  if(distanceM < 6){
    wallM = 1;
  }else{
    wallM = 0;
  }
  if(distanceD < 6){
    wallD = 1;
  }else{
    wallD = 0;
  }
  Serial.print(wallS);
  Serial.print(",");
  Serial.print(wallM);
  Serial.print(",");
  Serial.print(wallD);
  Serial.println("");
  //delay(100);
}

cell get_walls(){
  cell aux;
  distanceS = get_sensor(echoPinS);
  distanceM = get_sensor(echoPinM);
  distanceD = get_sensor(echoPinD);
  if(distanceS < 6){//in cell dist from sensor to wall is 3.1cm
    aux.wallS = 1;
  }else{
    aux.wallS = 0;
  }
  if(distanceM < 6){
    aux.wallM = 1;
  }else{
    aux.wallM = 0;
  }
  if(distanceD < 6){
    aux.wallD = 1;
  }else{
    aux.wallD = 0;
  }
  return aux;
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
