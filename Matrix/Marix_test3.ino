#include <Wire.h>
#include <SPI.h>
#include <Pixy.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <EEPROM.h>

/////////////////////////////////
#define pingpinA 12
#define pingpinB 11
int cm;
int cm1;
/////////////////////////////////////

///////////////////////////////////////
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
///////////////////////////////////////


///////////////////////////////////////
unsigned long t;
int kekka;
int kyori;
///////////////////////////////////////

/////////////////////////////////////
int pattern = 0;
////////////////////////////////////

////////////////////////////////////////////
//A--Zは適当な物に使う（使用している所を明記すること）
int A = 0;//loop内case2で使用
int B = 0;//loop内case5で使用
int C = 0;//setup内whileで使用
int D =  0; //loop内case7で使用
int E = 0;//loop内case175で使用
int F = 0;//loop内case175で使用
int i = 0;//loop内case174で使用
//////////////////////////////////////////

////////////////////////////////////////////
int LED_kazu = 4;
int LED_pin_firest = 2;
///////////////////////////////////////////,

/////////////////////////////////////////////
unsigned long time_data = 0;
unsigned long time_gendo = 120000;
/////////////////////////////////////////////

////////////////////////////////////////////
uint16_t blocks;
int data_blocks_x[30];
int data_blocks_y[30];
int data_gap_y[30];
int data_kaburi_number;
int kaburi = 0;
int data_kaburi_y;
int discover = 0;
int data_great_y_number;
int pea_count = 0;
int data_great_x = 0;
int data_great_y = 0;
int center_x = 159;
int center_x_min = 155;
int center_x_max = 163;
int left_or_right = 0;
////////////////////////////////////////////

////////////////////////////////////////////
int kakudo;
int kakudo_ookii = 2;
int kakudo_tisai = 358;


uint8_t buf[2];
////////////////////////////////////////////

////////////////////////////////////////////
int data_sukima[8] = {27, 73, 120, 172};
int data_sukima_count = 0;
////////////////////////////////////////////

////////////////////////////////////////////
int aitemu_pos[7] = {40, 48, 53, 95, 95, 96};
int aitemu_pos_count = 0;
////////////////////////////////////////////

////////////////////////////////////////////
uint8_t b[2];
int X, Y;
////////////////////////////////////////////

Pixy pixy;

int evaluation;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pixy.init();
}

/*
  A:0~172(初期化) B:173~191（メイン） C:172~255（帰宅）
*/

