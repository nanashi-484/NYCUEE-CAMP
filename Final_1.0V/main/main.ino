// 主程式1.1.0

#include "OLED_control.h"
#include "Servo_control.h"
#include "Button_read.h"
#include "Photo_read.h"
#include "Motor_control.h"

void setup()
{
  Serial.begin(38400);
  setupOLED();
  delay(1000);
  setupMotor();
  setupPhoto();
  setupServo();
  setupButton();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop()
{
  if(!task_Timer){ //低頻任務
    updateMotor();
    updateServo();
    updateOLED();
    ReadPhoto_LOW();
  }

  // 高頻任務
  ReadButton();
  ReadPhoto_HIGH();

  if(task_Timer == task_Frequency){
    task_Timer = 0;
  }
  else{
    task_Timer ++ ;
  }
  //  delay(25);
}
