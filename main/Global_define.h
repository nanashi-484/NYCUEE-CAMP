#ifndef VALUE
#define VALUE
#include <stdio.h>
#include <string.h>

// 主程式
enum Mode
{
    COMMUNICATION,  // 按下/按住按鈕後處理指令
    WAITING_COMMAND // 等待使用者輸入
};
Mode mode = WAITING_COMMAND;

int task_Timer = 0;           // 主程式任務計時器;
const int task_Frequency = 8; // 設定高頻任務相對低頻任務的觸發數

enum Command
{
    PLAY,       // 播放
    G_PLAY,     // 播放全部
    REC,        // 錄音
    ERASE,      // 擦除
    G_ERASE,     // 擦除全部
    FWD,        // 快轉
    RESET,      // 重置
    NULL_COMMAND,       // 空指令
};
Command command_current = NULL_COMMAND; // 當前指令
Command command_previous = NULL_COMMAND; // 前一個指令

// INT腳位
const int INT_PIN = 3; // INT腳位
bool INT_state = false; // INT腳位狀態

// 按鈕腳位
const int buttonPins[] = {2, 4, 6, 7, 8, 9}; // PLAY REC TEMP1 ERASE FWD RESET
const int buttonCount = 6; // 按鈕數量
// 按鈕對應的指令
const Command COMMAND_LIST_SHORTPRESS[buttonCount] = {PLAY, NULL_COMMAND, NULL_COMMAND, ERASE, FWD, RESET}; // 短按對應的指令
const Command COMMAND_LIST_LONGPRESS[buttonCount] = {G_PLAY, REC, NULL_COMMAND, G_ERASE, NULL_COMMAND, NULL_COMMAND}; // 長按對應的指令

// 按鈕狀態變數
#define LONG_PRESS_TIME 1000  // 長按門檻（毫秒）

bool lastButtonStates[buttonCount];
bool button_shortPress[buttonCount];          // 紀錄是否為短按
unsigned long buttonPressedTime[buttonCount]; // 記錄每顆按下的時間
bool button_longPress_Detected[buttonCount];         // 長按是否已被觸發
bool Button_longPress_Hendeled[buttonCount];         // 長按是否已經被處理過

//================================================================
//=========================函數定義================================
//================================================================

// 讀取序列埠數值成整數
void serialRead(int &value)
{
    value = 0;
    String temp_string = "";
    while (Serial.available() > 0)
    {
        char incomingByte = Serial.read();
        // 如果收到換行符號，結束讀取
        if (incomingByte == '\n')
        {
            break;
        }
        // 將字元加入字串
        temp_string += incomingByte;
    }
    value = temp_string.toInt();
}

char* concatenateStrings(char* dest, const char* str1, const char* str2) {
    // 先將 str1 複製到 dest 中
    strcpy(dest, str1);
//    dest[] = '\0';  // 確保字串結尾
    
    // 將 str2 附加到 dest 後面，限制附加長度以避免溢位
    strcat(dest, str2);
    
    return dest;
}

// 使序列埠印出byte(LSB->MSB)
void SerialPrintByte(byte in){
    bool out[8];
    int a = in;
    Serial.print(a);

    for (int i = 0 ; i < 7; i++) {
        if (a%2) {
            out[i] = 1;
        } else {
            out[i] = 0;
        }
        a = a/2;
    }

    for(int t=0 ; t<8 ;t++){
        if(out[t])
            Serial.print(1);
        else
            Serial.print(0);
    }
    Serial.println("");
}

#endif
