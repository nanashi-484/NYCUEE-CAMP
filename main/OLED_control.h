#include "Global_define.h"
#include <Wire.h>
#include <U8g2lib.h>

// OLED 使用硬體 I2C（節省記憶體的 page buffer 模式）
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// OLED 顯示資訊
#define USED_OLED_FONT u8g2_font_5x7_tf // 定義使用的字體
const int MAX_NUMBER_OF_LINE = 4; // 最大顯示行數

char* CommandToText();
void OLED_message(char *labels[MAX_NUMBER_OF_LINE]);
char* ErrorToText(int line = 1/*需要輸出的行數*/);


// OLED初始設定
void setupOLED()
{
  Wire.begin();
  u8g2.begin();
  u8g2.setFont(USED_OLED_FONT);
  u8g2.firstPage();
  do
  {
    u8g2.drawStr(0, 10, "System Initialized");
  } while (u8g2.nextPage());
}

// 顯示 OLED 畫面
void updateOLED()
{
  char *labels[MAX_NUMBER_OF_LINE];
  OLED_message(labels);

  u8g2.firstPage();
  do
  {
    u8g2.setFont(USED_OLED_FONT);

    for (int i = 0; i < MAX_NUMBER_OF_LINE; i++){
      u8g2.drawStr(0, 15 + i * 15, labels[i]);
    }
  } while (u8g2.nextPage());
}

// 決定OLED應該顯示的訊息
void OLED_message(char *labels[MAX_NUMBER_OF_LINE]){
  switch (mode){
    case COMMUNICATION:
      labels[0] = "COMMUNICATING... ";
      // concatenateStrings(labels[1],"  command: ",CommandToText());
      concatenateStrings(labels[1],"  command: ",CommandToText());
      labels[2] = "INSTRUCT: ";
      // snprintf(labels[3], sizeof(labels[3]), "%s:%d", 11 , command_current);
      labels[3] = ".e";
      break;
    
    case WAITING_COMMAND:
      labels[0] = "STATUS: ";
      labels[1] = ".e";
      labels[2] = "  Ready!";
      labels[3] = ".e";
      break;
    
    case ERROR_MODE:
      labels[0] = "ERROR: ";
      snprintf(labels[1], sizeof(labels[1]), "%s:%d", "  " , ErrorToText(1));
      snprintf(labels[2], sizeof(labels[2]), "%s:%d", "  " , ErrorToText(2));
      snprintf(labels[3], sizeof(labels[3]), "%s:%d", "  " , ErrorToText(3));
      break;
  }
}

// 將現在的指令轉換為對應的文字
char* CommandToText() {
  char* textOutput;
  switch (command_current) {
    case 0x01:
        textOutput = "PU";
        break;
    case 0x02:  // STOP
        textOutput = "STOP";
        break;
    case 0x03:  // RESET
        textOutput = "RESET";
        break;
    case 0x04:  // CLR_INT
        textOutput = "CLR_INT";
        break;
    case 0x05:  // RD_STATUS
        textOutput = "RD_STATUS";
        break;
    case 0x06:  // RD_PLAY_PTR
        textOutput = "RD_PLAY_PTR";
        break;
    case 0x07:  // PD
        textOutput = "PD";
        break;
    case 0x08:  // RD_REC_PTR
        textOutput = "RD_REC_PTR";
        break;
    case 0x09:  // DEVID
        textOutput = "DEVID";
        break;
    case 0x40:  // PLAY
        textOutput = "PLAY";
        break;
    case 0x41:  // REC
        textOutput = "REC";
        break;
    case 0x42:  // ERASE
        textOutput = "ERASE";
        break;
    case 0x43:  // G_ERASE
        textOutput = "G_ERASE";
        break;
    case 0x44:  // RD_APC
        textOutput = "RD_APC";
        break;
    case 0x45:  // WR_APC1
        textOutput = "WR_APC1";
        break;
    case 0x46:  // WR_NVCFG
        textOutput = "WR_NVCFG";
        break;
    case 0x47:  // LD_NVCFG
        textOutput = "LD_NVCFG";
        break;
    case 0x48:  // FWD
        textOutput = "FWD";
        break;
    case 0x49:  // CHK_MEM
        textOutput = "CHK_MEM";
        break;
    case 0x4A:  // EXTCLK
        textOutput = "EXTCLK";
        break;
    case 0x51:  // REC_LED
        textOutput = "REC_LED";
        break;
    case 0x65:  // WR_APC2
        textOutput = "WR_APC2";
        break;
    case 0x80:  // SET_PLAY
        textOutput = "SET_PLAY";
        break;
    case 0x81:  // SET_REC
        textOutput = "SET_REC";
        break;
    case 0x82:  // SET_ERASE
        textOutput = "SET_ERASE";
        break;
    case 0x91:  // SET_REC_LED
        textOutput = "SET_REC_LED";
        break;
    default:
        textOutput = "Unknown Command";  // 預設情況，返回未知指令的字串
        errorCode = 1;
        mode = ERROR_MODE;
        break;
  }
  return textOutput;  // 返回轉換後的文字
}

//根據error code輸出對應的錯誤代碼
char* ErrorToText(int line = 1/*需要輸出的行數*/){
  char* text_line1,text_line2,text_line3,textOutput;
  switch (errorCode){
    case 1:
      text_line1 = "Unknown Command";
      text_line2 = "Please chack command sended by SPI";
      text_line3 = "which sended by SPI";
      break;
    
    default:
      text_line1 = "";
      text_line2 = "";
      text_line3 = "";
      break;
  }
  switch (line){
    case 1:
      textOutput = text_line1;
      break;
    case 2:
      textOutput = text_line2;
      break;
    case 3:
      textOutput = text_line3;
      break;
    default:
      textOutput = "";
      break;
  }
}
