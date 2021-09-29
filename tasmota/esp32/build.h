// user_config_override.h
// sml configs

#undef USE_RULES
#define USE_SCRIPT
#define USE_SML_M
#define SML_MAX_VARS 50

// tcp

#define USE_TCP_BRIDGE

// misc

#define USE_SCRIPT_WEB_DISPLAY
#define USE_SML_SCRIPT_CMD
#define SML_REPLACE_VARS

// long lines

#define MAX_METERS 1
#define SML_BSIZ 256
#define TMSBSIZ 512
#define SML_DUMP_SIZE 512
#define LARGE_ARRAYS
#define SCRIPT_LARGE_VNBUFF

// eof
