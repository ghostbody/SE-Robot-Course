
int EnablePin1 = 11;
int EnablePin2 = 3;

int Sensor1 = A3;  // left
int Sensor2 = A4;  // middle
int Sensor3 = A5;  // right

int in[4] = {7, 8, 13, 12};

int speed0 = 150;
double straightfac = 0;
double turnfac = 0;

void setup() {
  Serial.begin(9600);                        // Sets the baud rate to 9600

  pinMode(in[0], OUTPUT);
  pinMode(in[1], OUTPUT);
  pinMode(in[2], OUTPUT);
  pinMode(in[3], OUTPUT);

  pinMode(EnablePin1, OUTPUT);
  pinMode(EnablePin2, OUTPUT);

  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);

  digitalWrite(in[0], HIGH);
  digitalWrite(in[1], LOW);
  digitalWrite(in[2], HIGH);
  digitalWrite(in[3], LOW);
  move_straight();
}

void loop() {
  int seValue_left = digitalRead(Sensor1);
  int seValue_center = digitalRead(Sensor2);
  int seValue_right = digitalRead(Sensor3);

  if(!seValue_center) {
      turnfac = 0;
    if(straightfac < 90) {
      straightfac += 4;
    }
    move_straight();
    //return;
    } else {
      straightfac=0;
      //return;
    }
  
  if(!seValue_left) {
      straightfac=0;
      turn_left();
      while(digitalRead(Sensor2)){
    if(turnfac < 30) {
      turnfac += 5;
    }
      turn_left();
        straightfac /= 4;
      }
      turnfac = 0;
      //return;
  }
  if(!seValue_right) {
      straightfac=0;
      while(digitalRead(Sensor2)){
    if(turnfac < 30) {
      turnfac += 5;
    }
      turn_right();
        straightfac /= 4;
      }
      turnfac = 0;
     // return;
  }

}


void turn_left() {
  analogWrite(EnablePin1, speed0+turnfac-40);
  analogWrite(EnablePin2, 0);
  //delay(50);
}

void turn_right() {
  analogWrite(EnablePin2, speed0+turnfac-40);
  analogWrite(EnablePin1, 0);
  //delay(50);
}

void move_straight() {
  analogWrite(EnablePin2, speed0+straightfac);
  analogWrite(EnablePin1, speed0+straightfac);
  //delay(50);
}


