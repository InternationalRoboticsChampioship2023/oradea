int ms1=15;
int ms2=2;
int md1=0;
int md2=4;

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
   ledcAttachPin(ms2, msChannel);
  ledcAttachPin(md2, mdChannel);
}



void loop() {
  // put your main code here, to run repeatedly:
  ledcWrite(msChannel, 100); 
  ledcWrite(mdChannel, 255); 
  digitalWrite(ms1, LOW);
  digitalWrite(md1, LOW);
}
