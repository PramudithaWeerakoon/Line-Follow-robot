#define enA 10 // Enable1 L298 Pin enA
#define in1 9  // Motor1 L298 Pin in1
#define in2 8  // Motor1 L298 Pin in2
#define in3 7  // Motor2 L298 Pin in3
#define in4 6  // Motor2 L298 Pin in4
#define enB 5  // Enable2 L298 Pin enB

#define R_S A0 // IR sensor Right
#define L_S A1 // IR sensor Left

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(R_S, INPUT);
  pinMode(L_S, INPUT);
}

void moveForward() {
  digitalWrite(in1, LOW);  // Reverse these two lines
  digitalWrite(in2, HIGH); // Reverse these two lines
  analogWrite(enA, 65);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 65);
}


void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 65);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 65);
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 65);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 65);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}

void loop() {
  int rightSensor = digitalRead(R_S);
  int leftSensor = digitalRead(L_S);

  // If both sensors are on a black line, stop
  if (rightSensor == HIGH && leftSensor == HIGH) {
    stopMotors();
  }
  // If both sensors are on a white surface, move forward
  else if (rightSensor == LOW && leftSensor == LOW) {
    moveForward();
  }
  // If only the left sensor is on a black line, turn right
  else if (rightSensor == HIGH && leftSensor == LOW) {
    turnRight();
  }
  // If only the right sensor is on a black line, turn left
  else if (rightSensor == LOW && leftSensor == HIGH) {
    turnLeft();
  }
  // Handle other cases (adjust as needed)
  else {
    // You may want to add specific behavior for different sensor conditions here
  }
}
