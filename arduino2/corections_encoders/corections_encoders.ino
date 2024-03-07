#define EncoderS 2 // pin2 of the Arduino
#define EncoderD 3 // pin 3 of the Arduino
int MSV =5;
int MS1 =A2;
int MS2 =4;
int MDV =6;
int MD1 =8;
int MD2 =7;
int m_speed = 100, m_speedS, m_speedD;

int Count_pulsesS = 0;
int Count_pulsesD = 0;
void setup() {
  Serial.begin(9600); // activates the serial communication
  pinMode(EncoderS,INPUT); // sets the Encoder_output_A pin as the input
  pinMode(EncoderD,INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderD),DC_MotorD,RISING);
  pinMode(MSV, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MDV, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
}
 
void loop() {
  m_speedS=m_speed;
  m_speedD=m_speed;
  if(Count_pulsesS>Count_pulsesD){
    m_speedD+=50;
  }else if(Count_pulsesS<Count_pulsesD){
    m_speedS+=50;
  }
  Serial.print(m_speedS);
  Serial.print('\t');
  Serial.print(m_speedD);
  Serial.println();
  analogWrite(MSV, m_speedS);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, LOW);
  analogWrite(MDV, m_speedD);
  digitalWrite(MD1, HIGH);
  digitalWrite(MD2, LOW);
}
 
void DC_MotorS(){
  Count_pulsesS++; 
}
void DC_MotorD(){
  Count_pulsesD++;
}
