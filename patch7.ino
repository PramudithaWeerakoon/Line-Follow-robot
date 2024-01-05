#define enA 10 // Enable1 L298 Pin enA
#define in1 9  // Motor1 L298 Pin in1
#define in2 8  // Motor1 L298 Pin in2
#define in3 7  // Motor2 L298 Pin in3
#define in4 6  // Motor2 L298 Pin in4
#define enB 5  // Enable2 L298 Pin enB

#define L_S A0      // IR sensor Right
#define R_S A1      // IR sensor Left
#define middle_ir_left A3 // middle left ir
#define middle_ir_right A2 // middle right ir


#define echo 12     // Echo pin
#define trigger 13  // Trigger pin

#define delayTime 10 // Time delay in milliseconds for smooth motion
#define waitTime 1000 

#define servo1 A4 // lower arm moter
#define servo2 A5 // lower middle arm moter
#define servo3 4 // lower upper arm moter
#define servo 2  // Servo pin
int Set=20;
int distance_L, distance_F, distance_R; 


void setup(){ // put your setup code here, to run once

Serial.begin(9600); // start serial communication at 9600bps

pinMode(R_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input

pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  


pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in4, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in3, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

analogWrite(enA, 65); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 65); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

servoPulse(servo1, 70);
servoPulse(servo2, 70);
servoPulse(servo3, 80);



pinMode(servo, OUTPUT);
pinMode(servo1,OUTPUT);
pinMode(servo2,OUTPUT);

 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
 for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }

 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }

distance_F = Ultrasonic_read();

delay(500);
}


void loop(){  
//==============================================
//     Line Follower and Obstacle Avoiding
//==============================================  

distance_F = Ultrasonic_read();
Serial.print("D F=");Serial.println(distance_F);


//if Right Sensor and Left Sensor are at White color then it will call forword function
if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) {
  if (distance_F > Set) {
    if (digitalRead(middle_ir_left) == HIGH) {
      Stop();
      for (int angle = 70; angle <= 150; angle++) {
        servoPulse(servo1, angle);
        delay(delayTime);
      }

      delay(waitTime);  // Wait at the end position

      for (int i =70;i<=150;i++) {
       servoPulse(servo2,i);
       delay(5);
      }
      delay(2000);

      for (int k =80;k<=90;k++) {  // top arm moter start
       servoPulse(servo3,k);
       delay(5);
      }
      
      delay(3000);

       for (int l =90;l>=80;l--) {  // top arm moter retact
       servoPulse(servo3,l);
       delay(10);
      }
      // Move from end position back to start position
       for (int j =150;j>=70;j--) {
       servoPulse(servo2,j);
       delay(10);
      }
      
      // Move from end position back to start position
      for (int angle = 150; angle >= 70; angle--) {
        servoPulse(servo1, angle);
        delay(delayTime);
      }

      delay(waitTime);  // Wait at the start position
      forword();
    } 
     else if (digitalRead(middle_ir_right) == HIGH) {
  Stop();
  for (int angle = 70; angle >= 0; angle--) { // Fix the loop condition here
    servoPulse(servo1, angle);
    delay(delayTime);
  }

  delay(waitTime);  // Wait at the end position

  for (int i =70;i<=150;i++) {
       servoPulse(servo2,i);
       delay(5);
      }
      delay(2000);
      
      for (int k =80;k<=90;k++) {  // top arm moter start
       servoPulse(servo3,k);
       delay(5);
      }
      
      delay(3000);

       for (int l =90;l>=80;l--) {  // top arm moter retact
       servoPulse(servo3,l);
       delay(10);
      }

      // Move from end position back to start position
       for (int j =150;j>=70;j--) {
       servoPulse(servo2,j);
       delay(10);
      }

  // Move from end position back to start position
  for (int angle = 0; angle <= 70; angle++) { // Fix the loop condition here
    servoPulse(servo1, angle);
    delay(delayTime);
  }

  delay(waitTime);  // Wait at the start position
  forword();
} else {
  forword();
}

  } else {
    Check_side();
  }
}


//if Right Sensor is Black and Left Sensor is White then it will call turn Right function
else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnLeft();}  

//if Right Sensor is White and Left Sensor is Black then it will call turn Left function
else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnRight();} 

//if Right Sensor is Black and Left Sensor is Black then it will call turn Stop function
else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){Stop();} 


   
delay(10);
}
void servoPulse (int pin, int angle){
int pwm = (angle*12) + 500;      // Convert angle to microseconds
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50); // Refresh cycle of servo
}


//**********************Ultrasonic_read****************************
long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}

void compareDistance(){
    if(distance_L > distance_R){
  turnLeft();
  delay(800);
  forword();
  delay(900);
  turnRight();
  delay(800);
  forword();
  delay(900);
  turnRight();
  delay(700);
  }
  else{
  turnRight();
  delay(800);
  forword();
  delay(900);
  turnLeft();
  delay(800);
  forword();
  delay(900);  
  turnLeft();
  delay(700);
  }
}

void Check_side(){
    Stop();
    delay(100);
 for (int angle = 85; angle <= 155; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    distance_R = Ultrasonic_read();
    Serial.print("D R=");Serial.println(distance_R);
    delay(100);
  for (int angle = 155; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
    Serial.print("D L=");Serial.println(distance_L);
    delay(100);
 for (int angle = 0; angle <= 85; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    compareDistance();
}

void forword(){  //forword
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, HIGH); //Left Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor backword Pin 
}
void backword(){  //backword
digitalWrite(in1, HIGH); //Left Motor forword Pin 
digitalWrite(in2, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
}
void turnRight(){ //turnRight
digitalWrite(in2, LOW); //Left Motor backword Pin 
digitalWrite(in1, HIGH); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, HIGH); //Right Motor backword Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in2, HIGH); //Left Motor backword Pin 
digitalWrite(in1, LOW); //Left Motor forword Pin 
digitalWrite(in3, HIGH); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Left Motor backword Pin 
digitalWrite(in2, LOW); //Left Motor forword Pin 
digitalWrite(in3, LOW); //Right Motor forword Pin 
digitalWrite(in4, LOW); //Right Motor backword Pin 
}
