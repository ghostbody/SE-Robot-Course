#include <Servo.h>                                  // Include Servo library
Servo myservo;  

int pos=90;
int URECHO = 9;         // PWM Output 0-25000US,Every 50US represent 1cm
int URTRIG = 10;         // PWM trigger pin
int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store the value coming from the sensor
boolean up = false;

int EnablePin1 = 11;  //right
int EnablePin2 = 3; //left

int in[4] = {8, 7 , 13, 12};

void setup() 
{
  Serial.begin(9600);                        // Sets the baud rate to 9600
  pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                 // Set to HIGH 
  pinMode(URECHO, INPUT);   
  myservo.attach(6);    // Set to HIGH 
  pinMode(in[0], OUTPUT);
  pinMode(in[1], OUTPUT);
  pinMode(in[2], OUTPUT);
  pinMode(in[3], OUTPUT);

  digitalWrite(in[0], LOW);
  digitalWrite(in[1], HIGH);
  digitalWrite(in[2], LOW);
  digitalWrite(in[3], HIGH);

  analogWrite(EnablePin1, 255); // right
  analogWrite(EnablePin2, 255); //left
  myservo.write(90);
}


        
void move_straight() {
  digitalWrite(in[0], LOW);
  digitalWrite(in[1], HIGH);
  digitalWrite(in[2], HIGH);
  digitalWrite(in[3], LOW);
  //delay(80);
}

void stop_move() {
  digitalWrite(in[0], LOW);
  digitalWrite(in[1], LOW);
  digitalWrite(in[2], LOW);
  digitalWrite(in[3], LOW);
}

void left() {
  digitalWrite(in[0], LOW);
  digitalWrite(in[1], HIGH);
  digitalWrite(in[2], LOW);
  digitalWrite(in[3], LOW);
  delay(60);
  stop_move();
}

void right() {
  digitalWrite(in[0], LOW);
  digitalWrite(in[1], LOW);
  digitalWrite(in[2], HIGH);
  digitalWrite(in[3], LOW);
  delay(60);
  stop_move();
}

void loop()
{                        // in steps of 1 degree
     search();
}

void search() {
    if(pos == 30)  up= false;                       // assign the variable again  
    if(pos==150)  up= true;                       // assign the variable again 
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
  int DistanceMeasured = 0;
    unsigned long LowLevelTime = pulseIn(URECHO, LOW) ;
    if(LowLevelTime>=45000) {
      return 9999;
    } else {
      DistanceMeasured = LowLevelTime /50;
      Serial.print(DistanceMeasured);
      Serial.println("cm");
    return DistanceMeasured;
  }
}



void turn(int pos) {
              if (pos == 45) {
                Serial.println("pos = 45");
                right();
                right();
                right();
              } else if (pos == 60) {
                Serial.println("pos = 60");
                right();
                right();
               } else if (pos == 75){
                 Serial.println("pos = 75:");
                right();
              } else if (pos == 90) {
                Serial.println("pos = 90: move_straight()");
                move_straight();
                //search();
              } else if (pos == 105) {
                Serial.println("pos = 105:");
                left();
              } else if (pos == 120) {
                Serial.println("pos = 120:");
                left();
                left();
              } else if (pos == 135) {
                Serial.println("pos = 135: left()");
                left();
                left();
                left();
                //delay(500); 
              } else if (pos == 30) {
                right();
                right();
                right();
                right();
              } else if (pos == 150) {
                left();
                left();
                left();
                left();
              }
  }

