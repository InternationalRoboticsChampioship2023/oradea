#include <QTRSensors.h>

// Atentie !senzorul sa fie orientat spre exterior
QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
int MOTOR2_PIN1 = 3;
int MOTOR2_PIN2 = 5;
int MOTOR1_PIN1 = 9;
int MOTOR1_PIN2 = 6;
int vitezaMS;
int vitezaMD;
int viteza_croaziera=255; /// se creste pana la maxim 255;
int poz_ref=35;
//best so far 15 91
int Kp=1;  //se poate modifica  (acceleratie) valoare prea mare duce la instabilitate
float Kd=40; //se poate modifica   (frana/redresare) valoare prea mare duce la instabilitate
int eroare;
int eroare_ant;
int derivativ;
int comanda;
bool sp = true;
uint8_t pins[8] = {A0, A1, A2, A3, A4, A5,A6,A7};

void setup()
{
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  // configure the sensors
  qtr.setTypeAnalog();
  Serial.begin(9600);
  //  qtr.setSensorPins((const uint8_t[]){A7, A6, A5, A4, A3, A2,A1,A0}, SensorCount);
  qtr.setSensorPins(pins, SensorCount);
  qtr.setEmitterPin(2);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  for (uint16_t i = 0; i < 100; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration
 
  delay(1000);
}
void loop()
{
  uint16_t position = qtr.readLineBlack(sensorValues)/100;
  
  eroare=poz_ref-position;
  //Serial.println(position);
  derivativ=eroare-eroare_ant;
  comanda=Kp*eroare+Kd*derivativ;
  vitezaMS=viteza_croaziera+comanda;
  vitezaMD=viteza_croaziera-comanda;
  if(vitezaMS>=255)
  {
    vitezaMS=255;
  }
  if(vitezaMD>=255)
  {
    vitezaMD=255;
  }
  if(vitezaMS<=-255)
  {
    vitezaMS=-255;
  }
  if(vitezaMD<=-255)
  {
    vitezaMD=-255;
  }
  sp = finish();
  if(sp == 1){
   go(vitezaMS,vitezaMD); 
  }else{
    go(-20,-20);
  }
  eroare_ant=eroare;
}

bool finish(){
  bool ok = 1;
  int cnt = 0;
  for(int i =0;i<8;i++){
    if(analogRead(pins[i])<750){
      cnt++;
    }
  }
  if(cnt >6){
    ok = 0;
  }
  return ok;
}

void go(int speedLeft, int speedRight) {
  if (speedLeft > 0) {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  } 
  else {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }
  if (speedRight > 0) {
    analogWrite(MOTOR2_PIN1, speedRight);
    analogWrite(MOTOR2_PIN2, 0);

  }else {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}
