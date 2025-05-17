#include "Global_define.h"
#include <SPI.h>

void resetISD1760();
void powerUpISD1760();

void setupSPI() {
    pinMode(SS_Pin, OUTPUT);
    pinMode(MOSI_Pin, OUTPUT);
    pinMode(MISO_Pin, INPUT);
    pinMode(SCK_Pin, OUTPUT);
    digitalWrite(SS_Pin, HIGH);
    SPI.begin();
  
    // 重置 ISD1760
    resetISD1760();
    
    // 上電 ISD1760
    powerUpISD1760();
}

void receiveCommand() {
    mode = COMMUNICATION;
    if (button_currentValue[0] == 1) command_current = PLAY;
    else if (button_currentValue[1] == 1) command_current = STOP;
    else if (button_currentValue[2] == 1) command_current = REC;
    else if (button_currentValue[3] == 1) command_current = RD_STATUS;
    else if (button_currentValue[4] == 1) command_current = FWD;
    else if (button_currentValue[5] == 1) command_current = RESET;
    else mode = WAITING_COMMAND;
}

void sendCommand() {
    SPI.beginTransaction(SPISettings(500000, LSBFIRST, SPI_MODE3));
    digitalWrite(SS_Pin, LOW);
    SPI.transfer(PU);
    //Serial.println(command_current);
    uint8_t a = SPI.transfer(command_current);
    Serial.println(a);

    bool* tempBool;
//    intToBinary(a,tempBool,16);
    char* tempChar;
//    binaryArrayToString(tempBool,16,tempChar);
//    Serial.println(tempChar);

    // Serial.println(command_current);
    // Serial.println(printBinary(10));
    delay(10);  // 確保指令傳輸完成
    digitalWrite(SS_Pin, HIGH);
    SPI.endTransaction();
    delay(1000);
    mode = WAITING_COMMAND;
}


void resetISD1760() {
  digitalWrite(SS_Pin, LOW);
  SPI.beginTransaction(SPISettings(500000, LSBFIRST, SPI_MODE3));
  SPI.transfer(RESET);
  SPI.endTransaction();
  digitalWrite(SS_Pin, HIGH);
  
  delay(100); // 等待設備重置完成
}

void powerUpISD1760() {
  digitalWrite(SS_Pin, LOW);
  SPI.beginTransaction(SPISettings(500000, LSBFIRST, SPI_MODE3));
  SPI.transfer(PU);  // 發送上電指令
  SPI.endTransaction();
  digitalWrite(SS_Pin, HIGH);
  
  delay(30); // 等待設備上電完成
}
