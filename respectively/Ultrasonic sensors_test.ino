#define pingpinA  12
#define pingpinB 11
int cm;
int cm1;



void setup() {
  Serial.begin(9600);
}

void loop() {
  cm = PingPin(pingpinA);
  //Serial.print("cm=");
  Serial.println(cm);
  //cm1 = PingPin(pingpinB);
  //Serial.print("cm1=");
  //Serial.println(cm1);
  //delay(10);
}
//28  -64-131

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
  if (!kekka == 0 && kekka > 3) {
    kyori = kekka;
  }
  return kyori ;
}
