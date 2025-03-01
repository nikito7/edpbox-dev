#ifndef _HAN_ESP32_H_
#define _HAN_ESP32_H_

// edit > include/tasmota_configurations_ESP32
// ..
// [tasmota32.bin]
// ..
//  #include ../han_esp32.h

#undef USE_ENHANCED_GUI_WIFI_SCAN
#undef USE_TIMERS_WEB
#undef USE_AUTOCONF

#if defined(USE_HAN_V2) && defined(ESP32C6)
#undef USE_TASMOTA_DISCOVERY
#endif

#ifdef ESP32C6
#undef USE_SHT
#undef USE_VEML6070 // UV sensor with conflicting I2C address
#undef USE_AHT1x
#undef USE_AHT2x
#define USE_AHT2x
#endif

// ### ### ###

#endif // _HAN_ESP32_H_
