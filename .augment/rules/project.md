# 项目规则

## 语言规范

- **默认使用中文**回复和编写注释
- 代码中的变量名、函数名、类名等标识符使用英文
- 专业术语（如 SPI、PWM、GPIO、DMA 等）可直接使用英文缩写，无需翻译
- 代码注释尽量用中文，解释清楚意图和注意事项

---

## 硬件环境

- **开发板**：Waveshare ESP32-S3-Touch-LCD-1.28（圆形触摸屏手表）
- **主控芯片**：ESP32-S3
- **显示屏**：GC9A01A，240×240 圆形屏，通过 SPI 驱动
- **通信接口**：SPI2_HOST，SCLK=GPIO10，MOSI=GPIO11，MISO=GPIO12，DC=GPIO8，CS=GPIO9，RST=GPIO14
- **背光**：PWM 控制，引脚 GPIO2
- **串口调试**：UART0（CH343P 转 COM 口），波特率 115200

---

## 软件环境

- **开发框架**：PlatformIO + Arduino framework
- **平台版本**：`espressif32@6.6.0`（对应 Arduino-ESP32 v2.0.14，**禁止升级到 6.7+**，v3.x 有破坏性 API 变更）
- **显示库**：LovyanGFX ^1.1.16（直接调用 ESP-IDF SPI，绕开 Arduino SPI 冲突）
- **上传速度**：921600
- **USB CDC**：`ARDUINO_USB_CDC_ON_BOOT=0`，Serial 输出到 UART0（COM 口）

---

## 注意事项

- 不使用 TFT_eSPI，`include/User_Setup.h` 为历史遗留占位文件，忽略即可
- 修改平台依赖版本前必须确认与 Arduino-ESP32 v2.x API 的兼容性
- 串口调试用 COM 口 + 串口监视器，不走内置 USB CDC
