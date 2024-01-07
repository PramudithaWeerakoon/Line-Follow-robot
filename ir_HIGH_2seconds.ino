const int sensorPin = 2;  // Replace with the actual pin connected to your sensor
const int motorPin = 9;   // Replace with the actual pin connected to your motor

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Read the state of the sensor
  int sensorState = digitalRead(sensorPin);

  if (sensorState == HIGH) {
    delay(2000); // Wait for 2 seconds

    // Check again after 2 seconds
    sensorState = digitalRead(sensorPin);

    if (sensorState == HIGH) {
      // Stop the car
      digitalWrite(motorPin, LOW);
    }
  }

  // Continue with other tasks or code as needed
}
