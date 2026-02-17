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

#undef INFLUXDB_INITIAL
#define INFLUXDB_INITIAL 51

#if defined(USE_HAN_V2) && defined(ESP32C6)
#undef USE_TASMOTA_DISCOVERY
#endif

// ### ### ###

#endif // _HAN_ESP32_H_
