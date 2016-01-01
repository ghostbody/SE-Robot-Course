#define  Measure  2     //Mode select
#include <Servo.h>                                  // Include Servo library
Servo myservo;  
int pos=90;
int URECHO = 4;         // PWM Output 0-25000US,Every 50US represent 1cm
int URTRIG = 5;         // PWM trigger pin
int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store the value coming from the sensor

int enablePin1 = 9;
int enablePin2 = 10;

int speadLeft;
int speadRight;

boolean up = true;
unsigned int DistanceMeasured= 0;
boolean ll = true;
void setup() 
{
  Serial.begin(9600);                        // Sets the baud rate to 9600
  pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                 // Set to HIGH 
  pinMode(URECHO, INPUT);  
  myservo.write(90);
      delay(5000);
}


        
void move_straight() {
  Serial.println("###");
  speadLeft = 255;
  speadRigh t= 255;
  delay(500);
  stop_move();
}

//void move_back() {
//  digitalWrite(7, HIGH);
//  digitalWrite(8, LOW);
//  digitalWrite(2, LOW);
//  digitalWrite(3, HIGH);
//  delay(200);
//  stop_move();
//}

void stop_move() {
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void left() {
   Serial.println("test left");
  speadLeft = 100;
  speadRigh t= 255;
  delay(60);
      Serial.println("test left");
  stop_move();
}

void left1() {
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(360);
  stop_move();
}

void right() {
      Serial.println("test right");
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(60);
  stop_move();
}

void right1() {
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(360);
  stop_move();
}

void loop()
{                        // in steps of 1 degree
    myservo.attach(6);    // Set to HIGH 
    
  analogWrite(enablePin1,speadRight);
  analogWrite(enablePin2,speadLeft);
  
  if(block()) {
    move_back();
    if(ll) {
    left();
    ll = false;
    } else {
      right();
      ll = true;
      }
  } else {
    move_straight();
  }
}

bool block() {
    if(getDistance() < 50) {
        return true;;
    } else return false;
  }

void search() {
    if(pos == 30)  up= true;                       // assign the variable again  
    if(pos==150)  up= false;                       // assign the variable again 
    int a = getDistance();
    Serial.print("diatance:  ");
    Serial.println(a);
    if(up){
         Serial.print("up:pos: ");// judge the condition
         Serial.println(pos);
            if (a < 50 ) {
               stop_move();
            }
            else if (a > 150) {
               pos=pos+15;                                  // in steps of 1 degree 
               myservo.write(pos);
               stop_move();  
            }
            else if (a >= 50 && a <= 150){
              turn(pos);
              myservo.write(90); 
              pos = 90;
            }
    }
    if(!up){ // judge the condition
       Serial.print("!up:pos: ");// judge the condition
       Serial.println(pos);
         if (a < 50 ) {
               stop_move();
            }
         else if (a > 150) {
               pos=pos-15;                                  // in steps of 1 degree 
               myservo.write(pos);  
                stop_move();
        }
        else if (a >= 50 && a <= 150) {
              turn(pos);
              pos = 90;
              myservo.write(90); 
       }
    } // !up
} // zhuanquan

int getDistance() {
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses  
  if( Measure) {
    unsigned long LowLevelTime = pulseIn(URECHO, LOW) ;
    if(LowLevelTime>=45000) {
      Serial.print(DistanceMeasured);
      Serial.println("cm");
      Serial.print("Invalid!");
      return 9999;
    } else {
    DistanceMeasured = LowLevelTime /50;
      Serial.print(DistanceMeasured);
      Serial.println("cm");
    return DistanceMeasured;
  }
  } else {
    sensorValue = analogRead(sensorPin); 
    if(sensorValue<=10) {
      Serial.print(sensorValue);
      Serial.println("cm!");
      Serial.print("Invalid!!");
      return 0;
    } else {
      sensorValue = sensorValue*0.718;      
      Serial.print(sensorValue);
      Serial.println("cm");
      return sensorValue;
    }
  } 
}


void turn(int pos) {
              if (pos == 2){
                 Serial.println("pos = 75:");
                right();
              } else if (pos == 3) {
                Serial.println("pos = 105:");
                left();
              } else if (pos == 0) {
        Serial.println("turn right");
                right1();
               } else if (pos == 1) {
        Serial.println("turn left");
                left1();
               }
  }
