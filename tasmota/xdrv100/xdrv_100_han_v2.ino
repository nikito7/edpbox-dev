// Tasmota HAN Driver for EMI (edpbox)
// easyhan.pt

#ifdef USE_HAN_V2
#ifndef HAN_V1

#warning **** HAN_V2 Driver is included... ****
#define XDRV_100 100

#undef HAN_VERSION_T
#define HAN_VERSION_T "7.256"

#ifdef EASYHAN_TCP
#undef HAN_VERSION
#define HAN_VERSION HAN_VERSION_T "-tcp"
#else
#undef HAN_VERSION
#define HAN_VERSION HAN_VERSION_T
#endif

// This variable will be set to true
// after initialization
bool hDrvInit = false;

// HAN

uint8_t hanCFG = 99;   // def: serial stop bits
uint8_t hanEB = 99;    // def: mono or tri
uint8_t subType = 99;  // def: if meter reply
                       // to L1 L2 L3 in mono.
uint8_t hanERR = 0;
bool hanWork = false;
bool hDiscovery = true;
uint32_t hanDelay = 0;
uint16_t hanDelayWait = 1000;    // 1000:
                                 // Required by e-redes.
uint32_t hanDelayError = 35000;  // Janz GPRS
                                 // need 35000ms.
uint16_t hTimeout = 1500;        // 1500: Some  meters
                                 // are slow to reply.
uint8_t hanIndex = 0;            // 0 = setup
uint32_t hanRead = 0;
uint8_t hanCode = 0;
uint8_t hRestart = 0;

// Clock 01
uint16_t hanYY = 0;
uint8_t hanMT = 0;
uint8_t hanDD = 0;

uint8_t hanHH = 0;
uint8_t hanMM = 0;
uint8_t hanSS = 0;

// Voltage Current 6C
// mono
float hanVL1 = 0;
float hanCL1 = 0;
// tri
float hanVL2 = 0;
float hanCL2 = 0;
float hanVL3 = 0;
float hanCL3 = 0;
float hanCLT = 0;

// Total Energy T (kWh) 26
float hanTET1 = 0;
float hanTET2 = 0;
float hanTET3 = 0;

// Total Energy (kWh) 16
float hanTEI = 0;
float hanTEE = 0;

// Total Energy L1 L2 L3 (kWh) 1C
float hTEIL1 = 0;
float hTEIL2 = 0;
float hTEIL3 = 0;

// Active Power Import/Export 73
// tri
uint32_t hanAPI1 = 0;
uint32_t hanAPE1 = 0;
uint32_t hanAPI2 = 0;
uint32_t hanAPE2 = 0;
uint32_t hanAPI3 = 0;
uint32_t hanAPE3 = 0;
// mono / tri total. (79)
uint32_t hanAPI = 0;
uint32_t hanAPE = 0;

// Power Factor (7B) / Frequency (7F)
float hanPF = 0;
float hanPF1 = 0;
float hanPF2 = 0;
float hanPF3 = 0;
float hanFR = 0;

// Load Profile

uint16_t hLP1YY = 0;
uint8_t hLP1MT = 0;
uint8_t hLP1DD = 0;
uint8_t hLP1HH = 0;
uint8_t hLP1MM = 0;
char hLP1gmt[5];

uint16_t hLP2 = 0;  // tweaked to 16bits

float hLP3 = 0;  // retro compatibility
float hLP4 = 0;  // idem
float hLP6 = 0;  // idem

uint8_t hLPid[9];
uint32_t hLPval[9];

uint32_t hLPX[2];

// Misc

float hCT1 = 0;
float hCT4 = 0;
uint8_t hTariff = 0;

char hErrTime[12];
char hErrCode[8];

char hStatus[12];
uint32_t hPerf[2] = {0, 0};
uint32_t hMnfC = 0;
uint16_t hMnfY = 0;
char hFw1[12];
char hFw2[12];
char hFw3[12];

uint8_t nsMo = 99;
float nsIkw = 0;
float nsEkw = 0;
float nsQs = 0;

uint32_t hWtdT = 0;

uint8_t hNick = 0;
int32_t hFreeDS = 0;

// **********************

#include <ModbusMaster.h>

#ifdef ESP8266
#undef HAN_DIR
#define HAN_DIR 16
#undef HAN_SERIAL
#define HAN_SERIAL Serial
//
#elif ESP32S3
#undef HAN_DIR
#define HAN_DIR 16
#undef HAN_TX
#define HAN_TX 15
#undef HAN_RX
#define HAN_RX 17
#undef HAN_SERIAL
#define HAN_SERIAL Serial1  // Serial2 used by radar
//
#elif ESP32C6
#undef HAN_DIR
#define HAN_DIR 3
#undef HAN_TX
#define HAN_TX 5
#undef HAN_RX
#define HAN_RX 4
#undef HAN_SERIAL
#define HAN_SERIAL Serial1
//
#elif ESP32
#undef HAN_DIR
#define HAN_DIR 18
#undef HAN_TX
#define HAN_TX 16
#undef HAN_RX
#define HAN_RX 17
#undef HAN_SERIAL
#define HAN_SERIAL Serial1
//
#endif

ModbusMaster node;

void preTransmission() { digitalWrite(HAN_DIR, 1); }
void postTransmission() { digitalWrite(HAN_DIR, 0); }

void hanBlink() {
//
#ifdef ESP8266
  digitalWrite(2, LOW);
  delay(50);
  digitalWrite(2, HIGH);
//
#elif ESP32C6
  digitalWrite(2, HIGH);
  delay(50);
  digitalWrite(2, LOW);
//
#elif ESP32S3
  digitalWrite(39, LOW);
  delay(50);
  digitalWrite(39, HIGH);
//
#endif
}

void netSaldo() {
  //
  if (nsIkw == 0) {
    nsIkw = hanTEI;
  }

  if (nsEkw == 0) {
    nsEkw = hanTEE;
  }

  if ((hanMM % 15 == 0) & (hanMM != nsMo) &
      (hanTEI != 0)) {
    nsIkw = hanTEI;
    nsEkw = hanTEE;
    nsMo = hanMM;
  }

  nsQs = hanTEI - hanTEE - nsIkw + nsEkw;
}

