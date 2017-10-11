#include <Wire.h>
#include <Adafruit_MotorShield.h>

float minTurn = 8;           //min rate at which to turn
float turnRate = 8;         //variable for current turn rate
float turnAcc = .5;        //acceleration while turning (the more time spent turning, the faster the turn)
float lowestSpeed = 10;   //minimum speed
float maxSpeed = 50;     //maximum speed
float forwardSpeed = 10;//variable for current speed
float speedAcc = .01;  //acceleration while not turning
int leftThres = 600;  //threshold to detect line
int rightThres = 600;
int rightSensor = 1000; //variable for right sensor value
int leftSensor = 1000; //variable for left sensor value
Adafruit_MotorShield AFMS = Adafruit_MotorShield();  
  // Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotorL = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorR = AFMS.getMotor(2);
void setup() {
  AFMS.begin();
  Serial.begin(9600);
  Serial.println("test");
  // You can also make another motor on port M2
  //Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
  myMotorL->setSpeed(10);
  myMotorR->setSpeed(10);
  myMotorL->run(FORWARD);
  myMotorR->run(FORWARD);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendData(forwardSpeed, forwardSpeed);                               //print data to Serial moniter for later use in Python
  myMotorL->run(FORWARD);
  myMotorR->run(FORWARD);
  if (forwardSpeed < maxSpeed)forwardSpeed += speedAcc; //increment speed by the acceleration
  
  turnRate = minTurn;//reset turn rate
  
  while(checkLeft()){
    if(forwardSpeed > lowestSpeed) forwardSpeed -= speedAcc;//decrement speed by acceleration
    turnRate += turnAcc;//increment turn rate
    myMotorR->setSpeed(turnRate);
    myMotorL->setSpeed(0);
    sendData(0,turnRate);                         //print data to Serial moniter for later use in Python
  }
  myMotorL->setSpeed(forwardSpeed);//reset speed
  myMotorR->setSpeed(forwardSpeed);
  turnRate = minTurn; //reset turn rate

  while(checkRight()){
    if(forwardSpeed > lowestSpeed) forwardSpeed -= speedAcc;
    turnRate += turnAcc;
    myMotorL->setSpeed(turnRate);
    myMotorR->setSpeed(0);
    sendData(turnRate,0);                         //print data to Serial moniter for later use in Python
  }
  myMotorL->setSpeed(forwardSpeed);
  myMotorR->setSpeed(forwardSpeed);
  
}

bool checkLeft(){
  leftSensor = analogRead(A1);
  return leftSensor > leftThres;
}

bool checkRight(){
  rightSensor = analogRead(A0);
  return rightSensor > rightThres;
}

void sendData(float leftVal,float rightVal) {
  Serial.print('<');
  Serial.print(leftVal);
  Serial.print(',');
  Serial.print(analogRead(A1));
  Serial.print(',');
  Serial.print(rightVal);
  Serial.print(',');
  Serial.print(analogRead(A0));
  
  Serial.println();
}

