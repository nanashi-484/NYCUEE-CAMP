# NYCUEE-CAMP
電擊營 Final Project - 按鈕控制系統

## 專案概述
這是一個基於 Arduino 的按鈕控制系統，結合了按鈕控制、OLED 顯示等功能。系統可以透過按鈕操作進行指令輸入，並提供即時的狀態顯示。

## 系統架構

### 主要版本
- **main**: 具備按鈕控制和 OLED 顯示功能的主控制系統
- **test**: 早期的測試版本，支援感測器觸發功能

## 功能模組說明

### 1. 控制系統 (`main/`)

#### 指令處理邏輯 (`Command_logic.h`)
- **模式管理**:
  - `COMMUNICATION`: 處理指令傳輸模式
  - `WAITING_COMMAND`: 等待使用者輸入模式
- **指令執行**: 
  - `sendCommand()`: 執行當前指令並切換回等待模式
  - `receiveCommand()`: 接收按鈕輸入並設定指令

### 2. 人機介面系統

#### OLED 顯示控制 (`OLED_control.h`)
- **功能**: 即時顯示系統狀態和指令資訊
- **顯示模式**:
  - `COMMUNICATION 模式`: 顯示 "Sending..." 和當前指令
  - `WAITING_COMMAND 模式`: 顯示 "Ready!" 狀態
- **指令轉換**: `CommandToText()` 將指令代碼轉換為可讀文字
- **使用庫**: U8g2lib (128x64 SSD1306)

#### 按鈕輸入處理 (`Button_read.h`)
- **功能**: 多按鈕輸入與長短按檢測
- **按鈕配置**: 6 個按鈕 (腳位: 2, 4, 6, 7, 8, 9)
- **按鈕映射**:
  - 短按: PLAY, -, -, ERASE, FWD, RESET
  - 長按: G_PLAY, REC, -, G_ERASE, -, -
- **長按檢測**: 1000ms 長按門檻
- **狀態管理**: 
  - `button_shortPress[]`: 短按狀態
  - `button_longPress_Detected[]`: 長按檢測
  - `Button_longPress_Hendeled[]`: 長按處理狀態

### 3. 系統控制架構

#### 全域定義 (`Global_define.h`)
- **模式枚舉**: `COMMUNICATION`, `WAITING_COMMAND`
- **指令枚舉**: `PLAY`, `G_PLAY`, `REC`, `ERASE`, `G_ERASE`, `FWD`, `RESET`, `NULL_COMMAND`
- **按鈕參數**: 按鈕腳位、數量、長按時間設定
- **工具函數**: 
  - `serialRead()`: 序列埠整數讀取
  - `concatenateStrings()`: 字串連接
  - `SerialPrintByte()`: 位元組列印

#### 主程式流程 (`main.ino`)
```cpp
void loop(){
  if (mode == COMMUNICATION){
    updateOLED();      // 更新顯示
    sendCommand();     // 發送指令
    delay(1000);
  }
  if (mode == WAITING_COMMAND){
    ReadButton();      // 讀取按鈕
    updateOLED();      // 更新顯示
    receiveCommand();  // 接收指令
    delay(100);
  }
}
```

### 4. 感測器系統 (`test/`)

#### 感測器觸發功能 (`test.ino`)
- **光敏電阻** (A0): 檢測環境光線變化
- **電位器** (A1): 手動調節觸發
- **按鈕** (2): 直接觸發
- **觸發條件**:
  - 光感 > 800: 觸發功能 3
  - 電位器 > 600: 觸發功能 2
  - 按鈕按下: 觸發功能 1

## 硬體連接

### 人機介面
- **按鈕**: 2, 4, 6, 7, 8, 9 (內建上拉電阻)
- **OLED**: I2C 介面 (SDA, SCL)

### 感測器 (測試版本)
- **光敏電阻**: A0
- **電位器**: A1
- **觸發按鈕**: 2

## 使用說明

### 按鈕控制系統操作
1. **系統初始化**: 上電後自動執行初始化和 OLED 顯示
2. **指令輸入**: 
   - 短按按鈕: 執行對應的短按指令
   - 長按按鈕: 執行對應的長按指令
3. **指令功能**:
   - PLAY: 播放功能
   - G_PLAY: 全域播放功能
   - REC: 錄製功能
   - ERASE: 擦除功能
   - G_ERASE: 全域擦除功能
   - FWD: 前進功能
   - RESET: 系統重置

### 系統狀態監控
- **OLED 顯示**: 即時顯示當前模式和執行指令
- **序列埠輸出**: 偵錯資訊和狀態回報

### 測試模式操作
1. 調整光線或電位器觸發對應功能
2. 按下按鈕觸發對應功能
3. 觀察序列埠輸出確認感測器數值

## 開發環境
- **Arduino IDE**
- **依賴庫**: Wire, U8g2lib
- **目標板**: Arduino Uno/Nano
- **通訊協定**: I2C, UART

## 技術特點
- **模組化設計**: 功能分離，便於維護和擴展
- **狀態機架構**: 清晰的模式切換邏輯
- **按鈕去彈跳**: 穩定的長短按檢測
- **即時反饋**: OLED 和序列埠雙重狀態顯示

## 作者
NYCUEE 電擊營專題組
