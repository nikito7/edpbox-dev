// copy to user_config_override.h
// (include/tasmota_configurations)
// based in 14.0.0 minimal:
// - freeup ram !

#ifdef ESP8266

// ### ### ###
// raw copy
// no changes

#undef FIRMWARE_LITE                             // Disable tasmota-lite with no sensors
#undef FIRMWARE_SENSORS                          // Disable tasmota-sensors with useful sensors enabled
#undef FIRMWARE_KNX_NO_EMULATION                 // Disable tasmota-knx with KNX but without Emulation
#undef FIRMWARE_DISPLAYS                         // Disable tasmota-display with display drivers enabled
#undef FIRMWARE_IR                               // Disable tasmota-ir with IR full protocols activated

#undef USE_IMPROV                                // Disable support for IMPROV serial protocol as used by esp-web-tools (+2k code)
#undef USE_TASMESH                               // Disable Tasmota Mesh using ESP-NOW (+11k code)
#undef USE_ARDUINO_OTA                           // Disable support for Arduino OTA
#undef USE_INFLUXDB                              // Disable influxdb support (+5k code)
#undef USE_DOMOTICZ                              // Disable Domoticz
#undef USE_HOME_ASSISTANT                        // Disable Home Assistant
#undef USE_TASMOTA_DISCOVERY                     // Disable Tasmota Discovery support (+2k code)
#undef USE_TELEGRAM                              // Disable support for Telegram protocol (+49k code, +7.0k mem and +4.8k additional during connection handshake)
//#undef USE_MQTT_TLS                              // Disable TLS support won't work as the MQTTHost is not set
#undef USE_KNX                                   // Disable KNX IP Protocol Support
//#undef USE_WEBSERVER                             // Disable Webserver
#undef USE_GPIO_VIEWER                           // Disable GPIO Viewer to see realtime GPIO states (+5k6 code)
#undef USE_ENHANCED_GUI_WIFI_SCAN                // Disable wifi scan output with BSSID (+0k5 code)
#undef USE_WEBSEND_RESPONSE                      // Disable command WebSend response message (+1k code)
#undef USE_EMULATION                             // Disable Wemo or Hue emulation
#undef USE_EMULATION_HUE                         // Disable Hue Bridge emulation for Alexa (+14k code, +2k mem common)
#undef USE_EMULATION_WEMO                        // Disable Belkin WeMo emulation for Alexa (+6k code, +2k mem common)
#undef USE_CUSTOM                                // Disable Custom features
#undef USE_DISCOVERY                             // Disable Discovery services for both MQTT and web server
#undef USE_TIMERS                                // Disable support for up to 16 timers
#undef USE_TIMERS_WEB                            // Disable support for timer webpage
#undef USE_SUNRISE                               // Disable support for Sunrise and sunset tools
#undef USE_PING                                  // Disable Ping command (+2k code)
#undef USE_UNISHOX_COMPRESSION                   // Disable support for string compression in Rules or Scripts
#undef USE_RULES                                 // Disable support for rules
#undef USE_SCRIPT                                // Disable support for script

// -- Optional modules ----------------------------
#undef ROTARY_V1                                 // Disable support for MI Desk Lamp
#undef USE_SONOFF_RF                             // Disable support for Sonoff Rf Bridge (+3k2 code)
  #undef USE_RF_FLASH                            // Disable support for flashing the EFM8BB1 chip on the Sonoff RF Bridge. C2CK must be connected to GPIO4, C2D to GPIO5 on the PCB
#undef USE_SONOFF_SC                             // Disable support for Sonoff Sc (+1k1 code)
#undef USE_TUYA_MCU                              // Disable support for Tuya Serial MCU
#undef USE_ARMTRONIX_DIMMERS                     // Disable support for Armtronix Dimmers (+1k4 code)
#undef USE_PS_16_DZ                              // Disable support for PS-16-DZ Dimmer and Sonoff L1 (+2k code)
#undef USE_SONOFF_IFAN                           // Disable support for Sonoff iFan02 and iFan03 (+2k code)
#undef USE_BUZZER                                // Disable support for a buzzer (+0k6 code)
#undef USE_ARILUX_RF                             // Disable support for Arilux RF remote controller
#undef USE_SHUTTER                               // Disable Shutter support for up to 4 shutter with different motortypes (+6k code)
#undef USE_DEEPSLEEP                             // Disable support for deepsleep (+1k code)
#undef USE_EXS_DIMMER                            // Disable support for EX-Store WiFi Dimmer
#undef USE_HOTPLUG                               // Disable support for HotPlug
#undef USE_DEVICE_GROUPS                         // Disable support for device groups (+3k5 code)
#undef USE_PWM_DIMMER                            // Disable support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+4k5 code)
#undef USE_PWM_DIMMER_REMOTE                     // Disbale support for remote switches to PWM Dimmer
#undef USE_KEELOQ                                // Disable support for Jarolift rollers by Keeloq algorithm (+4k5 code)
#undef USE_SONOFF_D1                             // Disable support for Sonoff D1 Dimmer (+0k7 code)
#undef USE_SHELLY_DIMMER                         // Disable support for Shelly Dimmer (+3k code)

