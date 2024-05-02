int ms1=4;
int ms2=13;
int md1=16;
int md2=17;

const int freq = 1000;
const int msChannel = 0;
const int mdChannel = 1;
const int resolution = 8;

void setup() {
  // put your setup code here, to run once:
   pinMode(ms1, OUTPUT);
   pinMode(ms2, OUTPUT);
   pinMode(md1, OUTPUT);
   pinMode(md2, OUTPUT);
   ledcSetup(msChannel, freq, resolution);
   ledcSetup(mdChannel, freq, resolution);
   
  
}



void loop() {
  // put your main code here, to run repeatedly:
  ledcAttachPin(ms2, msChannel);
  ledcAttachPin(md2, mdChannel);
  ledcWrite(msChannel, 100); 
  ledcWrite(mdChannel, 255); 
  digitalWrite(ms1, LOW);
  digitalWrite(md1, LOW);
}
