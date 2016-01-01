
int EnablePin1 = 11;
int EnablePin2 = 3;

int Sensor1 = A5;  // left
int Sensor2 = A4;  // middle
int Sensor3 = A3;  // right

int in[4] = {7, 8, 13, 12};

int speed_left = 255;
int speed_right = 255;

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

  digitalWrite(in[0], LOW);
  digitalWrite(in[1], HIGH);
  digitalWrite(in[2], LOW);
  digitalWrite(in[3], HIGH);
}

void loop() {
  move_straight();
}

void turn_right() {
  analogWrite(EnablePin1, 255);
  analogWrite(EnablePin2, 0);
}

void turn_left() {
  Serial.print("seValue_left: ");
  analogWrite(EnablePin1, 0); //left
  analogWrite(EnablePin2, 255);
}

void move_straight() {
  Serial.println("aaa");
  analogWrite(EnablePin1, speed_left);
  analogWrite(EnablePin2, speed_right);
}

