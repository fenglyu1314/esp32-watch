# ESP32-S3 圆形触摸屏手表

基于 **Waveshare ESP32-S3-Touch-LCD-1.28** 的智能手表项目。
搭载 1.28 英寸 IPS 圆形触摸屏、六轴 IMU、Wi-Fi / BLE，使用 Arduino 框架 + PlatformIO 开发。

---

## 📋 硬件规格

| 项目         | 参数                                      |
| ------------ | ----------------------------------------- |
| 主控芯片     | ESP32-S3R2，Xtensa LX7 双核，240 MHz      |
| 无线         | 2.4GHz Wi-Fi (802.11 b/g/n) + BLE 5.0    |
| 内存         | 512KB SRAM + 2MB PSRAM + 16MB Flash       |
| 显示屏       | 1.28" IPS 圆形，240×240，65K 色           |
| 显示驱动芯片 | GC9A01A，SPI 接口，最高 80MHz             |
| 触摸芯片     | CST816S，I2C 接口                         |
| IMU 传感器   | QMI8658，3 轴加速度计 + 3 轴陀螺仪        |
| USB 接口     | Type-C（CH343P USB 转 UART 芯片）         |
| 电池接口     | MX1.25 2P，支持 3.7V 锂电池充放电         |

---

## 🔌 板载引脚映射

| GPIO    | 功能             | 说明                              |
| ------- | ---------------- | --------------------------------- |
| GPIO 2  | LCD_BL           | 屏幕背光控制（HIGH = 开）         |
| GPIO 8  | LCD_DC           | SPI 数据/命令选择                 |
| GPIO 9  | LCD_CS           | SPI 片选                          |
| GPIO 10 | LCD_CLK (SCLK)   | SPI 时钟                          |
| GPIO 11 | LCD_MOSI         | SPI 数据输出                      |
| GPIO 12 | LCD_MISO         | SPI 数据输入（一般不用）          |
| GPIO 14 | LCD_RST          | 屏幕复位                          |
| GPIO 6  | I2C SDA          | 触摸（CST816S）+ IMU（QMI8658）   |
| GPIO 7  | I2C SCL          | 触摸（CST816S）+ IMU（QMI8658）   |
| GPIO 5  | TP_INT           | 触摸中断                          |
| GPIO 13 | TP_RST           | 触摸复位                          |
| GPIO 1  | BAT_ADC          | 电池电压检测（ADC，分压 200K+100K）|
| GPIO 15-18, 21 | SH1.0 扩展 GPIO | 可配置为 I2C / SPI / UART 等 |

> **注意**：所有引脚均已集成在开发板上，**无需外部接线**，直接烧录程序即可运行。

---

## 📦 依赖库

| 库名              | 版本       | 用途                                       |
| ----------------- | ---------- | ------------------------------------------ |
| LovyanGFX         | ^1.1.16    | GC9A01A 圆形屏 LCD 驱动（当前使用）        |
| LVGL（可选）      | ^8.3.10    | 高级图形 UI 框架（需要配合 LovyanGFX 使用）|

> **为什么不用 TFT_eSPI？**
> TFT_eSPI 在 ESP32-S3 + Arduino-ESP32 v2.x 组合下，与 Arduino 全局 SPI 对象存在总线冲突，
> 导致 SPI 数据无法发送到屏幕（表现为程序运行正常但屏幕始终无显示）。
> LovyanGFX 直接调用 ESP-IDF 底层 SPI 驱动，完全绕开此问题，是目前最可靠的方案。

---

## 🛠️ 开发环境配置

### 所需工具

1. **VS Code** — 代码编辑器
2. **PlatformIO IDE 扩展** — 项目构建 / 烧录 / 库管理（VSCode 插件）
3. **CH343P USB 驱动** — 开发板 USB 转串口芯片驱动

### 安装步骤详见本文件末尾的「⚙️ 开发环境搭建指南」章节

---

## 🚀 快速开始

1. **打开项目**
   - 用 VS Code 打开本项目文件夹
   - PlatformIO 会自动识别 `platformio.ini` 并配置环境

2. **等待依赖下载**
   - 首次打开时，PlatformIO 会自动下载 ESP32-S3 工具链和依赖库
   - 在底部状态栏可以看到进度（可能需要 5~15 分钟，取决于网速）

3. **连接开发板**
   - 用 USB Type-C 线连接开发板与电脑
   - 开发板接入后，Windows 设备管理器中会出现新的 COM 口

4. **编译项目**
   - 点击 VS Code 底部状态栏的 **✓（Build）** 按钮
   - 或在终端执行：`pio run`

5. **烧录到开发板**
   - 点击底部状态栏的 **→（Upload）** 按钮
   - 或在终端执行：`pio run --target upload`

6. **查看串口输出**
   - 点击底部状态栏的 **🔌（Monitor）** 按钮
   - 或在终端执行：`pio device monitor`

---

## ⚙️ 开发环境搭建指南

### 第一步：安装 CH343P USB 驱动

本开发板使用 **CH343P** USB 转串口芯片（沁恒 WCH 出品）。
需要安装对应驱动，电脑才能识别到 COM 口。

