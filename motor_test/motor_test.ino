// 控制馬達開關的測試程式
#include "Button_read.h"
#include "Motor_control_0.h" 

void setup(){
  Serial.begin(9600);
  setupMotor();
  setupButton();
}

void loop(){
  ReadButton();
  updateMotor();
  delay(50);
}
