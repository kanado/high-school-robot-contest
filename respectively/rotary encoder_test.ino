boolean old_a, old_b;
boolean now_a, now_b;

byte old_stat, now_stat;

int counter = 0;

float pos;
int seen;

byte b[2];

// 送信する時のif文で使用、millis()が変わらない間に複数回通るのを防ぐ
// 一回通ったタイミングのミリ秒を覚えておいて、変わるまで動かないようにする
unsigned long old_millis = -1;

void setup() {
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  Serial.begin(19200);

  old_a = digitalRead(10);
  old_b = digitalRead(11);

  if (old_a == 1 && old_b == 0) {
    old_stat = 0;
  } else if (old_a == 1 && old_b == 0) {
    old_stat = 1;
  } else if (old_a == 1 && old_b == 1) {
    old_stat = 2;
  } else if (old_a == 0 && old_b == 1) {
    old_stat = 3;
  }
}

void loop() {
  if (digitalRead(7) == HIGH) {
    counter = 0;
  }
  now_a = digitalRead(10);
  now_b = digitalRead(11);

  if (old_a != now_a || old_b != now_b) {
    if (now_a == 0 && now_b == 0) {
      now_stat = 0;
    } else if (now_a == 1 && now_b == 0) {
      now_stat = 1;
    } else if (now_a == 1 && now_b == 1) {
      now_stat = 2;
    } else if (now_a == 0 && now_b == 1) {
      now_stat = 3;
    }
  }
  if ((old_stat == 0 && now_stat == 1) || (old_stat == 1 && now_stat == 2) || (old_stat == 2 && now_stat == 3) || (old_stat == 3 && now_stat == 0)) {
    counter++;
  } else if ((old_stat == 0 && now_stat == 3) || (old_stat == 3 && now_stat == 2) || (old_stat == 2 && now_stat == 1) || (old_stat == 1 && now_stat == 0)) {
    counter--;
  }

  old_a = now_a;
  old_b = now_b;
  old_stat = now_stat;
  pos = (60.0 * 3.14 / 360.0) * (counter / 4);
  seen  = int(pos);
  b[0] = byte(seen);
  b[1] = byte(seen >> 8);

  if (millis() % 10 == 0 && millis() != old_millis) {
    old_millis = millis();
    //            Serial.print("stat:");
    //            Serial.print(now_stat);
    //            Serial.print(",counter:");
    //            Serial.print(counter);
    //            Serial.print(",A:");
    //            Serial.print(now_a);
    //            Serial.print(",B:");
    //            Serial.print(now_b);
    //            Serial.print(",seen:");
    //            Serial.println(pos);
    //Serial.write(buf[0]);
    Serial.write(b, 2);
  }
}
