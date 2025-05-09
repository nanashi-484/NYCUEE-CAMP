// 主程式

#include "OLED_control.h"
#include "Servo_control.h"
#include "Button_read.h"
#include "Photo_read.h"
#include "Motor_control.h"

void setup()
{
  Serial.begin(9600);
  setupOLED();
  delay(1000);
  setupMotor();
  setupPhoto();
  setupServo();
  setupButton();

  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);

  ReadButton();
  ReadPhoto();
  updateMotor();
  updateServo();
  updateOLED();
  //  delay(25);
}
