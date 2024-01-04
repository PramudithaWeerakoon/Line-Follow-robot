#define enA 10 // Enable1 L298 Pin enA
#define in1 9  // Motor1 L298 Pin in1
#define in2 8  // Motor1 L298 Pin in2
#define in3 7  // Motor2 L298 Pin in3
#define in4 6  // Motor2 L298 Pin in4
#define enB 5  // Enable2 L298 Pin enB

#define R_S A0 // IR sensor Right
#define L_S A1 // IR sensor Left

#define echo 12    // Echo pin
#define trigger 13 // Trigger pin

void setup() {
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(R_S, INPUT);
  pinMode(L_S, INPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void moveForward() {
  Serial.println("Moving Forward");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 65);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 65);
}

void turnLeft() {
  Serial.println("Turning Left");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 65);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 65);
}

void turnRight() {
  Serial.println("Turning Right");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 65);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 65);
}

void stopMotors() {
  Serial.println("Stopping Motors");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}

int getDistance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  int duration = pulseIn(echo, HIGH);
  int distance = duration / 58; // Convert pulse duration to distance (cm)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void loop() {
  int rightSensor = digitalRead(R_S);
  int leftSensor = digitalRead(L_S);
  int distance = getDistance();

  // If an obstacle is detected, stop
  if (distance <= 15) {
    stopMotors();
    // Add additional behavior or adjustments as needed
  } else {
    // Perform line following
    if (rightSensor == HIGH && leftSensor == HIGH) {
      stopMotors();
    } else if (rightSensor == LOW && leftSensor == LOW) {
      moveForward();
    } else if (rightSensor == HIGH && leftSensor == LOW) {
      turnRight();
    } else if (rightSensor == LOW && leftSensor == HIGH) {
      turnLeft();
    }
    // Add additional line-following behaviors as needed
  }
}
