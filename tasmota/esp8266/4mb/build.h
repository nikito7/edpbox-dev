// .ini
// board = esp8266_4M2M

// user_config_override.h

// ufs

#define USE_UFILESYS
#define UFSYS_SIZE 8192

// user_config_override.h
// sml configs

#undef USE_RULES
#define USE_SCRIPT
#define USE_SML_M
#define USE_SML_SCRIPT_CMD
#define SML_MAX_VARS 50
#define SML_REPLACE_VARS

// tcp

//#define USE_TCP_BRIDGE

// misc

#define USE_SCRIPT_WEB_DISPLAY
#define USE_SCRIPT_JSON_EXPORT
#define MAX_METERS 2
#define MAXSVARS 10

// eof
