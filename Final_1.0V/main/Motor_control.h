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
//  motorSpeed += motorAddSpeed - !motorAddSpeed;
//  if(motorSpeed==255){
//    motorAddSpeed = 0;
//  }
//  if(motorSpeed==0){
//    motorAddSpeed = 1;
//    motorDirect = !motorDirect;
//  }
  motorDirect = 0;
  digitalWrite(motorPinB, motorDirect);
  analogWrite(motorPinA, motorSpeed);
}
