#ifndef VALUE
#define VALUE

// 主程式
enum Mode
{
    ERROR,          // 當發生程序無法繼續運行的錯誤，進入ERROR
    COMMUNICATION,  // 需要與IDS1760 SPI通訊時
    WAITING_COMMAND // 等待使用者輸入
};
Mode mode = WAITING_COMMAND;

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

// 按鈕腳位
const int buttonPins[] = {4, 7, 8, 9, 2};
const int buttonCount = 5;

// 按鈕狀態變數
bool lastButtonStates[buttonCount];
bool button_currentValue[buttonCount];

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

#endif
