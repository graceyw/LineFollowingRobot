#include <Wire.h>
#include <Adafruit_MotorShield.h>

float minTurn = 5;           //min rate at which to turn
float turnRate = 5;         //variable for current turn rate
float turnAcc = 3;        //acceleration while turning (the more time spent turning, the faster the turn)
float lowestSpeed = 20;   //minimum speed
float maxSpeed = 25;     //maximum speed
float forwardSpeed = 20;//variable for current speed
float speedAcc = .03;  //acceleration while not turning
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
    if(forwardSpeed > lowestSpeed) forwardSpeed -= 5 * speedAcc;//decrement speed by acceleration
    turnRate += turnAcc;//increment turn rate
    
    myMotorR->setSpeed(forwardSpeed + turnRate/3);
    if(turnRate>forwardSpeed){
      myMotorL->setSpeed(0);
      sendData(0,forwardSpeed + turnRate/3);
    }else{
      myMotorL->setSpeed(forwardSpeed - turnRate);
      sendData(forwardSpeed - turnRate,forwardSpeed + turnRate/3);
    }
                             //print data to Serial moniter for later use in Python
  }
  myMotorL->setSpeed(forwardSpeed);//reset speed
  myMotorR->setSpeed(forwardSpeed);
  turnRate = minTurn; //reset turn rate

  while(checkRight()){
    if(forwardSpeed > lowestSpeed) forwardSpeed -= speedAcc;
    turnRate += turnAcc;
    myMotorL->setSpeed(forwardSpeed + turnRate/3);
    if(turnRate>forwardSpeed){
      myMotorR->setSpeed(0);
      sendData(forwardSpeed + turnRate/3,0);
    }else{
      myMotorR->setSpeed(forwardSpeed - turnRate);
      sendData(forwardSpeed + turnRate/3,forwardSpeed - turnRate);
    }                       //print data to Serial moniter for later use in Python
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

