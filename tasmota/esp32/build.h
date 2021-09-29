// user_config_override.h
// sml configs

#undef USE_RULES
#define USE_SCRIPT
#define USE_SML_M
#define SML_MAX_VARS 100

// tcp

#define USE_TCP_BRIDGE

// misc

#define USE_SCRIPT_WEB_DISPLAY
#define USE_SML_SCRIPT_CMD
#define SML_REPLACE_VARS

// long lines

#define MAX_METERS 1
#define SML_BSIZ 1024
#define TMSBSIZ 2048
#define SML_DUMP_SIZE 1024
#define LARGE_ARRAYS
#define SCRIPT_LARGE_VNBUFF

// eof
