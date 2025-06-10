#include "Global_define.h"

void modeLogic() {
    case(mode) {
        case COMMUNICATION:
            // 在這裡處理 COMMUNICATION 模式的邏輯
            if (command_current == NULL_COMMAND) {
                mode = WAITING_COMMAND; // 如果沒有指令，切換到等待指令模式
            }
            break;
        case WAITING_COMMAND:
            // 在這裡處理 WAITING_COMMAND 模式的邏輯
            if (command_current != NULL_COMMAND) {
                mode = COMMUNICATION; // 如果有指令，切換到通信模式
            }
            break;
        default:
            break;
    }
}

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
