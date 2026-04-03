/**
 * Waveshare ESP32-S3-Touch-LCD-1.28 圆形触摸屏手表
 * 使用 LovyanGFX 库驱动 GC9A01A 圆形屏
 * LovyanGFX 直接调用 ESP-IDF SPI 驱动，绕开 Arduino SPI 封装层的冲突问题
 */
#include <Arduino.h>
#include <LovyanGFX.hpp>

// ========== LovyanGFX 板子配置 ==========
class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_GC9A01  _panel_instance;
    lgfx::Bus_SPI       _bus_instance;
    lgfx::Light_PWM     _light_instance;

public:
    LGFX(void) {
        // SPI 总线配置
        {
            auto cfg = _bus_instance.config();
            cfg.spi_host = SPI2_HOST;   // ESP32-S3 上 GPIO10/11/12 是 SPI2 的原生引脚
            cfg.spi_mode = 0;
            cfg.freq_write = 40000000;  // 写入 40MHz
            cfg.freq_read  = 16000000;  // 读取 16MHz
            cfg.spi_3wire  = true;      // 单向 MOSI，不用 MISO
            cfg.use_lock   = true;
            cfg.dma_channel = SPI_DMA_CH_AUTO;
            cfg.pin_sclk = 10;
            cfg.pin_mosi = 11;
            cfg.pin_miso = 12;
            cfg.pin_dc   =  8;          // 数据/命令选择
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        // 显示面板配置
        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs   =  9;          // SPI 片选
            cfg.pin_rst  = 14;          // 复位
            cfg.pin_busy = -1;          // 无忙信号引脚
            cfg.memory_width  = 240;
            cfg.memory_height = 240;
            cfg.panel_width   = 240;
            cfg.panel_height  = 240;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.invert = true;          // GC9A01A 需要颜色反转
            cfg.rgb_order = false;
            cfg.readable  = false;
            _panel_instance.config(cfg);
        }
        // 背光配置（PWM 控制）
        {
            auto cfg = _light_instance.config();
            cfg.pin_bl = 2;             // 背光引脚
            cfg.invert = false;
            cfg.freq   = 44100;
            cfg.pwm_channel = 7;
            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }
        setPanel(&_panel_instance);
    }
};

// ========== 全局对象 ==========
LGFX tft;

// ========== 初始化 ==========
void setup() {
    Serial.begin(115200);
    Serial.println("[Watch] 启动中...");

    tft.init();
    tft.setRotation(0);
    Serial.println("[Watch] LCD 初始化完成");

    // 颜色测试
    Serial.println("[Watch] 颜色测试...");
    tft.fillScreen(TFT_RED);
    Serial.println("[Watch] 红色");
    delay(1000);

    tft.fillScreen(TFT_GREEN);
    Serial.println("[Watch] 绿色");
    delay(1000);

    tft.fillScreen(TFT_BLUE);
    Serial.println("[Watch] 蓝色");
    delay(1000);

    // 显示文字
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(middle_center);
    tft.setTextSize(2);
    tft.drawString("Hello!", 120, 100);
    tft.drawString("ESP32-S3 Watch", 120, 135);
    Serial.println("[Watch] 启动完成！");
}

// ========== 主循环 ==========
void loop() {
    delay(1000);
}
