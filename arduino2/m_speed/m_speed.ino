#define MSV 5
#define MS1 A2
#define MS2 4
#define EncoderS 2
int ms = 0,x;
float elapsedTime, currentTime, previousTime,m_speed;
int Count_pulsesS = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MSV, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EncoderS,INPUT);
  attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  x = Serial.read();
  if(x!=-1){
    ms=x*20;
  }
  analogWrite(MSV, abs(ms));
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  m_speed = Count_pulsesS *120/ elapsedTime;
  Serial.println(m_speed);
  Count_pulsesS=0;
}

void DC_MotorS(){
  int ES = A0;
  if(digitalRead(ES)==HIGH){
    Count_pulsesS--; 
  }else{
    Count_pulsesS++; 
  }
  
}
