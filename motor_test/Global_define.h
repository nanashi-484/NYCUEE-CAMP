#ifndef VALUE
#define VALUE

// 定義伺服馬達
#define vibrationPin A1
int servoPins[] = {3, 5, 6, 10};
int servoSpeed;
int servoAngle[4];

// 定義馬達
#define motorPinB A0 //for digital output
#define motorPinA 11 //for analog output
int motorSpeed;
bool motorDirect , motorAddSpeed;

// 按鈕腳位
const int buttonPins[] = {4, 7, 8, 9, 12}; 
const int buttonCount = 5;

// 按鈕狀態變數
bool lastButtonStates[buttonCount];
bool button_currentValue[buttonCount];

// 光敏腳位 & 數據
const int photoPins[] = {A2, A3, A6, A7};
float threshold[4]; //自動門檻
const float hardThreshold = 0.4; //需要高平均 (1+hardThreshold) 倍才會觸發
int CoinData[4];
bool CoinActive[4]; //硬幣是否落下

// 微動開關（尚未使用）
#define switchPin 2
#define ledPin 13

#endif
