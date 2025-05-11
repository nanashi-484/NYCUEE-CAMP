#include "Global_define.h"

// 設定按鈕為輸入並啟用內建上拉電阻
void setupButton(){
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonStates[i] = false;
    button_currentValue[i] = false;
  }
}

// 讀取按鈕數值
void ReadButton(){
  for (int i = 0; i < buttonCount; i++) {
    bool currentState = !digitalRead(buttonPins[i]); // 按下為 LOW，取反
    if (currentState && !lastButtonStates[i]) {
      //CoinData[i]++;
      button_currentValue[i] = 1;
    }
    else{
      button_currentValue[i] = 0;
    }
    lastButtonStates[i] = currentState;
  }
}
