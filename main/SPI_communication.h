#include "Global_define.h"
#include <SPI.h>
void playFromTo(uint16_t startAddr, uint16_t endAddr);
void recordFromTo(uint16_t startAddr, uint16_t endAddr);
void SendtoISD(byte);
bool isRecording(), isPlaying();
void fullReset();
uint16_t readPlayPointer();
byte checkMemoryStatus();

void setupSPI() {
  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  pinMode(SS_Pin, OUTPUT);

  digitalWrite(SS_Pin, LOW);
  SPI.transfer(PU);
  SPI.transfer(0x00);
  digitalWrite(SS_Pin, HIGH);
  //fullReset(); // 初始化時全清除
  delay(100);
  //readPlayPointer();
  checkMemoryStatus();
}

void sendCommand() {
    switch (command_current) {
        case PLAY:
            SendtoISD(command_current);
            break;
        case SET_PLAY:
            playFromTo(0x0010, 0x00A0);
            break;
        case REC:
            SendtoISD(command_current);
            break;
        case SET_REC:
            recordFromTo(0x0010, 0x00A0);
            break;
        case STOP:
            SendtoISD(command_current);
            break;
        case ERASE:
            SendtoISD(command_current);
            break;
        case G_ERASE:
            SendtoISD(command_current);
            //SendtoISD(CLR_INT);
            break;
        case FWD:
            SendtoISD(command_current);
            break;
        case RESET:
            SendtoISD(command_current);
            break;
        case RD_STATUS:
            isRecording();
            break;
        default:
            break;
    }
  delay(10);  // 確保指令傳輸完成

  mode = WAITING_COMMAND;
}
byte checkMemoryStatus() {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(0x44); // CHK_MEM 指令
  SPI.transfer(0x00); // 格式固定
  byte cmr = SPI.transfer(0x00); // 讀出記憶體狀態

  digitalWrite(SS_Pin, HIGH);

  Serial.print("記憶體狀態 CMR: 0b");
  Serial.println(cmr, BIN);

  if (cmr & 0b10000000) Serial.println("記憶體已滿 (OVF)");
  if (cmr & 0b01000000) Serial.println("有語音資料 (EOM)");
  if (cmr & 0b00100000) Serial.println("錄音段重疊 (CMP)");

  return cmr;
}

void recordFromTo(uint16_t startAddr, uint16_t endAddr) {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(SET_REC); // SET_REC 指令
  SPI.transfer(0x00); // 保留位

  SPI.transfer(startAddr & 0xFF);           // S7:S0
  SPI.transfer((startAddr >> 8) & 0x07);    // S10:S8

  SPI.transfer(endAddr & 0xFF);             // E7:E0
  SPI.transfer((endAddr >> 8) & 0x07);      // E10:E8

  delayMicroseconds(5);
  digitalWrite(SS_Pin, HIGH);

  Serial.print("開始錄音：從 0x");
  Serial.print(startAddr, HEX);
  Serial.print(" 到 0x");
  Serial.println(endAddr, HEX);
}

void SendtoISD(byte) {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(command_current);
  SPI.transfer(0x00); // 格式固定

  delayMicroseconds(5);
  digitalWrite(SS_Pin, HIGH);
}


void playFromTo(uint16_t startAddr, uint16_t endAddr) {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(0x80); // SET_PLAY 指令
  SPI.transfer(0x00); // 保留位

  SPI.transfer(startAddr & 0xFF);
  SPI.transfer((startAddr >> 8) & 0x07);

  SPI.transfer(endAddr & 0xFF);
  SPI.transfer((endAddr >> 8) & 0x07);

  delayMicroseconds(5);
  digitalWrite(SS_Pin, HIGH);

  Serial.print("播放語音：從 0x");
  Serial.print(startAddr, HEX);
  Serial.print(" 到 0x");
  Serial.println(endAddr, HEX);
}

void fullReset() {
  Serial.println(" 開始清除整顆 ISD1700...");

  // 1. 全部擦除
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);
  SPI.transfer(0x43);  // G_ERASE 指令
  SPI.transfer(0x00);

  delayMicroseconds(5);
  digitalWrite(SS_Pin, HIGH);

  delay(500); // 擦除動作會花一點時間

  // 2. RESET
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);
  SPI.transfer(0x03);  // RESET 指令
  SPI.transfer(0x00);
  delayMicroseconds(5);
  digitalWrite(SS_Pin, HIGH);

  delay(100);

  // 3. CLR_INT
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);
  SPI.transfer(0x04);  // CLR_INT 指令
  SPI.transfer(0x00);
  delayMicroseconds(5);
  digitalWrite(SS_Pin, HIGH);

  Serial.println(" 已完成全清除與重置");
}

uint16_t readPlayPointer() {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(0x06); // RD_PLAY_PTR
  SPI.transfer(0x00); // 固定格式

  byte sr0 = SPI.transfer(0x00); // 狀態暫存器 SR0
  byte sr1 = SPI.transfer(0x00); // 狀態暫存器 SR1

  byte low = SPI.transfer(0x00);  // P7:P0
  byte high = SPI.transfer(0x00); // P10:P8

  digitalWrite(SS_Pin, HIGH);

  uint16_t pointer = ((high & 0x07) << 8) | low;

  Serial.print(" 放音指針地址：0x");
  Serial.println(pointer, HEX);
  return pointer;
}

bool isPlaying() {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(RD_STATUS);
  SPI.transfer(0x00);     // 第二 byte 固定

  byte sr0 = SPI.transfer(0x00);  // SR0（可略過）
  byte sr1 = SPI.transfer(0x00);  // SR1（我們要用這個）

  digitalWrite(SS_Pin, HIGH);

  bool playing = (sr1 & 0b00000100);  // bit2 = 1 表示正在播放

  Serial.print("播放狀態：");
  Serial.println(playing ? "正在播放 🎵" : "未播放 💤");

  return playing;
}

bool isRecording() {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  byte sr0 = SPI.transfer(RD_STATUS);
  byte sr1 = SPI.transfer(0x00);     // 固定格式

  byte sr2 = SPI.transfer(0x00);  // 忽略 SR0
  byte sr3 = SPI.transfer(0x00);  // 讀取 SR1

  byte sr4 = SPI.transfer(0x00);  // 忽略 SR0
  byte sr5 = SPI.transfer(0x00);  // 讀取 SR1

  delayMicroseconds(5);
  digitalWrite(SS_Pin, HIGH);

  bool recording = (sr1 & 0b00001000); // SR1 bit3 = REC
  SerialPrintByte(sr0);
  SerialPrintByte(sr1);
  SerialPrintByte(sr2);
  SerialPrintByte(sr3);
  SerialPrintByte(sr4);
  SerialPrintByte(sr5);
//   Serial.print("錄音狀態：");
//   Serial.println(recording ? "錄音中" : "未錄音");
  return recording;
}
