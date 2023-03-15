#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 myIMU = Adafruit_BNO055();

int kakudo;
byte b[2];

void setup() {
  Serial.begin(115200);
  myIMU.begin();
  delay(1000); 
}

void loop() {
  imu::Vector<3> head = myIMU.getVector(Adafruit_BNO055::VECTOR_EULER);
  //Serial.println(head.x());
  kakudo = (int)head.x();
  //Serial.println(kakudo);
  b[0] = byte(kakudo);
  b[1] = byte(kakudo >> 8);
  Serial.write(b, 2);
}
