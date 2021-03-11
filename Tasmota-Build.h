// copy to user_config_override.h
// tasmota-minimal

#define USE_MQTT_TLS
#define USE_WEBSERVER
#define USE_ENHANCED_GUI_WIFI_SCAN
#define USE_CUSTOM
#define USE_ADC_VCC

// sml configs

#undef USE_RULES
#define USE_SCRIPT
#define USE_SML_M
#define SML_MAX_VARS 50
#define SML_REPLACE_VARS
#define USE_SCRIPT_GLOBVARS
#define USE_SCRIPT_SUB_COMMAND
#define USE_SML_SCRIPT_CMD

// eof
