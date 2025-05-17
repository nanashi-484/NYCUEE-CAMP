#include "SPI_communication.h"
#include "Button_read.h"
#include "OLED_control.h"
int freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
void setup(){
  Serial.begin(9600);
  setupOLED();
  setupButton();
  setupSPI();
}

void loop(){
  if (mode == COMMUNICATION){
    Serial.println(freeRam());
    updateOLED();
    /*
    ReadButton();
    if (button_currentValue[1]) { // 偵測 STOP 鍵
      command_current = STOP;
      sendCommand();
      updateOLED();
    }
    */
    sendCommand();
    delay(1000);
  }

  if (mode == WAITING_COMMAND){
    ReadButton();
    updateOLED();
    receiveCommand();
    delay(50);
  }

  if (mode == ERROR_MODE){
  }
}
