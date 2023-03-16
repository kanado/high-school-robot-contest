#include <Wire.h>

#define pingpinA 12
#define pingpinB 11
int cm;
int cm1;

int syori1 = 0;
int syori2 = 0;
int podition = 0;
int kaisu = 0;
int i = 0;
int A = 0;

void Motor(char one, char two, char three, char four, char five, char six) {
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

/*
  0xE4 = -100,0x64 = 100
*/

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  if (podition == 0) {
    syukko();
  } else if (podition == 1) {
    yziku_syoki();
  } else if (podition == 2) {
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
  } else {
    Motor(0, 0, 0, 0, 0, 0);
    digitalWrite(2, LOW);
  }
}

void syukko() {
  cm = PingPin(pingpinA);
  if (cm <= 10) {
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
    Serial.println("初期位置に到達しました");
    //syori1 = 1;
    podition = 1;
    loop();
  } else {
    Motor(0, 0xE4, 0x64, 90, 0xE4, 0);
    delay(10);
    Serial.println("移動中");
  }

}

void yziku_syoki() {
  if (digitalRead(8) == LOW) {
    Serial.println("Y軸の０点を終了しました。");
    Motor(0, 100, 100, 100, 100, 0);
    delay(200);
    Motor(0, 0, 0, 0, 0, 0);
    delay(10);
    //syori2 = 1;
    podition = 2;
    loop();
  } else {
    Motor(0, 0xE4, 0xE4, 0xE4, 0xE4, 0);
    delay(10);
    Serial.println("０点中");
  }
}
int PingPin(int pin) {
  unsigned long t;
  int kekka;
  int kyori;
  pinMode(pin, OUTPUT);//出力モード
  digitalWrite(pin, LOW); //LOＷ出力
  delayMicroseconds(2);
  digitalWrite(pin, HIGH); //ＨＩＧＨ出力
  delayMicroseconds(5);
  digitalWrite(pin, LOW); //ＬＯＷ出力
  pinMode(pin, INPUT); //入力モード
  t = pulseIn(pin, HIGH);
  kekka = (t / 29) / 2;
  if (!kekka < 3) {
    kyori = kekka;
  }
  return kyori ;
}
