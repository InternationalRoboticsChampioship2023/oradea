 #define outputA A0
 #define outputB A1
 #define M2speed 6
 #define M2a 8
 #define M2b 9

 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode (M2speed,OUTPUT);
   pinMode (M2a,OUTPUT);
   pinMode (M2b,OUTPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 

 void loop() { 
   aState = digitalRead(outputA);// Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState && aState == HIGH){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB)==HIGH) { 
       counter --;
     } else {
       counter ++;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 

   if(counter>0){
     digitalWrite(M2a, HIGH);
     digitalWrite(M2b, LOW);
     analogWrite (M2speed, 100);
   }else if(counter<0){
     digitalWrite(M2a, LOW);
     digitalWrite(M2b, HIGH);
     analogWrite (M2speed, 100);
   }else{
     digitalWrite(M2a, LOW);
     digitalWrite(M2b, LOW);
     analogWrite (M2speed, 100);
     
   }
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }
