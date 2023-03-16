byte b[2];
int X, Y;


void setup() {
  //Serial2.begin(19200);
  Serial1.begin(115200);
  Serial.begin(115200);
  pinMode(2,OUTPUT);
}

void loop() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  if (Serial1.available() >= 2) {
    for (int i = 0; i < 2 && Serial1.available() > 0; i++) {
      b[i] = Serial1.read();
    }
    X = b[1] << 8 | b[0];
    }
  
  /*
  if (Serial2.available() >= 2) {
    for (int i = 0; i < 2 && Serial2.available() > 0; i++) {
      b[i] = Serial2.read();
    }
    Y = b[1] << 8 | b[0];
  }
  */
  Serial.println(X);
  //Serial.println(Y);
  //  Serial.print(b[1],DEC);
  //  Serial.print("\t");
  //  Serial.print(b[0],DEC);
  //  Serial.print("\t");
  //  Serial.print(Serial2.available());
  //  Serial.print("\n");
}
