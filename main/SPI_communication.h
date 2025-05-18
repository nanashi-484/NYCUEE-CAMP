#include "Global_define.h"
#include <SPI.h>
void playFromTo(uint16_t startAddr, uint16_t endAddr);
void recordFromTo(uint16_t startAddr, uint16_t endAddr);
void sendStop(), play(), Record();
bool isRecording(), isPlaying();
void fullReset();
uint16_t readPlayPointer();
byte checkMemoryStatus();

void setupSPI() {
    SPI.begin();
    SPI.setBitOrder(LSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    pinMode(SS_Pin, OUTPUT);
    
    digitalWrite(SS_Pin,LOW);
    SPI.transfer(PU); // power up
    SPI.transfer(0x00); 
    digitalWrite(SS_Pin,HIGH);
    
    delay(100);
    //fullReset(); // 初始化時全清除
    delay(100);
    //readPlayPointer();
    checkMemoryStatus();
}

void receiveCommand() {
    mode = COMMUNICATION;
    if (button_currentValue[0] == 1) command_current = PLAY;
    else if (button_currentValue[1] == 1) command_current = STOP;
    else if (button_currentValue[2] == 1) command_current = REC;
    else if (button_currentValue[3] == 1) command_current = ERASE;
    else if (button_currentValue[4] == 1) command_current = FWD;
    else if (button_currentValue[5] == 1) command_current = RESET;
    else mode = WAITING_COMMAND;
}

void sendCommand() {

    if(command_current == PLAY){
        sendtoISD(command_current);
    }
    else if(command_current == REC){
        sendtoISD(command_current);
    }
    else if(command_current == STOP){
        sendtoISD(command_current);
    }
    else if(command_current == ERASE){
        sendtoISD(command_current);
    }
    else if(command_current == FWD){
        sendtoISD(command_current);
    }
    else if(command_current == RESET){
        sendtoISD(command_current);
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

  Serial.print("📦 記憶體狀態 CMR: 0b");
  Serial.println(cmr, BIN);

  if (cmr & 0b10000000) Serial.println("⚠️ 記憶體已滿 (OVF)");
  if (cmr & 0b01000000) Serial.println("✅ 有語音資料 (EOM)");
  if (cmr & 0b00100000) Serial.println("⚠️ 錄音段重疊 (CMP)");

  return cmr;
}

void recordFromTo(uint16_t startAddr, uint16_t endAddr) {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(0x81); // SET_REC 指令
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

void SendtoISD(int command_current) {
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

bool isRecording() {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(0x05);     // RD_STATUS
  SPI.transfer(0x00);     // 固定格式

  byte sr0 = SPI.transfer(0x00);  // 忽略 SR0
  byte sr1 = SPI.transfer(0x00);  // 讀取 SR1
  
  delayMicroseconds(5); 
  digitalWrite(SS_Pin, HIGH);

  bool recording = (sr1 & 0b00001000); // SR1 bit3 = REC
  Serial.print("錄音狀態：");
  Serial.println(recording ? "錄音中" : "未錄音");
  return recording;
}


void fullReset() {
  Serial.println("⚠️ 開始清除整顆 ISD1700...");
  
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

  Serial.println("✅ 已完成全清除與重置");
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

  Serial.print("📍 放音指針地址：0x");
  Serial.println(pointer, HEX);
  return pointer;
}

bool isPlaying() {
  digitalWrite(SS_Pin, LOW);
  delayMicroseconds(5);

  SPI.transfer(0x05);     // RD_STATUS 指令
  SPI.transfer(0x00);     // 第二 byte 固定

  byte sr0 = SPI.transfer(0x00);  // SR0（可略過）
  byte sr1 = SPI.transfer(0x00);  // SR1（我們要用這個）

  digitalWrite(SS_Pin, HIGH);

  bool playing = (sr1 & 0b00000100);  // bit2 = 1 表示正在播放

  Serial.print("播放狀態：");
  Serial.println(playing ? "正在播放 🎵" : "未播放 💤");

  return playing;
}
