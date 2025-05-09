#include "Global_define.h"
#include <Servo.h>

// 宣告伺服馬達
Servo myServo[4];

// 伺服馬達初始設定
void setupServo(){
  servoSpeed = 1;
  for(int i=0;i<4;i++){
    myServo[i].attach(servoPins[i]);
    servoAngle[i] = 0;
  }
}

// 計算伺服馬達角度（可變更）
void calculateServo(){
  for(int i=0;i<4;i++)
    servoAngle[i] += servoSpeed;
  if(servoAngle == 90 || servoAngle == 0)
    servoSpeed = -servoSpeed;
}

// 更新伺服馬達
void updateServo(){
  for(int i=0;i<4;i++){
    myServo[i].write(servoAngle[i]);
  }
}