void freeDS() {
  //
  int32_t ape = hanAPE;
  int32_t api = hanAPI;
  hFreeDS = api - ape;
  //
  char _dst[30];
  char _dsm[120];
  //
  snprintf_P(_dst, sizeof(_dst),
             PSTR("freeds/edpbox%d/SENSOR"), hNick);

  snprintf_P(_dsm, sizeof(_dsm),
             PSTR(""
                  "{\"Time\":\"%s\","
                  "\"ENERGY\":{"
                  "\"Voltage\":%d,"
                  "\"Power\":%d,"
                  "\"Import\":%d,"
                  "\"Export\":%d"
                  "}}"
                  ""),
             GetDT(Rtc.local_time).c_str(),
             (uint16_t)hanVL1, hFreeDS, hanAPI, hanAPE);

  //

  MqttPublishPayload(_dst, _dsm, 0,
                     false);  // retain = true

}  // freeDS

void setDelayError(uint8_t hanRes) {
  sprintf(hStatus, "Error");
  hanCode = hanRes;
  //
  hanDelay = hanDelayError;
  //
  sprintf(hErrTime, "%02d:%02d:%02d", hanHH, hanMM,
          hanSS);
  sprintf(hErrCode, "0x%02X", hanCode);
  //
}

// ###

void HanDiscovery() {
  //
  char _topic[100];
  char _msg[768];

  AddLog(LOG_LEVEL_INFO, PSTR("HAN: Discovery..."));

  char _file[20];
  char _settings[1];

  snprintf_P(_file, sizeof(_file), PSTR("id.txt"));

  if (TfsLoadFile(_file, (uint8_t *)&_settings,
                  sizeof(_settings))) {
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: %s found: [%d]"),
           _file, _settings[0] - 48);
    hNick = (uint8_t)_settings[0] - 48;
  } else {
    hNick = hanEB;
  }

  //
  for (size_t i = 1; i <= 2; i++) {
    //

    // firmware
    if (i == 1) {
      snprintf_P(_topic, sizeof(_topic),
                 PSTR("homeassistant/sensor/nikito7-EB%d/"
                      "fw/config"),
                 hNick);

      snprintf_P(
          _msg, sizeof(_msg),
          PSTR(""
               "{\"name\":\"ESP Firmware\","
               "\"uniq_id\":\"EB%d_ESP_FW\","
               "\"stat_t\":\"tele/edpbox%d/SENSOR\","
               "\"val_tpl\":\""
               "{%% if value_json.EB%d is defined %%}"
               "{%% if value_json.EB%d.FW is defined %%}"
               "{{ value_json.EB%d.FW|string }}"
               "{%% else %%}"
               "{{ states('sensor.eb%d_esp_firmware') }} "
               "{%% endif %%}"
               "{%% endif %%}\","
               "\"ic\":\"mdi:chip\","
               "\"dev\":{"
               "\"ids\":\"nikito7-EB%d\","
               "\"name\":\"EB%d\"}}"
               ""),
          hNick, hNick, hanEB, hanEB, hanEB, hNick, hNick,
          hNick);
    }  // 1

    // fake_solar freeds
    if (i == 2) {
      snprintf_P(_topic, sizeof(_topic),
                 PSTR("freeds/fake_solar/SENSOR"));

      snprintf_P(_msg, sizeof(_msg),
                 PSTR(""
                      "{\"Time\":\"%s\","
                      "\"ENERGY\":{\"Pv1Current\":0,"
                      "\"Pv2Current\":0,"
                      "\"Pv1Voltage\":0,"
                      "\"Pv2Voltage\":0,"
                      "\"Pv1Power\":0,"
                      "\"Pv2Power\":0,"
                      "\"Today\":0,"
                      "\"Power\":300,"
                      "\"Temperature\":0"
                      "}}"
                      ""),
                 GetDT(Rtc.local_time).c_str());
    }  // 2

    // publish

    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Publish [%d]"), i);
    MqttPublishPayload(_topic, _msg, 0,
                       true);  // retain = true

  }  // end for

  // end
  hDiscovery = false;
}  // HanDiscovery

// ###

void HanInit() {
  AddLog(LOG_LEVEL_INFO, PSTR("HAN: Init..."));

#ifdef ESP8266
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
#elif ESP32C6
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
#elif ESP32S3
  pinMode(39, OUTPUT);
  digitalWrite(39, LOW);
#endif

  //

  pinMode(HAN_DIR, OUTPUT);
  digitalWrite(HAN_DIR, LOW);

  //

  if (PinUsed(GPIO_MBR_RX) | PinUsed(GPIO_MBR_TX) |
      PinUsed(GPIO_TCP_RX) | PinUsed(GPIO_TCP_TX)) {
    //
#ifdef ESP8266
    digitalWrite(2, HIGH);
#elif ESP32C6
    digitalWrite(2, LOW);
#elif ESP32S3
    digitalWrite(39, HIGH);
#endif
    //
    AddLog(LOG_LEVEL_INFO,
           PSTR("HAN: Driver disabled. Bridge Mode..."));
  } else {
    //

#ifdef ESP8266
    ClaimSerial();  // Tasmota SerialLog
#endif

    sprintf(hStatus, "Init");
    hanRead = millis() + 5000;
    hWtdT = millis();
    //

    sprintf(hErrTime, "%s", "None");
    sprintf(hErrCode, "%s", "None");

    // Init is successful
    hDrvInit = true;
  }
}  // end HanInit

