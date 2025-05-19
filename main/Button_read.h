#include "Global_define.h"

// 設定按鈕為輸入並啟用內建上拉電阻
void setupButton(){
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonStates[i] = false;
    button_shortPress[i] = false;
    Button_longPress_Hendeled[i] = false;
    Button_longPress_Detected[i] = false;
  }
}


void ReadButton(){
  for (int i = 0; i < buttonCount; i++) {
    bool currentState = !digitalRead(buttonPins[i]); // 按下為 LOW

    if (currentState && !lastButtonStates[i]) {
      // 按鈕剛被按下
      buttonPressedTime[i] = millis();
    }

    else if (!currentState && lastButtonStates[i]) {
      // 按鈕剛放開
      if (!Button_longPress_Detected[i]) {
        button_shortPress[i] = 1; // 如果沒被當成長按，當作短按
      }
      else {
        button_shortPress[i] = 0; // 長按已處理，不再視為短按
        Button_longPress_Hendeled[i] = 0; // 回到長按未處理狀態
        Button_longPress_Detected[i] = false; // 長按結束
      }
    }

    else if (currentState && !Button_longPress_Detected[i]) {
      // 按鈕持續按住中，尚未觸發長按
      if (millis() - buttonPressedTime[i] >= LONG_PRESS_TIME) {
        Button_longPress_Detected[i] = true;
      }
      else {
        Button_longPress_Hendeled[i] = 0; //長按未觸發，設定未處理
      }
    }

    else {
      // 其餘情況：未觸發動作
      button_shortPress[i] = 0;
      Button_longPress_Hendeled[i] = 1; //長按經過一個loop、視為已觸發
    }

    lastButtonStates[i] = currentState;
  }
}

void receiveCommand() {
  mode = COMMUNICATION;
  if (Button_longPress_Detected[0] == 1 && Button_longPress_Hendeled[0] == 0)command_current = SET_PLAY;
  else if (button_shortPress[0] == 1) command_current = PLAY;
  else if (button_shortPress[1] == 1) command_current = STOP;
  else if (Button_longPress_Detected[2] == 1 && Button_longPress_Hendeled[2] == 0) command_current = SET_REC;
  else if (button_shortPress[2] == 1) command_current = REC;
  else if (Button_longPress_Detected[3] == 1 && Button_longPress_Hendeled[3] == 0) command_current = G_ERASE; 
  else if (button_shortPress[3] == 1) command_current = ERASE;
  else if (button_shortPress[4] == 1) command_current = FWD;
  else if (button_shortPress[5] == 1) command_current = G_ERASE;
  else mode = WAITING_COMMAND;
}
