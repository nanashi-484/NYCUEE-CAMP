#ifndef VALUE
#define VALUE

// 主程式
int task_Timer = 0;// 主程式任務計時器;
const int task_Frequency = 8;// 設定高頻任務相對低頻任務的觸發數

// 定義伺服馬達
#define vibrationPin A1
int servoPins[] = {3, 5, 6, 10};
bool servoSpeed;
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
const float hardThreshold = 1.3; //需要高平均 (hardThreshold) 倍才會觸發
int PhotoData[4]; //光敏電阻當下的值
bool CoinActive[4]; //硬幣是否落下
int CoinTotal[4]; //盒內總硬幣數

// 微動開關（尚未使用）
#define switchPin 2
#define ledPin 13

// 讀取序列埠數值成整數
void serialRead(int& value){
    value = 0;
    String temp_string = "";
    while (Serial.available() > 0) {
        char incomingByte = Serial.read();
        // 如果收到換行符號，結束讀取
        if (incomingByte == '\n') {
            break;
        }
        // 將字元加入字串
        temp_string += incomingByte;
    }
    value = temp_string.toInt();
}

#endif
