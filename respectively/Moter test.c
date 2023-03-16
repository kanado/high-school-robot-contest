#include <Wire.h>


void Motor(byte one, byte two, byte three, byte four, byte five, byte six) {
  /*if (one < 0) {                //oneが負ならば…
    one = (abs(one) | 0b10000000) & 0b11111111;//oneの絶対値 OR (0b 1000 0000)
    }
    if (two < 0) {
    two = (abs(two) | 0b100000000) & 0b11111111;
    }
    if (three < 0) {
    three = (abs(three) | 0b100000000) & 0b11111111;
    }
    if (four < 0) {
    two = (abs(four) | 0b100000000) & 0b11111111;
    }
    if (five < 0) {
    two = (abs(five) | 0b100000000) & 0b11111111;
    }
    if (six < 0) {
    six = (abs(six) | 0b100000000) & 0b11111111;
    }*/
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
  /*Motor(0, 0x9E, 0x9E, 0x9E, 0x9E, 0); //後ろ
    delay(1000);
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
    Motor(0, 0x1E, 0x1E, 0x1E, 0x1E, 0); //前
    delay(1000);
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
    Motor(0, 0x32, 0xB2, 0xB2, 0x32, 0); //左
    delay(1000);
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
    Motor(0, 0xB2, 0x32, 0x32, 0xB2, 0); //右q
    delay(1000);
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
    Motor(0, 0x64, 0xE4, 0x64, 0xE4, 0);
    delay(1000);
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
    Motor(0, 0xE4, 0x64, 0xE4, 0x64, 0);
    delay(1000);
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
  */
//  Motor(0, 0x64, 0x64, 0xE4, 0xE4, 0);//後ろ
//  delay(1000);
//  Motor(0, 0xE4, 0xE4, 0x64, 0x64, 0);//前
//  delay(1000);
//  Motor(0, 0x64, 0xE4, 0xE4, 0x64, 0);//左
//  delay(1000);
  Motor(0, 0xE4, 0x64, 0x64, 0xE4, 0);//右
  delay(1000);

  //Motor(1番,2番,3番,4番,5番,6番); の順番
}
