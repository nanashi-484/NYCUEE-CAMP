#include "Global_define.h"
#include <Wire.h>
#include <U8g2lib.h>

// OLED 使用硬體 I2C（節省記憶體的 page buffer 模式）
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// 外部定義

// OLED初始設定
void setupOLED()
{
  Wire.begin();
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.firstPage();
  do
  {
    u8g2.drawStr(0, 10, "System Initialized");
  } while (u8g2.nextPage());
}

// 顯示 OLED 畫面
void updateOLED()
{
  const char *labels[] = {"1-dollar", "5-dollar", "10-dollar", "50-dollar"};
  char buffer[20];

  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_helvB14_tr);

    for (int i = 0; i < 4; i++)
    {
      snprintf(buffer, sizeof(buffer), "%s: %d", labels[i], CoinData[i]);
      u8g2.drawStr(0, 15 + i * 15, buffer);
    }
  } while (u8g2.nextPage());
}
