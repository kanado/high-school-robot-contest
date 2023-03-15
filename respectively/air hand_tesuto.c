void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  //HIGH->open,LOW->close
  digitalWrite(5,LOW);
  delay(500);
  digitalWrite(5,HIGH);
  delay(500);

}
