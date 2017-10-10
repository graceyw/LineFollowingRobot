void setup() {
  // put your setup code here, to run once:
  int sensor1 = analogRead(A0);
  int sensor2 = analogRead(A1);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
//  Serial.print(', ');
  Serial.println(analogRead(A1));
}
