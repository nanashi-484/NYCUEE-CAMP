#include "Global_define.h"
#include <Wire.h>
#include <U8g2lib.h>

// OLED 使用硬體 I2C（節省記憶體的 page buffer 模式）
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// OLED 顯示資訊
#define USED_OLED_FONT u8g2_font_helvB14_tr // 定義使用的字體
const int MAX_NUMBER_OF_LINE = 4; // 最大顯示行數

const char *label_COMMUNICATION[MAX_NUMBER_OF_LINE] = {"COMMUNICATE:","","",""};
const char *label_WAITING_COMMAND[MAX_NUMBER_OF_LINE] = {"","","",""};
const char *label_ERROR[MAX_NUMBER_OF_LINE] = {"","","",""};

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
  char buffer[20];
  OLED_message(labels);

  u8g2.firstPage();
  do
  {
    u8g2.setFont(USED_OLED_FONT);

    for (int i = 0; i < MAX_NUMBER_OF_LINE; i++){
      snprintf(buffer, sizeof(buffer), "%s", labels[i]);
      u8g2.drawStr(0, 15 + i * 15, buffer);
    }
  } while (u8g2.nextPage());
}

// 決定OLED應該顯示的訊息
void OLED_message(char *labels[MAX_NUMBER_OF_LINE]){
  switch (mode){
    case COMMUNICATION:{
      labels[0] = label_COMMUNICATION[0];
      labels[1] = "    ";
    }
    
    case WAITING_COMMAND:{
      
    }
    
    case ERROR_MODE:{

    }
  }
}