int LED_kazu = 4;
int LED_pin_firest = 2;

int C = 0;

int i;


void setup() {
  // put your setup code here, to run once:
  while (C < LED_kazu + LED_pin_firest ) {
    pinMode(LED_pin_firest, OUTPUT);
    digitalWrite(LED_pin_firest, LOW);
    LED_pin_firest = LED_pin_firest + 1;
    C = C + 1;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (i = 0; i < C; i++) {
    LED_Number(i);
    delay(1000);
  }
}

void LED_Number(int number) {        //LEDを使用して２進数で１０進数を示す（case番号を可視化する為に用いる）
  switch (number) {
    case 1:
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      number = 0;
      break;

    case 2:
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      number = 0;
      break;
    case 3:
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      number = 0;
      break;
    case 4:
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      number = 0;
      break;

    case 5:
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      number = 0;
      break;

    case 6:
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      number = 0;
      break;

    case 7:
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      number = 0;
      break;

    case 8:
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      number = 0;
      break;

    case 9:
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      number = 0;
      break;

    case 10:
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      number = 0;
      break;
  }
}
