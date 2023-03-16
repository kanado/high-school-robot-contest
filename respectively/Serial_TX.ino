int n = 100;
byte  b[2];

void setup() {
  Serial.begin(19200);
}

void loop() {
  b[0] = byte(n);
  b[1] = byte(n >> 8);

  Serial.write(b, 2);

  n--;

  delay(100);
}
