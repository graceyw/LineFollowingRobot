#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotorL = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorR = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotorL->setSpeed(50);
  myMotorR->setSpeed(50);
  myMotorL->run(FORWARD);
  myMotorL->run(RELEASE);
  myMotorR->run(FORWARD);
  myMotorR->run(RELEASE);
}

void loop() {
  uint8_t i;
  

  Serial.print("tock");

  myMotorL->run(FORWARD);
  myMotorR->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotorL->setSpeed(i);  
    myMotorR->setSpeed(i); 
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotorL->setSpeed(i);
    myMotorR->setSpeed(i);  
    delay(10);
  }

  delay(1000);
}
