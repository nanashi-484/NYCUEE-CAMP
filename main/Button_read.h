#include "Global_define.h"

// 設定按鈕為輸入並啟用內建上拉電阻
void setupButton(){
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonStates[i] = false;
    button_shortPress[i] = false;
    Button_longPress_Hendeled[i] = false;
    button_longPress_Detected[i] = false;
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
      if (!button_longPress_Detected[i]) {
        button_shortPress[i] = 1; // 如果沒被當成長按，當作短按
      }
      else {
        button_shortPress[i] = 0; // 長按已處理，不再視為短按
        Button_longPress_Hendeled[i] = 0; // 回到長按未處理狀態
        button_longPress_Detected[i] = false; // 長按結束
      }
    }

    else if (currentState && !button_longPress_Detected[i]) {
      // 按鈕持續按住中，尚未觸發長按
      if (millis() - buttonPressedTime[i] >= LONG_PRESS_TIME) {
        button_longPress_Detected[i] = true;
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

const byte COMMAND_LIST_SHORTPRESS[buttonCount] = { PLAY , STOP , REC , ERASE , FWD , G_ERASE}; // 短按對應的指令
const byte COMMAND_LIST_LONGPRESS[buttonCount]  = { SET_PLAY , RD_STATUS , SET_REC , G_ERASE , RD_STATUS , RD_STATUS}; // 長按對應的指令

void receiveCommand() {

  for(int i = 0;i < buttonCount; i++){
    if(button_longPress_Detected[i] == 1 && Button_longPress_Hendeled[i] == 0){ // 如果按鈕處於長按且未被處理
      command_current = COMMAND_LIST_LONGPRESS[i];
      mode = COMMUNICATION;
    }
    if(button_shortPress[i] == 1){
      command_current = COMMAND_LIST_SHORTPRESS[i];
      mode = COMMUNICATION;
    }
  }
}