void loop() {
  /* if (pattern >= 173) {     //初期化終了後のcase番号を入れる（７は仮数）
     time_data = millis();
     if (time_data >= time_gendo) {
       pattern == 8;     //アイテム回収case番号以降の帰宅case番号を入れること（8は仮数）
     }
    }*/
  switch (pattern) {
    case 0:
      Motor(0, 0, 0, 0, 0, 0);
      digitalWrite(5, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      pattern = 1;
      break;
    case 1:     //横移動
      Motor(0, 0xE4, 0xE4, 0xE4, 0xE4, 0);
      //Serial.println("横移動：");   //通信成功は失敗かをSerialに出力すると共にモータの指示を出す
      pattern = 2;
      delay(10);
      break;

    case 2:     //距離測定
      if (digitalRead(7) == LOW) {
        digitalWrite(2, HIGH);
        digitalWrite(13,HIGH);
        delay(10);
        digitalWrite(2, LOW);
        digitalWrite(13, LOW);
        delay(100);
        pattern = 3;
      } 
      delay(10);
      break;

    case 3:     //stop
      //Serial.print("停止:");
      Motor(0, 0, 0, 0, 0, 0/*停止*/);
      pattern = 4;
      delay(10);
      break;

    case 4:
      Motor(0, 0x64, 0x64, 0x64, 0x64, 0);
      pattern = 5;
      delay(10);
      break;

    case 5:
      if (Serial1.available() >= 2) {
        for (int w = 0; w < 2 && Serial1.available() > 0; w++) {
          b[w] = Serial1.read();
        }
        X = b[1] << 8 | b[0];
      }
      if (X > 0 && X >= 100) {
        pattern = 6;
      }
      break;

    case 6:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 7;
      delay(10);
      break;

    case 7:     //後ろ移動
      //Serial.print("後進：");
      Motor(0, 0x64, 0x64, 0xE4, 0xE4, 0);
      pattern = 8;
      break;

    case 8:     //スイッチの検知
      if (digitalRead(8) == LOW) {//マイクロスイッチの状況を読み取り判別する
        digitalWrite(3, HIGH);
        delay(100);
        digitalWrite(3, LOW);
        pattern = 9;
      }
      //Serial.println("case5");
      break;

    case 9:     //stop(初期化終了)
      //Serial.print("停止:");
      Motor(0, 0, 0, 0, 0, 0)/*停止*/;
      pattern = 10;
      delay(10);
      break;

    case 10:
      Motor(0, 0xE4, 0xE4, 0x64, 0x64, 0);//前
      pattern = 11;
      delay(10);
      break;

    case 11:
      if (Serial2.available() >= 2) {
        for (int i = 0; i < 2 && Serial2.available() > 0; i++) {
          b[i] = Serial2.read();
        }
        Y = b[1] << 8 | b[0];
      }
      if (Y >= 50) {
        pattern = 12;
      }
      break;

    case 12:     //(初期化終了)
      Motor(0, 0, 0, 0, 0, 0)/*停止*/;
      pattern = 255;
      delay(100);
      break;

    case 30:
      Serial.println("横移動する");
      cm = PingPin(pingpinA);     //超音波センサーから値を取得する
      if (aitemu_pos[aitemu_pos_count] >= cm) {
        Motor(0, 0x64, 0xE4, 0xE4, 0x64, 0); //左
        Serial.println("左");
        pattern = 31;
      } else if (aitemu_pos[aitemu_pos_count] <= cm) {
        Motor(0, 0xE4, 0x64, 0x64, 0xE4, 0); //右
        Serial.println("右");
        pattern = 32;
      }
      break;

    case 31:
      if (aitemu_pos[aitemu_pos_count] <= cm) {
        Serial.println("移動完了");
        pattern = 33;
      } else {
        pattern = 30;
      }
      break;


    case 32:
      if (aitemu_pos[aitemu_pos_count] >= cm) {
        Serial.println("移動完了");
        pattern = 33;
      } else {
        pattern = 30;
      }
      break;

    case 33:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 160;
      delay(10);
      break;


    case 160:
      if (Serial1.available() > 0) {
        Serial1.readBytes(buf, 2);
        uint16_t value16bit = buf[1] << 8 | buf[0];
        //Serial.println(String(value16bit, DEC));
        kakudo = value16bit;
        Serial.println(kakudo);
        if (kakudo_ookii <= kakudo && kakudo < 180) {
          Serial.println("右");
          Motor(0, 0x1E, 0x9E, 0x1E, 0x9E, 0);
        } else if (kakudo_tisai >= kakudo && kakudo > 180) {
          Serial.println("左");
          Motor(0, 0x9E, 0x1E, 0x9E, 0x1E, 0);
        } else if (kakudo_ookii > kakudo || kakudo_tisai < kakudo) {
          Serial.println("else");
          Motor(0, 0, 0, 0, 0, 0);
          pattern = 173;
        }
        delay(10);
      }
      break;


    case 173:
      blocks = pixy.getBlocks();
      if (blocks != 0) {
        pattern = 174;
      }
      Serial.print("Detected:");
      Serial.println(blocks);
      break;

    case 174:
      if (blocks == 1) {
        pattern = 180; //未確定
        Serial.println("一つを検知");
      } else {
        pattern = 175;
        Serial.println("二つ以上");
      }
      break;

    //
    //case 175:
    //  for (i = 0; i < blocks; i++) {
    //    data_blocks_x[i] = pixy.blocks[i].x;
    //    data_blocks_y[i] = pixy.blocks[i].y;
    //    Serial.println(data_blocks_x[i]);
    //  }
    //  pattern = 176;
    //  break;
    //
    //case 176:
    //  for (i = 0; i < blocks + 1; i++) {
    //    if (i == 0) {
    //      E =  data_blocks_y[0];
    //    } else {
    //      F  =  data_blocks_y[i];
    //      if (E < F) {
    //        E = F;
    //      } else if (E > F) {
    //        E = E;
    //      } else if (E == F) {
    //        data_kaburi_number = i;
    //        data_kaburi_y = E;
    //        kaburi = 1;
    //        E = E;
    //      }
    //    }
    //  }
    //  Serial.println(E);
    //  pattern = 177;
    //  break;
    //
    //case 177:
    //  for (i = 0; discover == 1; i++) {
    //    if (E == data_blocks_y[i]) {
    //      data_great_y_number = i;
    //      discover = 1;
    //    }
    //  }
    //  pattern = 178;
    //  break;
    //
    //case 178:
    //  data_great_x = data_blocks_x[data_great_y_number];
    //  pattern = 189;
    //  break;

    case 180:
      data_great_x = pixy.blocks[0].x;
      data_great_y = pixy.blocks[0].y;
      Serial.print(i + 1);
      Serial.println("個の座標");
      Serial.println(data_great_x);
      Serial.println(data_great_y);
      pattern = 189;
      break;


    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    case 189:
      Serial.println("モーター初期化");
      Motor(0, 0, 0, 0, 0, 0);
      delay(10);
      pattern = 190;
      break;

    case  190:      //左：１,右：２,センター:3
      if (data_great_x < center_x) {      //中央より左
        Motor(0, 0xA3, 0x23, 0x23, 0xA3, 0); //右
        delay(100);
        Serial.println("右移動");
      } else if (data_great_x > center_x) {     //中央より右
        Motor(0, 0x23, 0xA3, 0xA3, 0x23, 0); //左
        delay(100);
        Serial.println("左移動");
      } else if (data_great_x == center_x) {      //真ん中
        Motor(0, 0, 0, 0, 0, 0);
        Serial.println("真ん中");
      }
      pattern = 191;
      break;

    case 191:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 192;
      delay(10);
      break;

    case 192:
      blocks = 0;
      blocks = pixy.getBlocks();
      if (blocks == 0) {
        pattern = 173;
      } else {
        data_great_x = pixy.blocks[0].x;
        Serial.println(data_great_x);
        Serial.println("中心移動中");
        if (center_x_min < data_great_x && data_great_x < center_x_max) {
          Serial.println("中心です");
          pattern = 193;
        } else {
          pattern = 190;
        }
      }
      break;

    case 193:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 199;
      delay(10);
      break;

    case 199:
      //digitalWrite(5, HIGH);
      delay(10);
      pattern = 200;
      break;

    case 200:
      Motor(0, 0x32, 0x32, 0x32, 0x32, 0); //前
      pattern = 201;
      delay(1000);
      break;

    case 201:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 202;
      delay(10);
      break;

    case 202:
      digitalWrite(5, LOW);
      Serial.println("掴んだ");
      pattern = 213;
      delay(500);
      break;

    case 213:
      Motor(0, 0xB2, 0xB2, 0xB2, 0xB2, 0);
      Serial.println("バックする");
      pattern = 214;
      break;


    case 214:
      if (digitalRead(8) == LOW) {
        pattern = 215;
      }
      break;
    case 215:
      Motor(0, 0, 0, 0, 0, 0);
      Serial.println("下がり終わった");
      pattern = 216;
      delay(10);
      break;

    case 216:
      Motor(0, 0x1E, 0x1E, 0x1E, 0x1E, 0); //前
      delay(500);
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 217;
      delay(100);
      break;

    case 217:
      Serial.println("横移動する");
      cm = PingPin(pingpinA);     //超音波センサーから値を取得する
      if (data_sukima[data_sukima_count] >= cm) {
        Motor(0, 0x32, 0xB2, 0xB2, 0x32, 0); //左
        Serial.println("左");
        pattern = 218;
      } else if (data_sukima[data_sukima_count] <= cm) {
        Motor(0, 0xB2, 0x32, 0x32, 0xB2, 0); //右
        Serial.println("右");
        pattern = 219;
      }
      break;

    case 218:
      if (data_sukima[data_sukima_count] <= cm) {
        Serial.println("移動完了");
        pattern = 222;
      } else {
        pattern = 217;
      }
      break;


    case 219:
      if (data_sukima[data_sukima_count] >= cm) {
        Serial.println("移動完了");
        pattern = 222;
      } else {
        pattern = 217;
      }
      break;

    case 222:
      Motor(0, 0, 0, 0, 0, 0);
      delay(10);
      pattern = 223;
      break;
    case 223:
      if (Serial1.available() > 0) {
        Serial1.readBytes(buf, 2);
        uint16_t value16bit = buf[1] << 8 | buf[0];
        //Serial.println(String(value16bit, DEC));
        kakudo = value16bit;
        Serial.println(kakudo);
        if (kakudo_ookii <= kakudo && kakudo < 180) {
          Serial.println("右");
          Motor(0, 0x1E, 0x9E, 0x1E, 0x9E, 0);
        } else if (kakudo_tisai >= kakudo && kakudo > 180) {
          Serial.println("左");
          Motor(0, 0x9E, 0x1E, 0x9E, 0x1E, 0);
        } else if (kakudo_ookii > kakudo || kakudo_tisai < kakudo) {
          Serial.println("else");
          Motor(0, 0, 0, 0, 0, 0);
          pattern = 224;
        }
        delay(10);
      }



    case 224:
      Motor(0, 0x32, 0x32, 0x32, 0x32, 0); //前
      Serial.println("前進");
      pattern = 225;
      break;

    case 225:
      cm1 = PingPin(pingpinB);     //超音波センサーから値を取得する
      if (cm1 >= 58) {
        pattern = 226;
      }
      break;
    case 226:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 227;
      delay(10);
      break;

    case 227:
      digitalWrite(5, HIGH);
      delay(100);
      pattern = 230;
      break;

    case 230:
      Motor(0, 0xE4, 0xE4, 0xE4, 0xE4, 0); //後ろ
      pattern = 231;
      break;

    case 231:
      if (digitalRead(8) == LOW) {
        pattern = 232;
      }
      break;

    case 232:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 233;
      delay(10);
      break;

    case 233:
      Motor(0, 0x64, 0x64, 0x64, 0x64, 0); //前
      delay(300);
      Motor(0, 0, 0, 0, 0, 0);
      delay(10);
      pattern = 234;
      break;

    case 234:
      data_sukima_count++;
      aitemu_pos_count++;
      pattern = 30;
      delay(100);
      break;

    case 255:     //初期化終了後の初動作
      Serial.println("終了");
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      //digitalWrite(5, HIGH);
      delay(500);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      //digitalWrite(5, LOW);
      delay(500);
      break;
  }
}




void Motor(byte one, byte two, byte three, byte four, byte five, byte six) {         //Motorに対しての出力割合を16進数で送信する（通信が成立したかをreturnで返す）
  if (one < 0) {                //oneが負ならば…
    one = (abs(one) || 0b10000000) & 0b11111111;//oneの絶対値 OR (0b 1000 0000)
  }
  if (two < 0) {
    two = (abs(two) || 0b100000000) & 0b11111111;
  }
  if (three < 0) {
    three = (abs(three) || 0b100000000) & 0b11111111;
  }
  if (four < 0) {
    two = (abs(four) || 0b100000000) & 0b11111111;
  }
  if (five < 0) {
    two = (abs(five) || 0b100000000) & 0b11111111;
  }
  if (six < 0) {
    six = (abs(six) || 0b100000000) & 0b11111111;
  }
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

int PingPin(int pin) {          //超音波センサーの値を指定されたpinに接続されたセンサーから取得し、returnで距離(cm)で返す
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
