
#define  Measure  2     //Mode select
#include <Servo.h>                                  // Include Servo library
Servo myservo;  
int pos=90;
int URECHO = 4;         // PWM Output 0-25000US,Every 50US represent 1cm
int URTRIG = 5;         // PWM trigger pin
int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store the value coming from the sensor
boolean up = true;
unsigned int DistanceMeasured= 0;
int wall = 0; // left wall
int degree[2] = {180, 0};

void setup() 
{
  Serial.begin(9600);                        // Sets the baud rate to 9600
  pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                 // Set to HIGH 
  pinMode(URECHO, INPUT);   
  myservo.attach(6);    // Set to HIGH 
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  myservo.write(0);
      delay(5000);
  if(getDistance() < 40) {
        Serial.println("right wall");
    wall = 1;
    } else {
        Serial.println("left wall");
      myservo.write(180);
      delay(200);
      }
}

void move_straight1() {
  Serial.println("###");
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(50);
  stop_move();
}


void move_straight2() {
  Serial.println("###");
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(350);
  stop_move();
}
void move_straight() {
      Serial.println("###");
  int b = getDistance();
  if(wall == 0) {
    if(b < 10) {
      right();
      delay(200);
      move_straight1();
      delay(200);
      left();
    } else if (b > 50) {
      left();
      delay(200);
      move_straight1();
      delay(200);
      right();
    } else {
      move_straight1();
      }
   } else {
    if(b < 10) {
      left();
  delay(200);
      move_straight1();
  delay(200);
      right();
    } else if (b > 50) {
      right();
  delay(200);
      move_straight1();
  delay(200);
      left();
    } else {
      move_straight1();
      }
  }
   delay(1000);
}

void stop_move() {
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void left() {
  Serial.println("test left");
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(60);
  Serial.println("test left");
  stop_move();
}

void left1() {
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(220);
  stop_move();
  delay(200);
  move_straight1();
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
  delay(220);
  stop_move();
  delay(200);
  move_straight1();
}

void loop()
{                        // in steps of 1 degree
      myservo.write(degree[wall]);
      delay(500);
        Serial.println("forward");
      move_straight2();
      while(1) {      
      if(search_wall()) {
        Serial.println("wall at one side");
        myservo.write(90);
        delay(500);
        if(search_wall()) {
            Serial.println("wall in front");
            turn(wall);
            myservo.write(degree[wall]);
            delay(500);
        } else {
            Serial.println("nothing in front");
            break;
        }
        
      } else {
        Serial.println("no wall");
        Serial.println(!wall);
        turn(!wall);
        
        break;
      }
      
      }
}

bool search_wall() {
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
                move_straight1();
                left();
              } else if (pos == 3) {
                Serial.println("pos = 105:");
                left();
                move_straight1();
                right();
              } else if (pos == 0) {
        Serial.println("turn right");
                right1();
                move_straight1();
                left1();
               } else if (pos == 1) {
        Serial.println("turn left");
                left1();
                move_straight1();
                93
                right1();
               }
  }
