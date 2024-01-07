// Define pin numbers
const int irSensorPin = 2;  // Connect the IR sensor to digital pin 2
const int motorPin1 = 3;   // Connect motor driver input 1 to digital pin 3
const int motorPin2 = 4;   // Connect motor driver input 2 to digital pin 4

// Define states for the state machine
enum State {
  WAITING_LOW,
  WAITING_HIGH,
  WAITING_SECOND_LOW,
  CAR_STOPPED
};

// Initialize the state machine
State currentState = WAITING_LOW;

void setup() {
  // Set pin modes
  pinMode(irSensorPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  // Read the state of the IR sensor
  int irSensorState = digitalRead(irSensorPin);

  // Update the state machine based on the IR sensor state
  switch (currentState) {
    case WAITING_LOW:
      if (irSensorState == LOW) {
        currentState = WAITING_HIGH;
      }
      break;

    case WAITING_HIGH:
      if (irSensorState == HIGH) {
        currentState = WAITING_SECOND_LOW;
      }
      break;

    case WAITING_SECOND_LOW:
      if (irSensorState == LOW) {
        currentState = CAR_STOPPED;
        stopCar();
      } else {
        currentState = WAITING_LOW;  // Reset if the sequence is not completed
      }
      break;

    case CAR_STOPPED:
      // Car is already stopped, do nothing
      break;
  }
}

// Function to stop the car
void stopCar() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
