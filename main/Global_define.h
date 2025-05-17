#ifndef VALUE
#define VALUE
#include <stdio.h>
#include <string.h>

// 主程式
enum Mode
{
    ERROR_MODE,          // 當發生程序無法繼續運行的錯誤，進入ERROR
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

int command_current; //目前執行的指令

// 按鈕腳位
const int buttonPins[] = {2, 3, 4, 7, 8, 9}; // PLAY STOP REC ERA FWD RESET
const int buttonCount = 6;

// 按鈕狀態變數
bool lastButtonStates[buttonCount];
bool button_currentValue[buttonCount];

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

// 函數：合併兩個字串並返回結果
// 參數：
//   dest - 目標字串陣列（必須有足夠空間）
//   str1 - 第一個輸入字串
//   str2 - 第二個輸入字串
// 返回值：合併後的字串（即 dest 的指標）
char* concatenateStrings(char* dest, const char* str1, const char* str2) {
    // 先將 str1 複製到 dest 中
    strcpy(dest, str1);
//    dest[] = '\0';  // 確保字串結尾
    
    // 將 str2 附加到 dest 後面，限制附加長度以避免溢位
    strcat(dest, str2);
    
    return dest;
}

void intToBinary(int num, bool binaryArray[], int arraySize) {
    // 處理負數的情況，先轉為無符號整數以避免問題
    unsigned int unum = (unsigned int)num;
    
    // 初始化陣列為 0
    for (int i = 0; i < arraySize; i++) {
        binaryArray[i] = 0;
    }
    
    // 從最高位開始計算二進制
    int index = arraySize - 1;
    if (num == 0) {
        binaryArray[index] = 0;
        return;
    }
    
    // 對負數特別處理（使用補碼表示）
    if (num < 0) {
        unum = ~unum + 1; // 取得二進制補碼
    }
    
    // 轉換為二進制
    while (unum > 0 && index >= 0) {
        binaryArray[index] = unum % 2;
        unum /= 2;
        index--;
    }
}

// 將二進制陣列轉為字串的函式
// 參數：binaryArray 是二進制陣列，size 是陣列大小，binaryString 是用來儲存結果的字串
void binaryArrayToString(int binaryArray[], int size, char binaryString[]) {
    for (int i = 0; i < size; i++) {
        binaryString[i] = binaryArray[i] ? '1' : '0'; // 將 0 轉為 '0'，1 轉為 '1'
    }
    binaryString[size] = '\0'; // 在字串結尾加上空字元，表示字串結束
}

// 將int轉為binary的string
// char* printBinary(int num) {
//     int bits = sizeof(int) * 8; // 計算 int 的位元數，通常是 32 位
//     char* textOutput = "";
//     for (int i = bits - 1; i >= 0; i--) {
//         // 使用位元 AND 檢查第 i 位是否為 1
//         int bit = (num >> i) & 1;
//         if(bit){
//           textOutput = textOutput + '1';
//         }
//         else{
//           textOutput = textOutput + '0';
//         }
//     }
//     Serial.println(textOutput);
//     return textOutput;
//   }

#endif
