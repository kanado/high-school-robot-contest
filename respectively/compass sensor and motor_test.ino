#include <Wire.h>

int kakudo;
int kakudo_ookii = 2;
int kakudo_tisai = 358;


uint8_t b[2];

void setup() {
  Serial.begin(115200);
  //uSerial1.begin(115200);
}

void loop() {
  if (Serial.available() >= 2) {
    for (int i = 0; i < 2 && Serial.available() > 0; i++) {
      b[i] = Serial.read();
    }
    kakudo = b[1] << 8 | b[0];
    Serial.println(kakudo);
    if (kakudo_ookii < kakudo && kakudo < 180) {
      Serial.println("右");
      Motor(0, 0x1E, 0x9E, 0x1E, 0x9E, 0);
      delay(1);
    } else if (kakudo_tisai > kakudo && kakudo > 180) {
      Serial.println("左");
      Motor(0, 0x9E, 0x1E, 0x9E, 0x1E, 0);
      delay(1);
    } else if (kakudo_ookii > kakudo || kakudo_tisai < kakudo) {
      Serial.println("else");
      Motor(0, 0, 0, 0, 0, 0);
      delay(1);
    }
  }
  delay(1);
}

void Motor(byte one, byte two, byte three, byte four, byte five, byte six) {
  Wire.beginTransmission(0x14);
  Wire.write(0x00 + one); // 1ch
  Wire.write(0x00 + two); // 2ch
  Wire.write(0x00 + three); // 3ch
  Wire.write(0x00 + four); // 4ch
  Wire.write(0x00 + five); // 5ch
  Wire.write(0x00 + six); // 6ch : 0 しかダメ
  Wire.write(0); // ダミー
  Wire.endTransmission();
  delay(2); // このディレーがないと連続稼動せずハングアップ
}