// -- Optional light modules ----------------------
#undef USE_LIGHT                                 // Disable support for lights

#undef USE_COUNTER                               // Disable counters
#define USE_ADC_VCC                              // Display Vcc in Power status. Disable for use as Analog input on selected devices
#undef USE_DS18x20                               // Disable DS18x20 sensor

#undef USE_I2C                                   // Disable all I2C sensors and devices
#undef USE_SPI                                   // Disable all SPI devices
#undef USE_DISPLAY                               // Disable Display support

#undef USE_MHZ19                                 // Disable support for MH-Z19 CO2 sensor
#undef USE_SENSEAIR                              // Disable support for SenseAir K30, K70 and S8 CO2 sensor
#undef USE_PMS5003                               // Disable support for PMS5003 and PMS7003 particle concentration sensor
#undef USE_NOVA_SDS                              // Disable support for SDS011 and SDS021 particle concentration sensor
#undef USE_HPMA                                  // Disable support for Honeywell HPMA115S0 particle concentration sensor
#undef USE_SR04                                  // Disable support for HC-SR04 ultrasonic devices (+1k code)
#undef USE_ME007                                 // Disable support for ME007 ultrasonic devices (+1k5 code)
#undef USE_DYP                                   // Disable support for DYP ME-007 ultrasonic distance sensor, serial port version (+0k5 code)
#undef USE_SERIAL_BRIDGE                         // Disable support for software Serial Bridge
#undef USE_MODBUS_BRIDGE                         // Disable support for software Modbus Bridge (+3k code)
#undef USE_TCP_BRIDGE                            // DIsable support for Serial to TCP bridge (+1.3k code)
#undef USE_MP3_PLAYER                            // Disable DFPlayer Mini MP3 Player RB-DFR-562 commands: play, volume and stop
#undef USE_AZ7798                                // Disable support for AZ-Instrument 7798 CO2 datalogger
#undef USE_PN532_HSU                             // Disable support for PN532 using HSU (Serial) interface (+1k8 code, 140 bytes mem)
#undef USE_ZIGBEE                                // Disable serial communication with Zigbee CC2530 flashed with ZNP
#undef USE_RDM6300                               // Disable support for RDM6300 125kHz RFID Reader (+0k8)
#undef USE_IBEACON                               // Disable support for bluetooth LE passive scan of ibeacon devices (uses HM17 module)
#undef USE_GPS                                   // Disable support for GPS and NTP Server for becoming Stratus 1 Time Source (+ 3.1kb flash, +132 bytes RAM)
#undef USE_HM10                                  // (ESP8266 only) Disable support for HM-10 as a BLE-bridge for the LYWSD03 (+5k1 code)
#undef USE_BLE_ESP32                             // (ESP32 only) Disable support for native BLE on ESP32 - use new driver
#undef USE_MI_ESP32                              // (ESP32 only) Disable support for ESP32 as a BLE-bridge (+9k2 mem, +292k flash)
#undef USE_HRXL                                  // Disable support for MaxBotix HRXL-MaxSonar ultrasonic range finders (+0k7)
#undef USE_TASMOTA_CLIENT                        // Disable support for Arduino Uno/Pro Mini via serial interface including flashing (+2k3 code, 44 mem)
#undef USE_OPENTHERM                             // Disable support for OpenTherm (+15k code)
#undef USE_MIEL_HVAC                             // Disable support for Mitsubishi Electric HVAC serial interface (+5k code)
#undef USE_PROJECTOR_CTRL                        // Disable support for LCD/DLP Projector serial control interface
#undef USE_AS608                                 // Disable support for AS608 optical and R503 capacitive fingerprint sensor (+3k4 code)
#undef USE_TFMINIPLUS                            // Disable support for TFmini Plus (TFmini, TFmini-S) LiDAR modules via UART interface (+0k8)
#undef USE_HRG15                                 // Disable support for Hydreon RG-15 Solid State Rain sensor (+1k5 code)
#undef USE_VINDRIKTNING                          // Disable support for IKEA VINDRIKTNING particle concentration sensor (+0k6 code)
#undef USE_LOX_O2                                // Disable support for LuminOx LOX O2 Sensor

