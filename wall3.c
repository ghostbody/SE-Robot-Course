#define  Measure  2     //Mode select
#include <Servo.h>                                  // Include Servo library
Servo myservo;

// These two ends are used for chao sheng bo chuan gan qi
int URECHO = 4;         // PWM Output 0-25000US,Every 50US represent 1cm
int URTRIG = 5;         // PWM trigger pin

int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store he value coming from the sensor

int EnablePin1 = 11;
int EnablePin2 = 3;

int wall = 0; // left wall;
int pos = 0; // the degree of the 舵机

int in[4] = {7, 8 , 12, 13};

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

  pinMode(EnablePin1, OUTPUT); // right
  pinMode(EnablePin2, OUTPUT); // left

  myservo.write(0);
  pos = 0;
  if(getDistance() < 40) { //wall is on the right
      Serial.println("right wall");
      wall = 1;
  } else { // wall is on the left
      Serial.println("left wall");
      myservo.write(180);
      pos = 180;
  }

  delay(1000)
  analogWrite(EnablePin1, 80);
  analogWrite(EnablePin2, 80);

  move_straight();
}

void loop() {
  int distance = getDistance();
  myservo.write(pos);
  move_straight();

 if (distance < 10) { //距离很小时转向
   if (wall == 0) { //wall is on the left
     turn_right();
     delay(500);
     move_straight();
     delay(500);
     turn_left();
     delay(500);
   } else { //wall is on the right
     turn_left();
     delay(500);
     move_straight();
     delay(500);
     turn_right();
     delay(500);
   }
 } else if (distance < 60) {  //距离再１０到５０之间直走
   move_straight();
   delay(500);
 } else {  //距离很大时转向
    if (wall == 0) { //wall is on the left
     delay(500);
     turn_left();
     delay(500);
    move_straight();
    delay(500);
     turn_right();
     delay(500);
   } else { //wall is on the right
     turn_right();
     delay(500);
     move_straight();
     delay(500);
     turn_left();
     delay(500);
   }
 }
}

void turn_left() {
  pos += 60; // 舵机先转６０度
  myservo.write(pos);
  analogWrite(EnablePin2, 60);
  delay(60);
  analogWrite(EnablePin2, 80)
}

void turn_right() {
  pos -= 60; // 舵机先转６０度
  analogWrite(EnablePin1, 60);
  delay(60);
  analogWrite(EnablePin1, 80)
}

void move_straight() {
  pos = 90;
  myservo.write(pos);
  digitalWrite(in[0], LOW);
  digitalWrite(in[1], HIGH);
  digitalWrite(in[2], LOW);
  digitalWrite(in[3], HIGH);
}

int getDistance() {
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  int DistanceMeasured;
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


