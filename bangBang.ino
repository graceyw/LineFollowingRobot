void setup() {
  // put your setup code here, to run once:
  #include <Servo.h>
  Servo rightWheel;        //create servo object to control right wheel
  Servo leftWheel;         //create servo object to control left wheel
  int rightSensor = analogRead(A0);
  int leftSensor = analogRead(A1);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
//  Serial.print(', ');
  Serial.println(analogRead(A1));
}

