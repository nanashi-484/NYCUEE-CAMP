#include "Global_define.h"
// 初始化光敏電阻參數
void setupPhoto()
{
  for (int i = 0; i < 4; i++)
  {
    threshold[i] = 400;
    PhotoData[i] = 0;
    CoinActive[i] = 0;
    CoinTotal[i] = 0;
  }
}

// 高頻率讀取光敏電阻
void ReadPhoto_HIGH(){
  for (int t = 0; t < 4; t++)
  {
    PhotoData[t] = analogRead(photoPins[t]);
    // threshold[t] = 63 * (threshold[t] / 64.0) + (CoinData[t]) / 64.0;

    if (PhotoData[t] > threshold[t] * hardThreshold)
      CoinActive[t] = 1;
  }
}

// 低頻計算平均值
void ReadPhoto_LOW(){
  Serial.println("Current :");
  for (int t = 0; t < 4; t++){
    threshold[t] = (7 * (threshold[t]) + (PhotoData[t])) / 8;

    if(CoinActive[t])
      CoinTotal[t] ++ ;
    // threshold[t] = 700;

    Serial.print("  Coin[");
    Serial.print(t);
    Serial.print("] : threshold = ");
    Serial.print(threshold[t]);
    Serial.print(" CoinData = ");
    Serial.print(PhotoData[t]);
    Serial.print(" CoinActive = ");
    Serial.print(CoinActive[t]);
    Serial.print(" TotalCoin = ");
    Serial.println(CoinTotal[t]);

    CoinActive[t] = 0;
  }
}
