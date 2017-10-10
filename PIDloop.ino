#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);    //using port number i.e. M1=1, M4=4 etc.
int rightSensor = analogRead(A0);
int leftSensor = analogRead(A1);

void setup() {
  AFMS.begin();
  rightMotor->setSpeed(150);   //initialize right motor speed
  leftMotor->setSpeed(150);    //initialize left motor speed

  Serial.begin(9600);          //initialize Serial moniter
  Serial.println('Beginning program now.');
}

void loop() {
  Serial.println(rightSensor);
  Serial.println(leftSensor);            //for testing purposes
}
