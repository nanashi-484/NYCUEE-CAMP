//將所有servo 重置至0度，並在任意按鈕按下時開始旋轉

#include "Button_read.h"
#include "Servo_control_0.h" 

void setup(){
  Serial.begin(9600);
  setupServo();
  setupButton();
}

void loop(){
  ReadButton();
  updateServo();
  delay(50);
}
