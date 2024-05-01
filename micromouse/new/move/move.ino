int ms1=15;
int ms2=2;
int md1=0;
int md2=4;
#define EncoderS 12
#define EncoderD 13
int Count_pulsesS = 0;
int Count_pulsesD = 0;

const int freq = 1000;
const int msChannel = 0;
const int mdChannel = 1;
const int resolution = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  ledcSetup(msChannel, freq, resolution);
  ledcSetup(mdChannel, freq, resolution);
  pinMode(EncoderS,INPUT); // sets the Encoder_output_A pin as the input
  pinMode(EncoderD,INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderD),DC_MotorD,RISING);
}



void loop() {
  // put your main code here, to run repeatedly:
  motors(100, -100);
}

void motors(int vst, int vdr){
  if(vst >= 0){
    ledcDetachPin(ms1);
    digitalWrite(ms1, LOW);
    ledcWrite(msChannel, vst);
    ledcAttachPin(ms2, msChannel);
  }else{
    ledcDetachPin(ms2);
    digitalWrite(ms2, LOW);
    ledcWrite(msChannel, abs(vst));
    ledcAttachPin(ms1, msChannel);
  }
  if(vdr >= 0){
    ledcDetachPin(md1);
    digitalWrite(md1, LOW);
    ledcWrite(mdChannel, vdr);
    ledcAttachPin(md2, mdChannel);
  }else{
    ledcDetachPin(md2);
    digitalWrite(md2, LOW);
    ledcWrite(mdChannel, abs(vdr));
    ledcAttachPin(md1, mdChannel);
  }
}

void DC_MotorS(){
  int ES = 16;
  if(digitalRead(ES)==HIGH){
    Count_pulsesS--; 
  }else{
    Count_pulsesS++; 
  }
  
}
void DC_MotorD(){
  int ED = 17;
  if(digitalRead(ED)==HIGH){
    Count_pulsesD++; 
  }else{
    Count_pulsesD--;
  }
}
