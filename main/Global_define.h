#ifndef VALUE
#define VALUE
#include <stdio.h>
#include <string.h>

// 主程式
enum Mode
{
    COMMUNICATION,  // 需要與IDS1760 SPI通訊時
    WAITING_COMMAND // 等待使用者輸入
};
Mode mode = WAITING_COMMAND;

int errorCode = 0; // 錯誤代碼，如果發生錯誤則不為0
int task_Timer = 0;           // 主程式任務計時器;
const int task_Frequency = 8; // 設定高頻任務相對低頻任務的觸發數

// SPI通訊
#define PU 0x01
#define STOP 0x02
#define RESET 0x03
#define CLR_INT 0x04
#define RD_STATUS 0x05
#define RD_PLAY_PTR 0x06
#define PD 0x07
#define RD_REC_PTR 0x08
#define DEVID 0x09
#define PLAY 0x40
#define REC 0x41
#define REC_LED 0x51 // record with LED on
#define ERASE 0x42
#define G_ERASE 0x43
#define RD_APC 0x44
#define WR_APC1 0x45
#define WR_APC2 0x65
#define WR_NVCFG 0x46
#define LD_NVCFG 0x47
#define FWD 0x48
#define CHK_MEM 0x49
#define EXTCLK 0x4A
#define SET_PLAY 0x80
#define SET_REC 0x81
#define SET_REC_LED 0x91 // set record with LED on
#define SET_ERASE 0x82

#define WAIT_TIME 10 // waiting time (ms) after SS=LOW at least 500ns
#define WAIT_TIME2 100

const int SS_Pin = 10;
const int MISO_Pin = 12;
const int MOSI_Pin = 11;
const int SCK_Pin = 13;

byte command_current; //目前執行的指令

// 按鈕腳位
const int buttonPins[] = {2, 4, 5, 6, 7, 8, 9}; // PLAY STOP REC ERA FWD RESET
const int buttonCount = 7;

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
