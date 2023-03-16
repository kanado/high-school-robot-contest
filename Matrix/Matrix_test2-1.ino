#include <Wire.h>
#include <SPI.h>
#include <Pixy.h>

/////////////////////////////////
#define pingpinA 12
#define pingpinB 11
int cm;
int cm1;
/////////////////////////////////////

///////////////////////////////////////
unsigned long t;
int kekka;
int kyori;
///////////////////////////////////////

/////////////////////////////////////
int pattern = 173;
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

////////////////////\////////////////////////
int blocks = 0;
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

////////////////////////////////////////////

Pixy pixy;


void setup() {
  pixy.init();
  Serial.begin(9600);
  Serial.print("Starting...\n");
  pinMode(5, OUTPUT);
}

void loop() {
  switch (pattern) {
    case 173:
      digitalWrite(5, HIGH);
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


    case 175:
      for (i = 0; i < blocks; i++) {
        data_blocks_x[i] = pixy.blocks[i].x;
        data_blocks_y[i] = pixy.blocks[i].y;
        Serial.println(data_blocks_x[i]);
      }
      pattern = 176;
      break;

    case 176:
      for (i = 0; i < blocks + 1; i++) {
        if (i == 0) {
          E =  data_blocks_y[0];
        } else {
          F  =  data_blocks_y[i];
          if (E < F) {
            E = F;
          } else if (E > F) {
            E = E;
          } else if (E == F) {
            data_kaburi_number = i;
            data_kaburi_y = E;
            kaburi = 1;
            E = E;
          }
        }
      }
      Serial.println(E);
      pattern = 177;
      break;

    case 177:
      for (i = 0; discover == 1; i++) {
        if (E == data_blocks_y[i]) {
          data_great_y_number = i;
          discover = 1;
        }
      }
      pattern = 178;
      break;

    case 178:
      data_great_x = data_blocks_x[data_great_y_number];
      pattern = 189;
      break;

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
      blocks = pixy.getBlocks();
      data_great_x = pixy.blocks[0].x;
      Serial.println(data_great_x);
      Serial.println("中心移動中");
      if (center_x_min < data_great_x && data_great_x < center_x_max) {
        Serial.println("中心です");
        pattern = 193;
      } else {
        pattern = 190;
      }
      break;

    case 193:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 194;
      delay(10);
      break;

    case 194:
      digitalWrite(5, HIGH);
      delay(10);
      pattern = 195;
      break;

    case 195:
      Motor(0, 0x32, 0x32, 0x32, 0x32, 0); //前
      pattern = 196;
      delay(1000);
      break;

    case 196:
      Motor(0, 0, 0, 0, 0, 0);
      pattern = 197;
      delay(10);
      break;

    case 197:
      digitalWrite(5, LOW);
      delay(10);
      pattern = 198;
      delay(100);
      break;
    case 198:
      Motor(0, 0xB2, 0xB2, 0xB2, 0xB2, 0); //後ろ
      pattern = 199;
      delay(700);
      break;
    case 199:
      Motor(0, 0, 0, 0, 0, 0);
      delay(10);
      pattern = 200;
      break;
    case 200:
      Motor(0, 0x32, 0xB2, 0xB2, 0x32, 0); //左
      delay(2500);
      pattern = 201;
      break;
    case 201:
      Motor(0, 0, 0, 0, 0, 0);
      delay(10);
      pattern = 202;
      break;
    case 202:
      Motor(0, 0x32, 0x32, 0x32, 0x32, 0); //前
      delay(4500);
      pattern = 203;
      break;
      case 203:
      Motor(0,0,0,0,0,0);
      delay(10);
      pattern = 204;
      break;
      case 204:
      digitalWrite(5,HIGH);
      delay(10);
      pattern = 205;
      break;
  }
}


void Motor(byte one, byte two, byte three, byte four, byte five, byte six) {         //Motorに対しての出力割合を16進数で送信する（通信が成立したかをreturnで返す）
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
