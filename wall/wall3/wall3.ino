#define  Measure  2     //Mode select
#include <Servo.h>                                  // Include Servo library
Servo myservo;

// These two ends are used for chao sheng bo chuan gan qi
int URECHO = 9;         // PWM Output 0-25000US,Every 50US represent 1cm
int URTRIG = 10;         // PWM trigger pin

int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store he value coming from the sensor

int EnablePin1 = 11;
int EnablePin2 = 3;

int wall = 0; // left wall;
int pos = 0; // the degree of the 舵机

int in[4] = {7, 8 , 12, 13};

int search_distance = 30;

int speadLeft[2] = {60, 80} ;
int speadRight[2] = {80, 100};

//小车的右边位０度，左边为１８０度

void setup() {
  Serial.begin(9600);                        // Sets the baud rate to 9600
  pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                 // Set to HIGH 
  pinMode(URECHO, INPUT);   
  myservo.attach(6);    // Set to HIGH

  // In1 In2 In3 In4
  pinMode(in[0], OUTPUT);
  pinMode(in[1], OUTPUT);
  pinMode(in[2], OUTPUT);
  pinMode(in[3], OUTPUT);

  digitalWrite(in[0], LOW);
  digitalWrite(in[1], HIGH);
  digitalWrite(in[2], LOW);
  digitalWrite(in[3], HIGH);

  pinMode(EnablePin1, OUTPUT);
  pinMode(EnablePin2, OUTPUT);
  
  myservo.write(0); // look on the left
  delay(50);
  pos = 0;
  //move_straight();
  
  if(getDistance() < search_distance) { //wall is on the left
    Serial.println("left wall");
    wall = 0;
  } else {
    myservo.write(180); // look right
     pos = 180;
    wall = 1;
  }
}

void loop() {
  move_straight();
    stop_move();
  delay(3000);
  turn_right();
//  if (wall == 0) { // wall is on the left
//    move_straight();
//    while (1) {
//      myservo.write(0); //look left
//      pos = 0;
//      if (getDistance() < search_distance) {
//        Serial.println(getDistance());
//         myservo.write(90); //look forward
//         pos = 90;
//         if (getDistance() < search_distance) {
//            turn_right();
//         } else {
//            break;
//         }
//    } else {
//      turn_left();
//    }
//  }//while
// } else { // wall is on the right
//   move_straight();
//   while (1) {
//      myservo.write(180); //look right
//      pos = 180;
//      if (getDistance() < search_distance) {
//         myservo.write(90); //look forward
//         pos = 90;
//         if (getDistance() < search_distance) {
//            turn_left();
//         } else {
//            break;
//         }
//    } else {
//      turn_right();
//    }
//  }//while
// }
}

void turn_left() {
  pos += 60; // 舵机先转６０度
  myservo.write(pos);
  Serial.println("turn_left()");
  analogWrite(EnablePin1, 255); // left
  analogWrite(EnablePin2, speadLeft[0]);
  delay(60);
  analogWrite(EnablePin2, speadLeft[1]);
}

void turn_right() {
  pos -= 60; // 舵机先转６０度
  myservo.write(pos);
  Serial.println("turn_right()");
   analogWrite(EnablePin2, 255); // left
  analogWrite(EnablePin1, speadRight[0]); // right
  delay(60);
  analogWrite(EnablePin1, speadLeft[1]); //right
}

void move_straight() {
  Serial.println("move_stragiht()");
  pos = 90;
  myservo.write(pos);
  analogWrite(EnablePin1, speadRight[0]);
  analogWrite(EnablePin2, speadLeft[1]);
}

void stop_move() {
  digitalWrite(in[0], LOW);
  digitalWrite(in[1], LOW);
  digitalWrite(in[2], LOW);
  digitalWrite(in[3], LOW);
}

int getDistance() {
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  int DistanceMeasured;
  unsigned long LowLevelTime = pulseIn(URECHO, LOW);
  if(LowLevelTime>=45000) {
    return 9999;
  } else {
    DistanceMeasured = LowLevelTime /50;
    Serial.print(DistanceMeasured);
    Serial.println("cm");
    return DistanceMeasured;
  }
}



