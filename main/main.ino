#include "SPI_communication.h"
#include "Button_read.h"
#include "OLED_control.h"

void setup(){
  Serial.begin(9600);
  setupOLED();
  setupButton();
  setupSPI();
}

void loop(){
  if (mode == COMMUNICATION){
    sendCommand();
  }

  if (mode == WAITING_COMMAND){
    ReadButton();
    receiveCommand();
    updateOLED();
  }

  if (mode == ERROR_MODE){
  }
}
