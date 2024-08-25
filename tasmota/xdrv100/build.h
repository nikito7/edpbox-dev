// copy to user_config_override.h

#ifdef ESP8266
#include "./han_esp8266.h"
#endif

// ### ### ###
// ### ### ###
// changes 2024.08.19.2152

#ifdef ESP32S3
#define USE_LD2410 // radar
#endif

#ifdef ESP32
#undef USE_ENHANCED_GUI_WIFI_SCAN // do not work here
// #define USE_BLE_ESP32
// #define USE_MI_ESP32
#endif

#ifdef ESP8266
#undef USE_FTP
#undef USE_ADC_VCC
#endif

// #define USE_CUSTOM
// #define USE_COUNTER
// #define USE_DS18x20
#define USE_INFLUXDB
#define USE_UNISHOX_COMPRESSION
// #define USE_DEEPSLEEP
// #define TASMOTAMODBUSDEBUG

// ### ### ###
// tasmota-4M

#ifdef ESP8266
#define USE_UFILESYS
#define UFSYS_SIZE 5900
#define GUI_TRASH_FILE
#define GUI_EDIT_FILE
#endif

// ### ### ###
// user_config_override.h
// sml configs

#undef USE_RULES
#define USE_SCRIPT // script or matter!?

#if defined(ESP32) || defined(HAN_V1)
#define USE_SML_M
#define USE_SML_SCRIPT_CMD
#define SML_MAX_VARS 50
#define SML_REPLACE_VARS
#define NO_USE_SML_SPECOPT
#define NO_USE_SML_DECRYPT
#define NO_USE_SML_CANBUS
#endif

// tcp

#if defined(EASYHAN_TCP) || defined(ESP32)
#define USE_TCP_BRIDGE
#define USE_MODBUS_BRIDGE
#define USE_MODBUS_BRIDGE_TCP
#endif

// misc

#if defined(USE_SCRIPT)
#define USE_SCRIPT_WEB_DISPLAY
#define USE_GOOGLE_CHARTS
#define USE_SCRIPT_JSON_EXPORT
#define MAXVARS 58
#define MAXSVARS 21
#define MAXFILT 5
#endif

#if defined(ESP32) && defined(USE_SCRIPT)
#define LARGE_ARRAYS
#define SCRIPT_LARGE_VNBUFF
#endif

#ifndef HAN_V1
//
#define USE_HAN_V2
//
#else
#undef USE_ADC_VCC
#define USE_CUSTOM
#define USE_COUNTER
#define USE_DS18x20
#define USE_INFLUXDB
#define USE_UNISHOX_COMPRESSION
#define USE_SML_TCP
#endif

// Default Configs

#ifdef ESP8266
#undef USER_BACKLOG
#define USER_BACKLOG                                                           \
  "TimeZone 99; TimeDST 0,0,3,1,1,60; TimeSTD 0,0,10,1,2,0; WebLog 2; "        \
  "SerialLog 0; Sleep 75; WifiPower 15; Template "                             \
  "{\"NAME\":\"easyhan.pt\",\"GPIO\":[1,1,1,1,1,1,1,1,1,1,1,1,1,1],\"FLAG\":"  \
  "0,\"BASE\":18}; Module 0; SaveData 9; WifiConfig 2; Script 1"
#undef BOOT_LOOP_OFFSET
#define BOOT_LOOP_OFFSET 3
#else
#define USER_BACKLOG                                                           \
  "TimeZone 99; TimeDST 0,0,3,1,1,60; TimeSTD 0,0,10,1,2,0; WebLog 4; "        \
  "WifiPower 15; SaveData 9; WifiConfig 2; Script 1"
#endif

#undef TELE_PERIOD
#define TELE_PERIOD 31

#undef MQTT_TOPIC
#define MQTT_TOPIC "edpbox99"

#undef WIFI_DEFAULT_HOSTNAME
#define WIFI_DEFAULT_HOSTNAME "Easy-HAN-EB99"

#undef MQTT_CLIENT_ID
#define MQTT_CLIENT_ID "Easy_HAN_%06X"

#undef MQTT_USER
#define MQTT_USER "none"

#undef MQTT_PASS
#define MQTT_PASS "none"

#if defined(ESP8266) && defined(HAN_V1)
#undef OTA_URL
#define OTA_URL "http://u.easyhan.pt/v2/tasmota-4M-v1.bin.gz"
//
#elif ESP8266
#undef OTA_URL
#define OTA_URL "http://u.easyhan.pt/v2/tasmota-4M.bin.gz"
//
#elif ESP32S3
#undef OTA_URL
#define OTA_URL "https://u.easyhan.pt/v2/32/tasmota32s3.bin"
//
#elif ESP32C6
#undef OTA_URL
#define OTA_URL "https://u.easyhan.pt/v2/32/tasmota32c6.bin"
//
#elif ESP32
#undef OTA_URL
#define OTA_URL "https://u.easyhan.pt/v2/32/tasmota32.bin"
#endif

// EOF
