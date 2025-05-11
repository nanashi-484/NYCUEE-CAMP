#include "Global_define.h"
// 初始化光敏電阻參數
void setupPhoto()
{
  for (int i = 0; i < 4; i++)
  {
    threshold[i] = 400;
    CoinData[i] = 0;
    CoinActive[i] = 0;
  }
}

// 讀取光敏電阻，並設定平均值
void ReadPhoto()
{
  Serial.println("Current :");
  for (int t = 0; t < 4; t++)
  {
    CoinData[t] = analogRead(photoPins[t]);
    threshold[t] = 63 * (threshold[t] / 64.0) + (CoinData[t]) / 64.0;

    if (CoinData[t] > threshold[t] * hardThreshold)
      CoinActive[t] += 1;

    Serial.print("  Coin[");
    Serial.print(t);
    Serial.print("] : threshold = ");
    Serial.print(threshold[t]);
    Serial.print(" CoinData = ");
    Serial.print(CoinData[t]);
    Serial.print(" CoinActive = ");
    Serial.println(CoinActive[t]);
  }
}