#undef USE_ENERGY_SENSOR                         // Disable energy sensors

#undef USE_DHT                                   // Disable support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor
#undef USE_MAX31855                              // Disable MAX31855 K-Type thermocouple sensor using softSPI
#undef USE_MAX31865                              // Disable support for MAX31865 RTD sensors using softSPI
#undef USE_LMT01                                 // Disable support for TI LMT01 temperature sensor, count pulses on single GPIO (+0k5 code)
#undef USE_IR_REMOTE                             // Disable IR driver
#undef USE_TM1638                                // Disable support for TM1638 switches copying Switch1 .. Switch8
#undef USE_HX711                                 // Disable support for HX711 load cell
#undef USE_TX20_WIND_SENSOR                      // Disable support for La Crosse TX20 anemometer
#undef USE_TX23_WIND_SENSOR                      // Disable support for La Crosse TX23 anemometer
#undef USE_WINDMETER                             // Disable support for analog anemometer (+2k2 code)
#undef USE_RC_SWITCH                             // Disable support for RF transceiver using library RcSwitch
#undef USE_RF_SENSOR                             // Disable support for RF sensor receiver (434MHz or 868MHz) (+0k8 code)
#undef USE_HRE                                   // Disable support for Badger HR-E Water Meter (+1k4 code)
#undef USE_A4988_STEPPER                         // Disable support for A4988_Stepper
#undef USE_THERMOSTAT                            // Disable support for Thermostat
#undef USE_PROMETHEUS                            // Disable support for https://prometheus.io/ metrics exporting over HTTP /metrics endpoint
#undef DEBUG_THEO                                // Disable debug code
#undef USE_DEBUG_DRIVER                          // Disable debug code
#undef USE_AC_ZERO_CROSS_DIMMER                  // Disable support for AC_ZERO_CROSS_DIMMER

// ### ### ###

// ifdef ESP8266
#endif

// ### ### ###
// changes 2024.08.17.0109

#ifdef ESP32
#undef USE_ENHANCED_GUI_WIFI_SCAN
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

#ifdef ESP32
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

#define USE_SCRIPT_WEB_DISPLAY
#define USE_GOOGLE_CHARTS
#define USE_SCRIPT_JSON_EXPORT
#define MAXVARS 58
#define MAXSVARS 21
#define MAXFILT 5

#ifdef ESP32
#define LARGE_ARRAYS
#define SCRIPT_LARGE_VNBUFF
#endif

#define USE_HAN_V2

// Default Configs

#ifdef ESP8266
#undef USER_BACKLOG
#define USER_BACKLOG "TimeZone 99; TimeDST 0,0,3,1,1,60; TimeSTD 0,0,10,1,2,0; WebLog 2; SerialLog 0; Sleep 75; WifiPower 15; Template {\"NAME\":\"easyhan.pt\",\"GPIO\":[1,1,1,1,1,1,1,1,1,1,1,1,1,1],\"FLAG\":0,\"BASE\":18}; Module 0; SaveData 9; WifiConfig 2; Script 1"
#undef BOOT_LOOP_OFFSET
#define BOOT_LOOP_OFFSET       3
#else
#define USER_BACKLOG "TimeZone 99; TimeDST 0,0,3,1,1,60; TimeSTD 0,0,10,1,2,0; WebLog 4; WifiPower 15; SaveData 9; WifiConfig 2; Script 1"
#endif

#undef TELE_PERIOD
#define TELE_PERIOD            31

#undef MQTT_TOPIC
#define MQTT_TOPIC             "edpbox99"

#undef WIFI_DEFAULT_HOSTNAME
#define WIFI_DEFAULT_HOSTNAME  "Easy-HAN-EB99"

#undef MQTT_CLIENT_ID
#define MQTT_CLIENT_ID         "Easy_HAN_%06X"

#undef MQTT_USER
#define MQTT_USER "none"

#undef MQTT_PASS
#define MQTT_PASS "none"

#ifdef ESP8266
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
