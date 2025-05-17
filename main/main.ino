#include "SPI_communication.h"
#include "Button_read.h"
#include "OLED_control.h"

void setup(){
  Serial.begin(9600);
  //setupOLED();
  setupButton();
  setupSPI();
}

void loop(){
  if (mode == COMMUNICATION){
    /*
    ReadButton();
    if (button_currentValue[1]) { // 偵測 STOP 鍵
      command_current = STOP;
      sendCommand();
      updateOLED();
    }*/
    sendCommand();
    updateOLED();
  }

  if (mode == WAITING_COMMAND){
    ReadButton();
    receiveCommand();
    updateOLED();
  }

  if (mode == ERROR_MODE){
  }
}
