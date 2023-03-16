#include <Wire.h>
uint8_t b[2];
int numu = 0;
int X, Y;

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

void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
  Serial2.begin(19200);

}
/*

  0X40 40
  0XC0 -40

  0011,0010 50
  0x32

  1011,0010 -50
  0xB2

  1010,0011 -35
  A3

  0010,0011 35
  23

  0001,1110 30
  1E

  1001,1110 -30
  9E


*/


void loop() {
  switch (numu)
  {
    case 0:
      Motor(0, 0, 0, 0, 0, 0);
      numu = 1;
      delay(10);
      break;
    case 1:
      Motor(0, 0xE4, 0xE4, 0xE4, 0xE4, 0);//右
      numu = 2;
      delay(10);
      break;
    case 2:
      if (Serial1.available() >= 2) {
        for (int i = 0; i < 2 && Serial1.available() > 0; i++) {
          b[i] = Serial1.read();
        }
        X = b[1] << 8 | b[0];
      }
      if (X >= 700) {
        numu = 3;
      }
      break;

    case 3:
      Motor(0, 0, 0, 0, 0, 0);
      numu = 30;
      delay(10);
      break;

    case 30:
      Motor(0, 0x64, 0x64, 0x64, 0x64, 0);//左
      numu = 31;
      delay(10);
      break;
    case 31:
      if (Serial1.available() >= 2) {
        for (int i = 0; i < 2 && Serial1.available() > 0; i++) {
          b[i] = Serial1.read();
        }
        X = b[1] << 8 | b[0];
      }
      if (X < 2) {
        numu = 32;
      }
      break;

    case 32:
      Motor(0, 0, 0, 0, 0, 0);
      numu = 255;
      delay(10);
      break;

    //    case 4:
    //      Motor(0, 0xE4, 0xE4, 0x64, 0x64, 0);//前
    //      numu = 5;
    //      break;
    //
    //    case 5:
    //      if (Serial2.available() >= 2) {
    //        for (int i = 0; i < 2 && Serial2.available() > 0; i++) {
    //          b[i] = Serial2.read();
    //        }
    //        Y = b[1] << 8 | b[0];
    //      }
    //      if (Y >= 300) {
    //        numu = 6;
    //      }
    //      break;
    //
    //    case 6:
    //      Motor(0, 0, 0, 0, 0, 0);
    //      numu = 7;
    //      delay(10);
    //      break;
    //
    //    case 7:
    //      Motor(0, 0x64, 0x64, 0xE4, 0xE4, 0);//後ろ
    //      numu = 8;
    //      break;
    //
    //    case 8:
    //      if (Serial2.available() >= 2) {
    //        for (int i = 0; i < 2 && Serial2.available() > 0; i++) {
    //          b[i] = Serial2.read();
    //        }
    //        Y = b[1] << 8 | b[0];
    //      }
    //      if (Y == 100) {
    //        numu = 9;
    //      }
    //      break;
    //
    //    case 9:
    //      Motor(0, 0, 0, 0, 0, 0);
    //      numu = 255;
    //      delay(10);
    //      break;

    case 255:
      Motor(0, 0, 0, 0, 0, 0);
      break;
  }
  /*
    Motor(0, 0x64, 0x64, 0xE4, 0xE4, 0);//後ろ
    delay(1000);
    Motor(0, 0xE4, 0xE4, 0x64, 0x64, 0);//前
    delay(1000);
    Motor(0, 0x64, 0x64, 0x64, 0x64, 0);//左
    delay(1000);
    Motor(0, 0xE4, 0xE4, 0xE4, 0xE4, 0);//右
    delay(1000);
    Motor(0, 0, 0, 0, 0, 0);
  */
  //Motor(1番,2番,3番,4番,5番,6番); の順番
}