void HanDoWork(void) {
  //

  uint32_t _millis = millis();

  if (((_millis - hWtdT) > 600000) & (_millis > 300000)) {
    if (hRestart == 1) {
      ESP_Restart();
    }
    hWtdT = _millis;
    hanIndex = 0;
  }

  if ((hDiscovery) && (_millis > 50000)) {
    HanDiscovery();
  }

  //

  if (hanRead + hanDelay < _millis) {
    hanWork = true;
    node.clearTransmitBuffer();
    delay(50);
    node.clearResponseBuffer();
    delay(50);
    node.setTimeout(hTimeout);
  }

  // # # # # # # # # # #
  // EASYHAN MODBUS BEGIN
  // # # # # # # # # # #

  uint8_t hRes;

  // # # # # # # # # # #
  // Setup: Serial
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 0)) {
    //
    // Detect Stop Bits

    node.setTimeout(2000);

    HAN_SERIAL.flush();
    HAN_SERIAL.end();
    delay(250);
#ifdef ESP8266
    HAN_SERIAL.begin(9600, SERIAL_8N1);
#else
    HAN_SERIAL.begin(9600, SERIAL_8N1, HAN_RX, HAN_TX);
#endif
    delay(250);
    node.begin(1, HAN_SERIAL);
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);

    delay(250);

    uint8_t testserial;

    node.clearResponseBuffer();
    testserial = node.readInputRegisters(0x0001, 1);
    if ((testserial == 0x00) | (testserial == 0x81)) {
      hanBlink();
      hanCFG = 1;
      hanIndex++;
      hanDelay = hanDelayWait;
      AddLog(LOG_LEVEL_INFO, PSTR("HAN: *** 8N1 OK ***"));
    } else {
      hanCode = testserial;
      AddLog(LOG_LEVEL_INFO,
             PSTR("HAN: 8N1 Fail. Error %d"), hanCode);
      //
      HAN_SERIAL.flush();
      HAN_SERIAL.end();
      delay(250);
#ifdef ESP8266
      HAN_SERIAL.begin(9600, SERIAL_8N2);
#else
      HAN_SERIAL.begin(9600, SERIAL_8N2, HAN_RX, HAN_TX);
#endif
      delay(250);
      node.begin(1, HAN_SERIAL);
      node.preTransmission(preTransmission);
      node.postTransmission(postTransmission);

      delay(250);
      //
      node.clearResponseBuffer();
      testserial = node.readInputRegisters(0x0001, 1);
      if ((testserial == 0x00) | (testserial == 0x81)) {
        hanBlink();
        hanCFG = 2;
        hanIndex++;
        hanDelay = hanDelayWait;
        AddLog(LOG_LEVEL_INFO,
               PSTR("HAN: *** 8N2 OK ***"));
      } else {
        AddLog(LOG_LEVEL_INFO,
               PSTR("HAN: 8N2 Fail. Error %d"), hanCode);
        setDelayError(testserial);
      }
      //
    }
    //
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Setup: EB
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 1)) {
    //
    // Detect EB Type

    uint8_t testEB = 0xff;
    uint16_t hanDTT = 0;

    testEB = node.readInputRegisters(0x006E, 1);
    if (testEB == node.ku8MBSuccess) {
      //
      hanBlink();
      hanDTT = node.getResponseBuffer(0);
      if (hanDTT > 0) {
        hanEB = 3;
        subType = 3;
        AddLog(LOG_LEVEL_INFO,
               PSTR("HAN: *** EB3 *** %d / %d ***"),
               testEB, hanDTT);
      } else {
        hanEB = 1;
        subType = 3;
        AddLog(LOG_LEVEL_INFO,
               PSTR("HAN: *** EB1 *** %d / %d ***"),
               testEB, hanDTT);
      }
      //
    } else {
      hanEB = 1;
      subType = 1;
      AddLog(LOG_LEVEL_INFO,
             PSTR("HAN: *** EB1 *** %d ***"), testEB);
    }
    hanIndex++;
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Contract
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 2)) {
    hRes = node.readInputRegisters(0x000C, 4);
    if (hRes == node.ku8MBSuccess) {
      hCT1 = (node.getResponseBuffer(1) |
              node.getResponseBuffer(0) << 16) /
             1000.0;
      hCT4 = (node.getResponseBuffer(7) |
              node.getResponseBuffer(6) << 16) /
             1000.0;
      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // LP ID
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 3)) {
    hRes = node.readInputRegisters(0x0080, 1);
    if (hRes == node.ku8MBSuccess) {
      hLPid[1] = node.getResponseBuffer(0) >> 8;
      hLPid[2] = node.getResponseBuffer(0) & 0xFF;
      hLPid[3] = node.getResponseBuffer(1) >> 8;
      hLPid[4] = node.getResponseBuffer(1) & 0xFF;
      hLPid[5] = node.getResponseBuffer(2) >> 8;
      hLPid[6] = node.getResponseBuffer(2) & 0xFF;
      hLPid[7] = node.getResponseBuffer(3) >> 8;
      hLPid[8] = node.getResponseBuffer(3) & 0xFF;

      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // EMI Info
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 4)) {
    hRes = node.readInputRegisters(0x0003, 4);
    if (hRes == node.ku8MBSuccess) {
      hMnfC = node.getResponseBuffer(1) |
              node.getResponseBuffer(0) << 16;
      hMnfY = node.getResponseBuffer(2);

      sprintf(hFw1, "%c%c%c%c%c",
              node.getResponseBuffer(3) >> 8,
              node.getResponseBuffer(3) & 0xFF,
              node.getResponseBuffer(4) >> 8,
              node.getResponseBuffer(4) & 0xFF,
              node.getResponseBuffer(5) >> 8);

      sprintf(hFw2, "%c%c%c%c%c",
              node.getResponseBuffer(5) & 0xFF,
              node.getResponseBuffer(6) >> 8,
              node.getResponseBuffer(6) & 0xFF,
              node.getResponseBuffer(7) >> 8,
              node.getResponseBuffer(7) & 0xFF);

      sprintf(hFw3, "%c%c%c%c%c",
              node.getResponseBuffer(8) >> 8,
              node.getResponseBuffer(8) & 0xFF,
              node.getResponseBuffer(9) >> 8,
              node.getResponseBuffer(9) & 0xFF,
              node.getResponseBuffer(10) >> 8);

      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Clock ( 12 bytes )
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 5)) {
    hPerf[0] = millis();
    hRes = node.readInputRegisters(0x0001, 1);
    if (hRes == node.ku8MBSuccess) {
      hPerf[1] = millis() - hPerf[0];
      hWtdT = millis();  // feed han wtd
      hanYY = node.getResponseBuffer(0);
      hanMT = node.getResponseBuffer(1) >> 8;
      hanDD = node.getResponseBuffer(1) & 0xFF;
      // hanWD = node.getResponseBuffer(2) >> 8;
      hanHH = node.getResponseBuffer(2) & 0xFF;
      hanMM = node.getResponseBuffer(3) >> 8;
      hanSS = node.getResponseBuffer(3) & 0xFF;
      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
      AddLog(LOG_LEVEL_INFO,
             PSTR("HAN: %02d:%02d:%02d !"), hanHH, hanMM,
             hanSS);
      sprintf(hStatus, "OK");
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Voltage Current
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 6)) {
    if (hanEB == 3) {
      hRes = node.readInputRegisters(0x006c, 7);
      if (hRes == node.ku8MBSuccess) {
        hanVL1 = node.getResponseBuffer(0) / 10.0;
        hanCL1 = node.getResponseBuffer(1) / 10.0;
        hanVL2 = node.getResponseBuffer(2) / 10.0;
        hanCL2 = node.getResponseBuffer(3) / 10.0;
        hanVL3 = node.getResponseBuffer(4) / 10.0;
        hanCL3 = node.getResponseBuffer(5) / 10.0;
        hanCLT = node.getResponseBuffer(6) / 10.0;
        hanBlink();
        hanDelay = hanDelayWait;
        hanIndex++;
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    } else {
      hRes = node.readInputRegisters(0x006c, 2);
      if (hRes == node.ku8MBSuccess) {
        hanVL1 = node.getResponseBuffer(0) / 10.0;
        hanCL1 = node.getResponseBuffer(1) / 10.0;
        hanBlink();
        hanDelay = hanDelayWait;
        hanIndex++;
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Active Power Import/Export 73 (tri)
  // Power Factor (mono) (79..)
  // # # # # # # # # # #

  if (hanWork & ((hanIndex == 7) | (hanIndex == 12))) {
    if (hanEB == 3) {
      hRes = node.readInputRegisters(0x0073, 8);
      if (hRes == node.ku8MBSuccess) {
        hanAPI1 = node.getResponseBuffer(1) |
                  node.getResponseBuffer(0) << 16;
        hanAPE1 = node.getResponseBuffer(3) |
                  node.getResponseBuffer(2) << 16;
        hanAPI2 = node.getResponseBuffer(5) |
                  node.getResponseBuffer(4) << 16;
        hanAPE2 = node.getResponseBuffer(7) |
                  node.getResponseBuffer(6) << 16;
        hanAPI3 = node.getResponseBuffer(9) |
                  node.getResponseBuffer(8) << 16;
        hanAPE3 = node.getResponseBuffer(11) |
                  node.getResponseBuffer(10) << 16;
        hanAPI = node.getResponseBuffer(13) |
                 node.getResponseBuffer(12) << 16;
        hanAPE = node.getResponseBuffer(15) |
                 node.getResponseBuffer(14) << 16;
        hanBlink();
        hanDelay = hanDelayWait;
        hanIndex++;
        sprintf(hStatus, "OK");
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    } else {
      hRes = node.readInputRegisters(0x0079, 3);
      if (hRes == node.ku8MBSuccess) {
        hanAPI = node.getResponseBuffer(1) |
                 node.getResponseBuffer(0) << 16;
        hanAPE = node.getResponseBuffer(3) |
                 node.getResponseBuffer(2) << 16;
        hanPF = node.getResponseBuffer(4) / 1000.0;
        hanBlink();
        hanDelay = hanDelayWait;
        hanIndex++;
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    }
    //
    if (!hDiscovery) {
      freeDS();
    }
    //
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Power Factor (7B) / Frequency (7F)
  // Power Factor (tri)
  // Frequency (mono)
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 8)) {
    if (hanEB == 3) {
      hRes = node.readInputRegisters(0x007b, 5);
      if (hRes == node.ku8MBSuccess) {
        hanPF = node.getResponseBuffer(0) / 1000.0;
        hanPF1 = node.getResponseBuffer(1) / 1000.0;
        hanPF2 = node.getResponseBuffer(2) / 1000.0;
        hanPF3 = node.getResponseBuffer(3) / 1000.0;
        hanFR = node.getResponseBuffer(4) / 10.0;
        hanBlink();
        hanDelay = hanDelayWait;
        hanIndex++;
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    } else {
      hRes = node.readInputRegisters(0x007f, 1);
      if (hRes == node.ku8MBSuccess) {
        hanFR = node.getResponseBuffer(0) / 10.0;
        hanBlink();
        hanDelay = hanDelayWait;
        hanIndex++;
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Total Energy Tarifas (kWh) 26
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 9)) {
    hPerf[0] = millis();
    hRes = node.readInputRegisters(0x0026, 3);
    if (hRes == node.ku8MBSuccess) {
      hPerf[1] = millis() - hPerf[0];
      hanTET1 = (node.getResponseBuffer(1) |
                 node.getResponseBuffer(0) << 16) /
                1000.0;
      hanTET2 = (node.getResponseBuffer(3) |
                 node.getResponseBuffer(2) << 16) /
                1000.0;
      hanTET3 = (node.getResponseBuffer(5) |
                 node.getResponseBuffer(4) << 16) /
                1000.0;
      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
      sprintf(hStatus, "OK");
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Total Energy (total) (kWh) 16
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 10)) {
    hRes = node.readInputRegisters(0x0016, 2);
    if (hRes == node.ku8MBSuccess) {
      hanTEI = (node.getResponseBuffer(1) |
                node.getResponseBuffer(0) << 16) /
               1000.0;
      hanTEE = (node.getResponseBuffer(3) |
                node.getResponseBuffer(2) << 16) /
               1000.0;
      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
      //
      netSaldo();
      //
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Total Energy (L1 L2 L3) (kWh) 1C
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 11) & (hanEB == 1)) {
    hanIndex++;
  }

  if (hanWork & (hanIndex == 11)) {
    hRes = node.readInputRegisters(0x001C, 3);
    if (hRes == node.ku8MBSuccess) {
      hTEIL1 = (node.getResponseBuffer(1) |
                node.getResponseBuffer(0) << 16) /
               1000.0;
      hTEIL2 = (node.getResponseBuffer(3) |
                node.getResponseBuffer(2) << 16) /
               1000.0;
      hTEIL3 = (node.getResponseBuffer(5) |
                node.getResponseBuffer(4) << 16) /
               1000.0;
      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Reserved
  // # # # # # # # # # #

  // hanIndex == 12

  // # # # # # # # # # #
  // Load Profile
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 13)) {
    hPerf[0] = millis();
    hRes = node.readLastProfile(0x00, 0x01);
    if (hRes == node.ku8MBSuccess) {
      hPerf[1] = millis() - hPerf[0];
      hLP1YY = node.getResponseBuffer(0);
      hLP1MT = node.getResponseBuffer(1) >> 8;
      hLP1DD = node.getResponseBuffer(1) & 0xFF;

      hLP1HH = node.getResponseBuffer(2) & 0xFF;
      hLP1MM = node.getResponseBuffer(3) >> 8;

      uint8_t tmpGMT = node.getResponseBuffer(5) & 0xFF;

      // tweaked to 16bits. branch: LP1.
      hLP2 = node.getResponseBuffer(6);

      // new

      hLPval[3] = node.getResponseBuffer(8) |
                  node.getResponseBuffer(7) << 16;
      hLPval[4] = node.getResponseBuffer(10) |
                  node.getResponseBuffer(9) << 16;
      hLPval[5] = node.getResponseBuffer(12) |
                  node.getResponseBuffer(11) << 16;
      hLPval[6] = node.getResponseBuffer(14) |
                  node.getResponseBuffer(13) << 16;
      hLPval[7] = node.getResponseBuffer(16) |
                  node.getResponseBuffer(15) << 16;
      hLPval[8] = node.getResponseBuffer(18) |
                  node.getResponseBuffer(17) << 16;

      hLP3 = hLPval[3] / 1000.0;
      hLP4 = hLPval[4] / 1000.0;
      hLP6 = hLPval[6] / 1000.0;

      //

      if (tmpGMT == 0x80) {
        sprintf(hLP1gmt, "01");
      } else {
        sprintf(hLP1gmt, "00");
      }

      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Tariff
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 14)) {
    hRes = node.readInputRegisters(0x000B, 1);
    if (hRes == node.ku8MBSuccess) {
      hTariff = node.getResponseBuffer(0) >> 8;
      hanBlink();
      hanDelay = hanDelayWait;
      hanIndex++;
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // EASYHAN MODBUS EOF
  // # # # # # # # # # #

  if (hanIndex > 14) {
    hanIndex = 5;  // skip setup and one time requests.
  }

  if (hanERR > 90) {
    hanERR = 30;
  }

  // end loop

}  // end HanDoWork

void HanDisabled() {
  WSContentSend_PD("{s}<br>{m} {e}");
  WSContentSend_PD("{s}Easy HAN ® V2 {m}" HAN_VERSION
                   "{e}");
#ifdef ESP32
  uint16_t cpu_freq = getCpuFrequencyMhz();
  WSContentSend_PD("{s}CPU Freq {m} %d MHz{e}", cpu_freq);
#endif

  if (bitRead(Settings->rule_enabled, 0) == 0) {
    WSContentSend_PD("{s}<br>{m} {e}");
    WSContentSend_PD("{s}Script disabled !! {m} {e}");
  }

  WSContentSend_PD("{s}Bridge Mode {m} {e}");

  WSContentSend_PD("{s}<br>{m} {e}");
}

void HanJson(bool json) {
  //
  char hanClock[10];
  sprintf(hanClock, "%02d:%02d:%02d", hanHH, hanMM,
          hanSS);
  //
  if (json) {
    ResponseAppend_P(",\"EB%d\":{", hanEB);
    ResponseAppend_P("\"ErrCode\":\"%s\"", hErrCode);
    ResponseAppend_P(",\"ErrTime\":\"%s\"", hErrTime);
    ResponseAppend_P(",\"ErrCnt\":%d", hanERR);

    ResponseAppend_P(",\"CLK\":\"%s\"", hanClock);
    ResponseAppend_P(",\"HH\":%d", hanHH);
    ResponseAppend_P(",\"MM\":%d", hanMM);
    ResponseAppend_P(",\"SS\":%d", hanSS);

    ResponseAppend_P(",\"VL1\":%1_f", &hanVL1);

    if (hanEB == 3) {
      ResponseAppend_P(",\"VL2\":%1_f", &hanVL2);
      ResponseAppend_P(",\"VL3\":%1_f", &hanVL3);
    }

    ResponseAppend_P(",\"CL1\":%1_f", &hanCL1);

    if (hanEB == 3) {
      ResponseAppend_P(",\"CL2\":%1_f", &hanCL2);
      ResponseAppend_P(",\"CL3\":%1_f", &hanCL3);
      ResponseAppend_P(",\"CL\":%1_f", &hanCLT);
    }

    ResponseAppend_P(",\"API\":%d", hanAPI);
    ResponseAppend_P(",\"APE\":%d", hanAPE);

    if (hanEB == 3) {
      ResponseAppend_P(",\"API1\":%d", hanAPI1);
      ResponseAppend_P(",\"API2\":%d", hanAPI2);
      ResponseAppend_P(",\"API3\":%d", hanAPI3);
      ResponseAppend_P(",\"APE1\":%d", hanAPE1);
      ResponseAppend_P(",\"APE2\":%d", hanAPE2);
      ResponseAppend_P(",\"APE3\":%d", hanAPE3);
    }

    ResponseAppend_P(",\"PF\":%3_f", &hanPF);

    if (hanEB == 3) {
      ResponseAppend_P(",\"PF1\":%3_f", &hanPF1);
      ResponseAppend_P(",\"PF2\":%3_f", &hanPF2);
      ResponseAppend_P(",\"PF3\":%3_f", &hanPF3);
    }

    ResponseAppend_P(",\"FR\":%1_f", &hanFR);

    ResponseAppend_P(",\"TET1\":%3_f", &hanTET1);
    ResponseAppend_P(",\"TET2\":%3_f", &hanTET2);
    ResponseAppend_P(",\"TET3\":%3_f", &hanTET3);

    ResponseAppend_P(",\"TEI\":%3_f", &hanTEI);
    ResponseAppend_P(",\"TEE\":%3_f", &hanTEE);
    ResponseAppend_P(",\"qs\":%3_f", &nsQs);

    if (hanEB == 3) {
      ResponseAppend_P(",\"TEIL1\":%3_f", &hTEIL1);
      ResponseAppend_P(",\"TEIL2\":%3_f", &hTEIL2);
      ResponseAppend_P(",\"TEIL3\":%3_f", &hTEIL3);
    }

    ResponseAppend_P(",\"LP1_Y\":%d", hLP1YY);
    ResponseAppend_P(",\"LP1_M\":%d", hLP1MT);
    ResponseAppend_P(",\"LP1_D\":%d", hLP1DD);
    ResponseAppend_P(",\"LP1_HH\":%d", hLP1HH);
    ResponseAppend_P(",\"LP1_MM\":%d", hLP1MM);
    ResponseAppend_P(",\"LP1_GMT\":\"%s\"", hLP1gmt);

    ResponseAppend_P(",\"LP3_IMP\":%3_f", &hLP3);
    ResponseAppend_P(",\"LP4\":%3_f", &hLP4);
    ResponseAppend_P(",\"LP6_EXP\":%3_f", &hLP6);

    // new LP

    for (uint8_t i = 3; i < 9; i++) {
      if ((hLPid[i] > 2) & (hLPid[i] < 99)) {
        ResponseAppend_P(",\"LPid%d\":%d", hLPid[i],
                         hLPval[i]);
      }
    }

    //

    ResponseAppend_P(",\"CT1\":%2_f", &hCT1);
    ResponseAppend_P(",\"Tariff\":%d", hTariff);
    ResponseAppend_P(",\"FW\":" HAN_VERSION);

    ResponseAppend_P("}");

  } else {
    // webui

    WSContentSend_PD("{s}<br>{m} {e}");
    WSContentSend_PD("{s}Easy HAN ® V2 {m}" HAN_VERSION
                     "{e}");

#ifdef ESP32
    uint16_t cpu_freq = getCpuFrequencyMhz();
    WSContentSend_PD("{s}CPU Freq {m} %d MHz{e}",
                     cpu_freq);
#endif

    if (bitRead(Settings->rule_enabled, 0) == 0) {
      WSContentSend_PD("{s}<br>{m} {e}");
      WSContentSend_PD("{s}Script disabled !! {m} {e}");
    }

    WSContentSend_PD("{s}<br>{m} {e}");

    uint32_t tmpWait =
        ((hanRead + hanDelay) - millis()) / 1000;

    if (tmpWait > 900) {
      tmpWait = 999;
    }

    WSContentSend_PD("{s}MB Status {m} %s %ds {e}",
                     hStatus, tmpWait);

    WSContentSend_PD("{s}MB Index {m} %d {e}", hanIndex);

    if (hanERR > 0) {
      WSContentSend_PD("{s}MB Error Time {m} %s{e}",
                       hErrTime);
      WSContentSend_PD("{s}MB Error Code {m} %s {e}",
                       hErrCode);
      WSContentSend_PD("{s}MB Error Count {m} %d {e}",
                       hanERR);
      WSContentSend_PD("{s}MB Restart {m} %d {e}",
                       hRestart);
      WSContentSend_PD("{s}MB Watchdog {m} %ds {e}",
                       ((millis() - hWtdT) / 1000));
    }  // if hanERR

    WSContentSend_PD("{s}MB Serial {m} 8N%d {e}", hanCFG);
    WSContentSend_PD("{s}MB Type {m} EB%d / %d {e}",
                     hanEB, subType);
    WSContentSend_PD("{s}MB Latency {m} %d ms{e}",
                     hPerf[1]);
    WSContentSend_PD("{s}MB Timeout {m} %d ms{e}",
                     hTimeout);
    WSContentSend_PD("{s}MB Delay Wait {m} %d ms{e}",
                     hanDelayWait);
    WSContentSend_PD("{s}MB Delay Error {m} %d ms{e}",
                     hanDelayError);
    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Clock {m} %s{e}", hanClock);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Voltage L1 {m} %1_f V{e}",
                     &hanVL1);

    if (hanEB == 3) {
      WSContentSend_PD("{s}L2 {m} %1_f V{e}", &hanVL2);
      WSContentSend_PD("{s}L3 {m} %1_f V{e}", &hanVL3);

      WSContentSend_PD("{s}<br>{m} {e}");
      WSContentSend_PD("{s}Current{m} %1_f A{e}",
                       &hanCLT);
    }

    WSContentSend_PD("{s}Current L1 {m} %1_f A{e}",
                     &hanCL1);

    if (hanEB == 3) {
      WSContentSend_PD("{s}L2 {m} %1_f A{e}", &hanCL2);
      WSContentSend_PD("{s}L3 {m} %1_f A{e}", &hanCL3);

      WSContentSend_PD("{s}<br>{m} {e}");
    }

    WSContentSend_PD("{s}Power Import {m} %d W{e}",
                     hanAPI);
    WSContentSend_PD("{s}Power Export {m} %d W{e}",
                     hanAPE);

    if (hanEB == 3) {
      WSContentSend_PD("{s}L1 {m} %d W{e}", hanAPI1);
      WSContentSend_PD("{s}L2 {m} %d W{e}", hanAPI2);
      WSContentSend_PD("{s}L3 {m} %d W{e}", hanAPI3);
      WSContentSend_PD("{s}L1 Export {m} %d W{e}",
                       hanAPE1);
      WSContentSend_PD("{s}L2 Export {m} %d W{e}",
                       hanAPE2);
      WSContentSend_PD("{s}L3 Export {m} %d W{e}",
                       hanAPE3);

      WSContentSend_PD("{s}<br>{m} {e}");
    }

    WSContentSend_PD("{s}Power Factor {m} %3_f φ{e}",
                     &hanPF);

    if (hanEB == 3) {
      WSContentSend_PD("{s}L1 {m} %3_f φ{e}", &hanPF1);
      WSContentSend_PD("{s}L2 {m} %3_f φ{e}", &hanPF2);
      WSContentSend_PD("{s}L3 {m} %3_f φ{e}", &hanPF3);
    }

    WSContentSend_PD("{s}Frequency {m} %1_f Hz{e}",
                     &hanFR);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Energy T1 Vazio {m} %3_f kWh{e}",
                     &hanTET1);
    WSContentSend_PD("{s}Energy T2 Ponta {m} %3_f kWh{e}",
                     &hanTET2);
    WSContentSend_PD(
        "{s}Energy T3 Cheias {m} %3_f kWh{e}", &hanTET3);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD(
        "{s}Energy Total Import {m} %3_f kWh{e}",
        &hanTEI);
    WSContentSend_PD(
        "{s}Energy Total Export {m} %3_f kWh{e}",
        &hanTEE);

    WSContentSend_PD("{s}<br>{m} {e}");

    if (hanEB == 3) {
      WSContentSend_PD(
          "{s}Energy Import L1 {m} %3_f kWh{e}", &hTEIL1);
      WSContentSend_PD("{s}L2 {m} %3_f kWh{e}", &hTEIL2);
      WSContentSend_PD("{s}L3 {m} %3_f kWh{e}", &hTEIL3);

      WSContentSend_PD("{s}<br>{m} {e}");
    }

    WSContentSend_PD(
        "{s}Diagrama de Carga {m} Load Profile{e}");

    WSContentSend_PD("{s}<br>{m} {e}");
    char hLPDate[15];
    sprintf(hLPDate, "%04d-%02d-%02d", hLP1YY, hLP1MT,
            hLP1DD);

    WSContentSend_PD("{s}LP 1 Date {m} %s{e}", hLPDate);

    char hLPClock[15];
    sprintf(hLPClock, "%02d:%02d Z%s", hLP1HH, hLP1MM,
            hLP1gmt);

    WSContentSend_PD("{s}LP 1 Time {m} %s{e}", hLPClock);

    WSContentSend_PD("{s}LP 2 AMR {m} %d{e}", hLP2);

    // new LP

    for (uint8_t i = 3; i < 9; i++) {
      //

      char _name[20];

      if (hLPid[i] == 9) {
        sprintf(_name, "%s", "Import Inc");
      } else if (hLPid[i] == 10) {
        sprintf(_name, "%s", "Export Inc");
      } else {
        sprintf(_name, "%s", "Reactive");
      }

      if ((hLPid[i] > 2) & (hLPid[i] < 99)) {
        WSContentSend_PD("{s}LP %d %s {m} %d Wh{e}",
                         hLPid[i], _name, hLPval[i]);
      }
    }

    //

    char tmpLPid[25];
    sprintf(tmpLPid, "%d %d %d %d %d %d %d %d", hLPid[1],
            hLPid[2], hLPid[3], hLPid[4], hLPid[5],
            hLPid[6], hLPid[7], hLPid[8]);

    WSContentSend_PD("{s}IDs: %s {m} {e}", tmpLPid);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD(
        "{s}Realtime Netmetering (qs) {m} %3_f kWh{e}",
        &nsQs);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Contract T1 {m} %2_f kVA{e}",
                     &hCT1);
    WSContentSend_PD("{s}Contract T4 {m} %2_f kVA{e}",
                     &hCT4);

    char tarifa[10];

    switch (hTariff) {
      case 1:
        sprintf(tarifa, "%s", "Vazio T1");
        break;
      case 2:
        sprintf(tarifa, "%s", "Ponta T2");
        break;
      case 3:
        sprintf(tarifa, "%s", "Cheias T3");
        break;
      default:
        sprintf(tarifa, "%d", hTariff);
    }

    WSContentSend_PD("{s}Tariff {m} %s{e}", tarifa);

    WSContentSend_PD("{s}<br>{m} {e}");

    char _emi[20];

    switch (hMnfC) {
      case 6623491:
        sprintf(_emi, "%s", "T Janz GPRS");
        break;
      case 6750210:
        sprintf(_emi, "%s", "M Landis+Gyr S3");
        break;
      case 6754306:
        sprintf(_emi, "%s", "T Landis+Gyr S3");
        break;
      case 6754307:
        sprintf(_emi, "%s", "T Landis+Gyr S5");
        break;
      case 11010050:
        sprintf(_emi, "%s", "M Sagem CX1000-6");
        break;
      case 11010051:
        sprintf(_emi, "%s", "M Sagem S212");
        break;
      case 11014146:
        sprintf(_emi, "%s", "T Sagem CX2000-9");
        break;
      case 16973825:
        sprintf(_emi, "%s", "? Ziv ???");
        break;
      case 16977920:
        sprintf(_emi, "%s", "T Ziv 5CTD-E2F");
        break;
      case 18481154:
        sprintf(_emi, "%s", "M Kaifa MA109P");
        break;
      case 18481156:
        sprintf(_emi, "%s", "M Kaifa MA109H");
        break;
      default:
        sprintf(_emi, "%s", "? ??? ???");
    }

    WSContentSend_PD("{s}EMI Manufacturer Year {m} %d{e}",
                     hMnfY);

    WSContentSend_PD("{s}EMI %s {m} %d{e}", _emi, hMnfC);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}EMI Firmware: {m} {e}");
    WSContentSend_PD("{s}1. Core {m} %s{e}", hFw1);
    WSContentSend_PD("{s}2. App {m} %s{e}", hFw2);
    WSContentSend_PD("{s}3. Com {m} %s{e}", hFw3);

    WSContentSend_PD("{s}<br>{m} {e}");

  }  // eof !json

}  // HanJson

// ********************************************
// ********************************************

const char HanCommands[] PROGMEM =
    "|"  // No Prefix
    "HanDelay|"
    "HanDelayWait|"
    "HanDelayError|"
    "HanTimeout|"
    "HanRestart|"
    "HanProfile";

void (*const HanCommand[])(void) PROGMEM = {
    &CmdHanDelay,   &CmdHanDelayWait, &CmdHanDelayError,
    &CmdHanTimeout, &CmdHanRestart,   &CmdHanProfile};

//

void CmdHanProfile(void) {
  hanWork = false;
  hanDelay = 15000;

  uint8_t hRes;

  if ((hLPX[0] == 0) | (hLPX[0] < hLPX[1])) {
    //
    node.clearTransmitBuffer();
    delay(100);
    node.clearResponseBuffer();
    delay(100);
    //
    hRes = node.readInputRegisters(0x0082, 2);
    if (hRes == node.ku8MBSuccess) {
      hLPX[0] = (node.getResponseBuffer(1) |
                 node.getResponseBuffer(0) << 16);
      hLPX[1] = (node.getResponseBuffer(3) |
                 node.getResponseBuffer(2) << 16);
      hanBlink();
    }
    delay(500);
  }

  uint16_t hLPX1YY = 0;
  uint8_t hLPX1MT = 0;
  uint8_t hLPX1DD = 0;
  uint8_t hLPX1HH = 0;
  uint8_t hLPX1MM = 0;
  uint8_t hLPX1gmt = 99;

  uint16_t hLPX2 = 0;  // tweaked to 16bits

  uint32_t hLPX3 = 0;
  uint32_t hLPX4 = 0;
  uint32_t hLPX5 = 0;
  uint32_t hLPX6 = 0;
  uint32_t hLPX7 = 0;
  uint32_t hLPX8 = 0;

  uint16_t getLP = 0;
  char resX[50];

  if ((XdrvMailbox.payload >= 1) &&
      (XdrvMailbox.payload <= hLPX[1])) {
    // *****
    getLP = XdrvMailbox.payload;

    node.clearTransmitBuffer();
    delay(100);
    node.clearResponseBuffer();
    delay(100);

    node.setTimeout(2000);

    hRes = node.readProfileX(getLP, 0x00);
    if (hRes == node.ku8MBSuccess) {
      hWtdT = millis();  // feed han wtd
      hLPX1YY = node.getResponseBuffer(0);
      hLPX1MT = node.getResponseBuffer(1) >> 8;
      hLPX1DD = node.getResponseBuffer(1) & 0xFF;

      hLPX1HH = node.getResponseBuffer(2) & 0xFF;
      hLPX1MM = node.getResponseBuffer(3) >> 8;

      hLPX1gmt = node.getResponseBuffer(5) & 0xFF;

      // tweaked to 16bits. branch: LP1.
      hLPX2 = node.getResponseBuffer(6);

      hLPX3 = (node.getResponseBuffer(8) |
               node.getResponseBuffer(7) << 16);
      hLPX4 = (node.getResponseBuffer(10) |
               node.getResponseBuffer(9) << 16);
      hLPX5 = (node.getResponseBuffer(12) |
               node.getResponseBuffer(11) << 16);
      hLPX6 = (node.getResponseBuffer(14) |
               node.getResponseBuffer(13) << 16);
      hLPX7 = (node.getResponseBuffer(16) |
               node.getResponseBuffer(15) << 16);
      hLPX8 = (node.getResponseBuffer(18) |
               node.getResponseBuffer(17) << 16);
      hanBlink();

      char tmpGMT[5];

      if (hLPX1gmt == 0x80) {
        sprintf(tmpGMT, "01");
      } else {
        sprintf(tmpGMT, "00");
      }

      sprintf(resX,
              "%04d,%04d-%02d-%02dT%02d:%02dZ%s,"
              "%02d,%05d,%05d,%05d,%05d",
              getLP, hLPX1YY, hLPX1MT, hLPX1DD, hLPX1HH,
              hLPX1MM, tmpGMT, hLPX2, hLPX3, hLPX4, hLPX5,
              hLPX6);

    } else {
      sprintf(resX, "%04d,Error,Code,%d", getLP, hRes);
    }
    // *****
  } else {
    sprintf(resX,
            "%04d,Error,Limit,%04d,%04d,"
            "ID,%d-%d-%d-%d-%d-%d-%d-%d",
            getLP, hLPX[0], hLPX[1], hLPid[1], hLPid[2],
            hLPid[3], hLPid[4], hLPid[5], hLPid[6],
            hLPid[7], hLPid[8]);
  }

  hanRead = millis();
  hanWork = false;
  //
  sprintf(hStatus, "Cmd");
  ResponseCmndChar(resX);
}

//

void CmdHanDelay(void) {
  if ((XdrvMailbox.payload >= 0) &&
      (XdrvMailbox.payload <= 900)) {
    hanDelay = XdrvMailbox.payload * 1000;
  } else {
    hanDelay = 300000;
  }
  AddLog(LOG_LEVEL_INFO, PSTR("HanDelay: Paused %ds"),
         hanDelay / 1000);
  sprintf(hStatus, "Cmd");
  ResponseCmndDone();
}

//

void CmdHanDelayWait(void) {
  if ((XdrvMailbox.payload >= 100) &&
      (XdrvMailbox.payload <= 60000)) {
    hanDelayWait = XdrvMailbox.payload;
  }
  ResponseCmndNumber(hanDelayWait);
}

//

void CmdHanTimeout(void) {
  if ((XdrvMailbox.payload >= 100) &&
      (XdrvMailbox.payload <= 5000)) {
    hTimeout = XdrvMailbox.payload;
  }
  ResponseCmndNumber(hTimeout);
}
//

void CmdHanRestart(void) {
  if ((XdrvMailbox.payload >= 0) &&
      (XdrvMailbox.payload <= 9)) {
    hRestart = XdrvMailbox.payload;
  }
  ResponseCmndNumber(hRestart);
}
//

void CmdHanDelayError(void) {
  if ((XdrvMailbox.payload >= 1000) &&
      (XdrvMailbox.payload <= 900000)) {
    hanDelayError = XdrvMailbox.payload;
  }
  AddLog(LOG_LEVEL_INFO, PSTR("HanDelayError: %dms"),
         hanDelayError);
  ResponseCmndDone();
}

// main tasmota function

bool Xdrv100(uint32_t function) {
  bool result = false;

  if (FUNC_INIT == function) {
    HanInit();
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Done !"));
  } else if (hDrvInit) {
    switch (function) {
      case FUNC_LOOP:
        HanDoWork();
        break;
      case FUNC_JSON_APPEND:
        if (millis() > 31000) {
          HanJson(true);
        }
        break;
      case FUNC_COMMAND:
        result = DecodeCommand(HanCommands, HanCommand);
        break;
#ifdef USE_WEBSERVER
      case FUNC_WEB_SENSOR:
        HanJson(false);
        break;
#endif  // USE_WEBSERVER
    }
  } else {
    // disabled
    switch (function) {
#ifdef USE_WEBSERVER
      case FUNC_WEB_SENSOR:
        HanDisabled();
        break;
#endif  // USE_WEBSERVER
    }
  }

  return result;
}

#warning **** HAN_V2 End! ****

#endif  // HAN_V1
#endif  // USE_HAN_V2
