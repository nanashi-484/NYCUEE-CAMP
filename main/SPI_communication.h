#include "Global_define.h"
#include <SPI.h>


void setupSPI() {
    pinMode(SS_Pin, OUTPUT);
    
}


void sendCommand() {
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(SS_Pin, LOW);
    if (button_currentValue[0] == 1) command_current =SPI.transfer(PLAY);
    else if (button_currentValue[1] == 1) command_current =SPI.transfer(STOP);
    else if (button_currentValue[2] == 1) command_current =SPI.transfer(REC);
    else if (button_currentValue[3] == 1) command_current =SPI.transfer(ERASE);
    else if (button_currentValue[4] == 1) command_current =SPI.transfer(FWD);
    else command_current = SPI.transfer(RESET);
    delay(10);  // 確保指令傳輸完成
    digitalWrite(SS_Pin, HIGH);
    SPI.endTransaction();  
}
