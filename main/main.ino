#include "Command_logic.h"
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

    updateOLED();
    sendCommand();
    delay(1000);
  }

  if (mode == WAITING_COMMAND){
    ReadButton();
    updateOLED();
    receiveCommand();
    delay(100);
  }
}
