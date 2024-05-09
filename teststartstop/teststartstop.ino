

//#define startstopbutton A1;


void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);

  Serial.begin(9600);   
  

}

void loop() {
  
if(digitalRead(2)==HIGH){
  Serial.print("ioi");
}
  

}
