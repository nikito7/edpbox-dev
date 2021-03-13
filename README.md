# Info

Aos novos utilizadores, ler primeiro: [tiagofreire-pt](https://github.com/tiagofreire-pt/Home_Assistant_EDP_Box)

# Tasmota 9.x

```c
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
```

# Links

- [tiagofreire-pt](https://github.com/tiagofreire-pt/Home_Assistant_EDP_Box)

- [tasmota smi](https://tasmota.github.io/docs/Smart-Meter-Interface/)

- [forum](https://forum.cpha.pt/t/integrar-contadores-inteligentes-da-edp-em-home-assistant/4953/)
