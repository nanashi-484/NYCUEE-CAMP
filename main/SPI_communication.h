#include "Global_define.h"
#include <SPI.h>


void setupSPI() {
    pinMode(SS_Pin, OUTPUT);
    
}


void sendCommand() {
    SPI.beginTransaction(SPISettings(500000, LSBFIRST, SPI_MODE3));
    digitalWrite(SS_Pin, LOW);
    SPI.transfer(PU);
    if (button_currentValue[0] == 1) {command_current = SPI.transfer(PLAY);Serial.println(command_current);}
    else if (button_currentValue[1] == 1) command_current = SPI.transfer(STOP);
    else if (button_currentValue[2] == 1) command_current = SPI.transfer(REC);
    else if (button_currentValue[3] == 1) command_current = SPI.transfer(ERASE);
    else if (button_currentValue[4] == 1) command_current = SPI.transfer(FWD);
    else if (button_currentValue[5] == 1) command_current = SPI.transfer(RESET);
    Serial.println(command_current);
    // Serial.println(printBinary(10));
    delay(10);  // 確保指令傳輸完成
    digitalWrite(SS_Pin, HIGH);
    SPI.endTransaction();  
}
