// easyhan.pt
// HAN V1 Firmware

#ifdef HAN_V1
#ifndef USE_HAN_V2

#warning **** HAN_V1 ****
#define XDRV_100 100

// This variable will be set to true
// after initialization
bool hDrvInit = false;

void HanInit() {
  AddLog(LOG_LEVEL_INFO, PSTR("HAN_V1: Init..."));

  // Init is successful
  hDrvInit = true;

}  // end HanInit

void HanJson(bool json) {
  //
  if (json) {
    //
  } else {
    // webui

    WSContentSend_PD("{s}<br>{m} {e}");
    WSContentSend_PD("{s}Easy HAN ® V1 {m} {e}");

#ifdef ESP32
    uint16_t cpu_freq = getCpuFrequencyMhz();
    WSContentSend_PD("{s}CPU Freq {m} %d MHz{e}",
                     cpu_freq);
#endif

    if (bitRead(Settings->rule_enabled, 0) == 0) {
      WSContentSend_PD("{s}<br>{m} {e}");
      WSContentSend_PD("{s}Script disabled ! {m} {e}");
    }

    WSContentSend_PD("{s}<br>{m} {e}");

  }  // eof !json

}  // HanJson

// ********************************************
// ********************************************

// main tasmota function

bool Xdrv100(uint32_t function) {
  bool result = false;

  if (FUNC_INIT == function) {
    HanInit();
    AddLog(LOG_LEVEL_INFO, PSTR("HAN_V1: Done !"));
  } else if (hDrvInit) {
    switch (function) {
#ifdef USE_WEBSERVER
      case FUNC_WEB_SENSOR:
        HanJson(false);
        break;
#endif  // USE_WEBSERVER
    }
  }

  return result;
}

#warning **** HAN_V1 End! ****

#endif  // USE_HAN_V2
#endif  // HAN_V1