1. 下载驱动（任选其一）：
   - **WCH 官网**（国内可能打不开）：[http://www.wch.cn/download/CH343SER_EXE.html](http://www.wch.cn/download/CH343SER_EXE.html)
   - **Adafruit CDN 镜像**（推荐，稳定可访问）：[https://cdn-learn.adafruit.com/assets/assets/000/120/907/original/CH343SER.ZIP](https://cdn-learn.adafruit.com/assets/assets/000/120/907/original/CH343SER.ZIP?1683669881)
2. 解压后运行 `SETUP.EXE`，在弹出窗口点击「INSTALL」
3. 用 USB Type-C 线连接开发板，打开「设备管理器」→「端口（COM 和 LPT）」
   应能看到类似 `USB-Enhanced-SERIAL CH343 (COM3)` 的条目

### 第二步：安装 VS Code

前往 [https://code.visualstudio.com](https://code.visualstudio.com) 下载并安装 VS Code。

### 第三步：安装 PlatformIO IDE 扩展

1. 打开 VS Code，点击左侧「扩展」图标（或按 `Ctrl+Shift+X`）
2. 搜索 `PlatformIO IDE`，点击「安装」
3. 安装完成后 VS Code 底部会出现 PlatformIO 的工具栏图标
4. **首次安装需要等待 PlatformIO Core 自动下载**（约 5~10 分钟）

### 第四步：打开项目并编译

1. 用 VS Code 打开 `esp32-watch` 文件夹（File → Open Folder）
2. PlatformIO 自动识别到 `platformio.ini`，开始下载 ESP32-S3 工具链（首次约 10 分钟）
3. 下载完成后点击底部 **✓** 按钮编译，出现 `SUCCESS` 表示成功

### 进入烧录模式（如果自动烧录失败）

开发板支持自动下载，通常不需要手动操作。
如果自动烧录失败，可手动进入下载模式：

> **长按 BOOT 按键 → 同时按下 RESET → 松开 RESET → 再松开 BOOT**
> 此时设备进入下载模式，再点击「Upload」按钮上传程序。

---

## ❓ 常见问题

### 找不到 COM 口 / 设备管理器没有新端口
- 检查 CH343P 驱动是否已正确安装
- 换一根 USB 线（部分数据线只能充电，不能传输数据）
- 重新拔插 USB

### 编译失败 / 找不到库
- 确保 PlatformIO 已完成初始化和工具链下载
- 在终端执行 `pio pkg update` 更新依赖

### 烧录失败（连接超时）
- 手动进入烧录模式（见上方「进入烧录模式」步骤）
- 检查 `platformio.ini` 中 `upload_port` 是否与实际 COM 口一致

### 屏幕不亮 / 显示异常
- 检查 LovyanGFX 的 `LGFX` 类中 `cfg.pin_bl = 2` 是否正确（背光引脚）
- 确认 `cfg.invert = true`——GC9A01A 必须开启颜色反转，否则颜色全部错误
- 确认 `cfg.spi_host = SPI2_HOST`——GPIO 10/11/12 是 ESP32-S3 上 SPI2 的原生引脚

### 程序一直复位 / COM 口闪烁
- Flash 为空时可能导致 USB 不稳定，手动进入烧录模式后重新烧录固件即可

### PlatformIO 首次下载非常慢（国内网络）
- 通过 Windows 系统环境变量设置代理可解决：
  - 变量名 `HTTP_PROXY`，变量值 `http://代理IP:端口`
  - 变量名 `HTTPS_PROXY`，变量值 `http://代理IP:端口`
  - 设置完全关闭 VSCode 再重新打开生效

---

## 🗒️ 关键技术笔记

### 为什么平台版本锁定为 `espressif32@6.6.0`？

Waveshare 官方示例要求 Arduino-ESP32 **v2.0.12**。`espressif32@6.6.0` 对应 Arduino-ESP32 v2.0.14，是功能完全兼容的最近稳定版。
**不要升级到 `espressif32@6.7+`**，这些版本对应 Arduino-ESP32 v3.x，API 有破坏性变更，与 v2.x 时代的库不兼容。

### LovyanGFX 在 ESP32-S3 上的关键配置

```cpp
auto cfg = _bus_instance.config();
cfg.spi_host = SPI2_HOST;   // GPIO10/11/12 是 SPI2 的原生引脚，必须指定
cfg.spi_3wire = true;       // 只用 MOSI，不需要 MISO
```

```cpp
auto cfg = _panel_instance.config();
cfg.invert = true;          // GC9A01A 必须开启，否则颜色完全错误
```

### `ARDUINO_USB_CDC_ON_BOOT` 的坑

ESP32-S3 有两路串口：
- **UART0**（通过 CH343P 芯片转 USB，就是 COM 口）
- **内置 USB CDC**（芯片原生 USB）

当 `ARDUINO_USB_CDC_ON_BOOT=1` 时，`Serial` 输出重定向到内置 USB，监视 COM 口看不到任何输出。
本项目使用 CH343P，必须设置 `ARDUINO_USB_CDC_ON_BOOT=0`。

### 官方参考资料

- Waveshare Wiki：https://www.waveshare.net/wiki/ESP32-S3-Touch-LCD-1.28
- LovyanGFX 文档：https://github.com/lovyan03/LovyanGFX
- GC9A01A 数据手册：https://www.waveshare.net/w/upload/5/5e/GC9A01A.pdf
- CST816S 数据手册：https://www.waveshare.net/w/upload/c/c2/CST816S_DS_V1.1.01.pdf
