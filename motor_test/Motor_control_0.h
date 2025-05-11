#include "Global_define.h"

// 初始化馬達狀態
void setupMotor(){
  pinMode(motorPinA , OUTPUT);
  pinMode(motorPinB , OUTPUT);
  motorSpeed = 255;
  motorDirect = 0 , motorAddSpeed = 1;
}


// 更新馬達狀態
void updateMotor(){
  for(int i = 0;i<4;i++){
    if(button_currentValue[i] == 1){
      if(motorSpeed == 0){
        motorSpeed = 255;
      }
      else{
        motorSpeed = 0;
      }
    }
  }
  motorDirect = 0;
  digitalWrite(motorPinB, motorDirect);
  analogWrite(motorPinA, motorSpeed);
}
