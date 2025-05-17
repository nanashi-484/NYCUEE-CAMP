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
  }

  if (mode == WAITING_COMMAND){
    ReadButton();
    sendCommand();
  }

  if (mode == ERROR_MODE){
  }
}
