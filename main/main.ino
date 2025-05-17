#include "SPI_communication.h"
#include "Button_read.h"
#include "OLED_control.h"

void setup() {

  Serial.begin(9600);
  setupOLED();
  setupButton();

}

void loop() {

  if(mode == COMMUNICATION){

  }

  if(mode == WAITING_COMMAND){

  }

  if(mode == ERROR_MODE){

  }

}
