//we simulate a robot that tracks an object 
//we detect it with the distance sensor
//because we are in the simulator and can't phisically get closer 
//we simulate the "approaching" process by computing the distance
//    between our robot and the object 
//also, the robot adjusts his speed, the closer it is to the object, 
//    the more it slows down
//when the object is reached, the motors are turned off
//    and the servo motor starts spinning to signal the goal
//if the object moves forward after it was reached 
//    the robot is turned on again and it goes towards it
//can only track objects that are in front of it 

#include <Servo.h>

Servo s;
int duration; //the duration needed by the ultrasound to reach back
int distance; //the distance from the sensor to the object 
int rotations; //the number of rotations the motors performed 
int speed; //the number of rotations of the wheels we need
int traversedDistance; //the distance the motors traversed
const int wheelDiameter = 2; //the diameter of a wheel 
int actualDistance; //the computed distance between the object and the sensor 
const int maxSpeed = 19; //the maximum speed we can reach

void setup()
{
  pinMode(12, OUTPUT); //the output for the distance sensor - trigger
  pinMode(11, INPUT); //input for the distance sensor - echo
  
  s.attach(8); //the servo is put on pin 8
  
  //the pins for the left motor
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  analogWrite(3, LOW);
  analogWrite(5, LOW);
  
  //the pins for the right motor
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  analogWrite(9, LOW);
  analogWrite(10, LOW);
  
  Serial.begin(9600);
}

void loop()
{
  computeDistanceFromSensor();
  computeTraversedDistance();
  
  //simulate the traversal of the distance
  actualDistance = distance - traversedDistance;
  Serial.println(actualDistance);
  
  //if we reached the object we stop the motors 
  //and turn the servo on 
  if(actualDistance <= 0)
  {
    turnOffMotors();
    startServo();
  }
  else 
  {
    speed = map(actualDistance, 0, 300, 1, maxSpeed); //set the speed depending on the distance
    //higher when far away, slow down as you approach
    activateMotors();
  }
}

//the distance between the sensor and the object 
void computeDistanceFromSensor()
{
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  
  duration = pulseIn(11, HIGH);
  distance = (duration * 0.034) / 2;
}

//simulate the distance traversed by using the motors 
void computeTraversedDistance()
{
  traversedDistance = rotations * wheelDiameter;
  rotations += speed;
}

//if the object is not yet reached, go towards it using the motors 
void activateMotors()
{
  //the left motor
  powerMotor(5, 3);
  
  //the right motor
  powerMotor(9, 10);
}

//power each motor individually
void powerMotor(int fw, int bw)
{
  digitalWrite(fw, map(speed, 0, maxSpeed, 0, 255));
  analogWrite(bw, 0);
  delay(20);
  
  analogWrite(fw,0);
  delay(20);
}

//if object is reached, the motors are off
void turnOffMotors()
{
  speed = 0;
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(9, 0);
  analogWrite(10, 0);
}

//if we reached the object, start the servo
void startServo()
{
  s.write(0);
  delay(700);
  s.write(45);
  delay(700);
  s.write(90);
  delay(700);
  s.write(135);
  delay(700);
  s.write(180);
  delay(700);
  s.write(135);
  delay(700);
  s.write(90);
  delay(700);
  s.write(45);
  delay(700);
}