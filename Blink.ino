/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  int i;
  // initialize digital pin 13 as an output.
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
 //  Serial.begin(9600);
  for(i = 0; i < 5; i++) {
  digitalWrite(i, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);   
    }
}

void style1() {
  int i;
  for(i = 0; i < 5; i++) {
  digitalWrite(i, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);   
    }
    
  for(i = 4; i >= 0; i--) {
  digitalWrite(i, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);        
    }
  }
  void style2() {
  int i;
  for(i = 0; i < 3; i++) {
  digitalWrite(i, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5-i, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);   
    }
    
  for(i = 0; i < 3 ; i++) {
  digitalWrite(2+i, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(2-i, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(200);   
    }
  }
// the loop function runs over and over again forever
void loop() {

  int sensorValue = analogRead(A0);

  if(sensorValue){
      style1();
  } else {
     style2();
    }
}
