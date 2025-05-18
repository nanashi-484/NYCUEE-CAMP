#include "Global_define.h"

// 設定按鈕為輸入並啟用內建上拉電阻
void setupButton(){
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonStates[i] = false;
    button_currentValue[i] = false;
  }
}


void ReadButton(){
  for (int i = 0; i < buttonCount; i++) {
    bool currentState = !digitalRead(buttonPins[i]); // 按下為 LOW

    if (currentState && !lastButtonStates[i]) {
      // 按鈕剛被按下
      buttonPressedTime[i] = millis();
      longPressDetected[i] = false;
      button_currentValue[i] = 1; // 短按先記下
    }

    else if (!currentState && lastButtonStates[i]) {
      // 按鈕剛放開
      if (!longPressDetected[i]) {
        button_currentValue[i] = 1; // 如果沒被當成長按，當作短按
      }
      else {
        button_currentValue[i] = 0; // 長按已處理，不再視為短按
      }
    }

    else if (currentState && !longPressDetected[i]) {
      // 按鈕持續按住中，尚未觸發長按
      if (millis() - buttonPressedTime[i] >= LONG_PRESS_TIME) {
        longPressDetected[i] = true;
      }
    }

    else {
      // 其餘情況：未觸發動作
      button_currentValue[i] = 0;
    }

    lastButtonStates[i] = currentState;
  }
}
