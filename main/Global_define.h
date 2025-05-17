#ifndef VALUE
#define VALUE

// 主程式
enum Mode{
    ERROR, // 當發生程序無法繼續運行的錯誤，進入ERROR
    COMMUNICATION, // 需要與IDS1760 SPI通訊時
    WAITING_COMMAND // 等待使用者輸入
};
Mode mode = WAITING_COMMAND;

int task_Timer = 0;// 主程式任務計時器;
const int task_Frequency = 8;// 設定高頻任務相對低頻任務的觸發數

// SPI通訊
const int SS_Pin = 10;
const int MISO_Pin = 12;
const int MOSI_Pin = 11;


// 按鈕腳位
const int buttonPins[] = {4, 7, 8, 9, 2}; 
const int buttonCount = 5;

// 按鈕狀態變數
bool lastButtonStates[buttonCount];
bool button_currentValue[buttonCount];

// 讀取序列埠數值成整數
void serialRead(int& value){
    value = 0;
    String temp_string = "";
    while (Serial.available() > 0) {
        char incomingByte = Serial.read();
        // 如果收到換行符號，結束讀取
        if (incomingByte == '\n') {
            break;
        }
        // 將字元加入字串
        temp_string += incomingByte;
    }
    value = temp_string.toInt();
}

#endif
