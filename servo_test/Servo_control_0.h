#include "Global_define.h"
#include <Servo.h>

// 宣告伺服馬達
Servo myServo[4];

// 決定旋轉模式
bool button_Triggered = 0;

// 伺服馬達初始設定
void setupServo(){
  servoSpeed = 1;
  Angle_input = 0;
  for(int i=0;i<4;i++){
    myServo[i].attach(servoPins[i]);
    servoAngle[i] = 120;
  }
}

// 計算伺服馬達角度
void calculateServo_continus(){
    for(int i=0;i<4;i++)
      servoAngle[i] += 2 * servoSpeed;
    if(servoAngle[0] <= 0 || servoAngle[0] >= 60) //從60轉到0再轉回來，重複
      servoSpeed = -servoSpeed;
    Serial.println(servoAngle[0]);
}

// 以input指定伺服馬達角度
void calculateServo_assign(int Angle_input){
    for(int i=0;i<4;i++)
      servoAngle[i] = Angle_input;
    Serial.println(Angle_input);
}

// 計算是指定角度(0)還是連續角度(1)變化
void ServoTrigger(){
  for(int i=0;i<4;i++){
    // Serial.print(button_currentValue[i]);
    // Serial.print(" ");
    if(button_currentValue[i] == 1){
      button_Triggered = !button_Triggered;
    }
  }
}

// 更新伺服馬達
void updateServo(){
  ServoTrigger();
  if(button_Triggered){
    calculateServo_continus();
  }
  else{
    if(Serial.available() > 0){
      serialRead(Angle_input);
    }
    calculateServo_assign(Angle_input);
  }
  for(int i=0;i<4;i++){
    myServo[i].write(servoAngle[i]);
  }
}
