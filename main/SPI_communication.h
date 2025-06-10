#include "Global_define.h"

void sendCommand() {
    switch (command_current) {
        case PLAY:
            break;
        case REC:
            break;
        case ERASE:
            break;
        case FWD:
            break;
        case RESET:
            break;
        case NULL_COMMAND:
            break;
        default:
            break;
    }
  delay(10);  // 確保指令傳輸完成

  mode = WAITING_COMMAND;
}
