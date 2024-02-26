// Tasmota HAN Driver for edpbox
// easyhan.pt

#define HAN_VERSION "13.4.0-6.04"

#ifdef USE_HAN_V2

#warning **** HAN_V2 Driver is included... ****

#define XDRV_100 100

// This variable will be set to true after initialization
bool initSuccess = false;

// HAN

uint8_t hanCFG = 99;
uint8_t hanEB = 99;
uint16_t hanERR = 0;
bool hanWork = false;
uint32_t hanDelay = 0;
uint32_t hanDelayWait = 700;
uint32_t hanDelayError = 91000;
uint8_t hanIndex = 0;  // 0 = setup
uint32_t hanRead = 0;
uint8_t hanCode = 0;

// Clock 01
uint16_t hanYY = 0;
uint8_t hanMT = 0;
uint8_t hanDD = 0;
uint8_t hanWD = 0;
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

// Last Profile

uint16_t hLP1YY = 0;
uint8_t hLP1MT = 0;
uint8_t hLP1DD = 0;
uint8_t hLP1HH = 0;
uint8_t hLP1MM = 0;

uint16_t hLP2 = 0;  // tweaked to 16bits

float hLP3 = 0;
float hLP4 = 0;
float hLP5 = 0;
float hLP6 = 0;
float hLP7 = 0;
float hLP8 = 0;
uint8_t hLPid[9];

// Misc

float hCT1 = 0;
uint8_t hTariff = 0;
char hErrTime[10];
char hErrCode[5];
char hStatus[10];

// **********************

#include <ModbusMaster.h>

ModbusMaster node;

void hanBlink() {
#ifdef ESP8266
  digitalWrite(2, LOW);
  delay(50);
  digitalWrite(2, HIGH);
#endif
}

void setDelayError(uint8_t hanRes) {
  hanCode = hanRes;
  if (hanRes == 0xe2) {
    hanDelay = hanDelayError;
    hanIndex = 0;
    sprintf(hStatus, "Error");
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Waiting %ds"),
           hanDelayError / 1000);
  } else {
    hanDelay = hanDelayWait;
  }
  sprintf(hErrTime, "%02d:%02d:%02d", hanHH, hanMM,
          hanSS);
  sprintf(hErrCode, "0x%02X", hanCode);
}

void HanInit() {
  AddLog(LOG_LEVEL_INFO, PSTR("HAN: Init..."));

#ifdef ESP8266
  pinMode(2, OUTPUT);
#endif

  ClaimSerial();  // Tasmota SerialLog

  sprintf(hStatus, "Init");
  hanRead = millis() + 21000;

  // Set initSuccess at the very end of the init process
  // Init is successful
  initSuccess = true;

}  // end HanInit

void HanDoWork(void) {
  //

  if (hanRead + hanDelay < millis()) {
    hanWork = true;
  }

  // # # # # # # # # # #
  // EASYHAN MODBUS BEGIN
  // # # # # # # # # # #

  uint8_t hRes;

  // # # # # # # # # # #
  // Setup
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 0)) {
    //

    Serial.end();
    Serial.flush();
    Serial.begin(9600, SERIAL_8N1);

    delay(250);

    node.begin(1, Serial);

    delay(100);

    uint8_t testserial;

    node.clearResponseBuffer();
    testserial = node.readInputRegisters(0x0001, 1);
    if (testserial == node.ku8MBSuccess) {
      hanCFG = 1;
      hanIndex++;
      hanDelay = hanDelayWait;
      AddLog(LOG_LEVEL_INFO, PSTR("HAN: 8N1 OK"));
    } else {
      hanCode = testserial;
      AddLog(LOG_LEVEL_INFO,
             PSTR("HAN: 8N1 Fail. Error %d"), hanCode);
      hanERR++;
      setDelayError(testserial);
      //
      Serial.end();
      Serial.flush();
      Serial.begin(9600, SERIAL_8N2);
      delay(250);
      //
      node.clearResponseBuffer();
      testserial = node.readInputRegisters(0x0001, 1);
      if (testserial == node.ku8MBSuccess) {
        hanCFG = 2;
        hanIndex++;
        hanDelay = hanDelayWait;
        AddLog(LOG_LEVEL_INFO, PSTR("HAN: 8N2 OK"));
      } else {
        hanCode = testserial;
        AddLog(LOG_LEVEL_INFO,
               PSTR("HAN: 8N2 Fail. Error %d"), hanCode);
        hanERR++;
        setDelayError(testserial);
        hanCFG = 99;
      }
      //
    }

    delay(150);

    if (hanCFG != 99) {
      // Detect EB Type

      uint8_t testEB;
      uint16_t hanDTT = 0;

      node.clearResponseBuffer();
      testEB = node.readInputRegisters(0x0070, 2);
      if (testEB == node.ku8MBSuccess) {
        //
        hanDTT = node.getResponseBuffer(0);
        if (hanDTT > 0) {
          hanDelay = hanDelayWait;
          hanEB = 3;
          AddLog(LOG_LEVEL_INFO, PSTR("HAN: EB3"));
        } else {
          hanDelay = hanDelayWait;
          hanEB = 1;
          AddLog(LOG_LEVEL_INFO, PSTR("HAN: EB1 Type 3"));
        }
        //
      } else {
        hanCode = testEB;
        hanDelay = hanDelayWait;
        hanEB = 1;
        AddLog(LOG_LEVEL_INFO,
               PSTR("HAN: EB1 Type 1 Error %d"), hanCode);
      }
    }  // if hanCFG != 99
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Clock ( 12 bytes )
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 1)) {
    node.clearResponseBuffer();
    hRes = node.readInputRegisters(0x0001, 1);
    if (hRes == node.ku8MBSuccess) {
      hanYY = node.getResponseBuffer(0);
      hanMT = node.getResponseBuffer(1) >> 8;
      hanDD = node.getResponseBuffer(1) & 0xFF;
      hanWD = node.getResponseBuffer(2) >> 8;
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

  if (hanWork & (hanIndex == 2)) {
    if (hanEB == 3) {
      node.clearResponseBuffer();
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
      node.clearResponseBuffer();
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

  if (hanWork & (hanIndex == 3)) {
    if (hanEB == 3) {
      node.clearResponseBuffer();
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
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    } else {
      node.clearResponseBuffer();
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
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Power Factor (7B) / Frequency (7F)
  // Power Factor (tri)
  // Frequency (mono)
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 4)) {
    if (hanEB == 3) {
      node.clearResponseBuffer();
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
      node.clearResponseBuffer();
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

  if (hanWork & (hanIndex == 5)) {
    node.clearResponseBuffer();
    hRes = node.readInputRegisters(0x0026, 3);
    if (hRes == node.ku8MBSuccess) {
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

  if (hanWork & (hanIndex == 6)) {
    node.clearResponseBuffer();
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
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    hanRead = millis();
    hanWork = false;
  }

  // # # # # # # # # # #
  // Load Profile
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 7)) {
    node.clearResponseBuffer();
    hRes = node.readLastProfile(0x00, 0x01);
    if (hRes == node.ku8MBSuccess) {
      hLP1YY = node.getResponseBuffer(0);
      hLP1MT = node.getResponseBuffer(1) >> 8;
      hLP1DD = node.getResponseBuffer(1) & 0xFF;
      // hLP1WD = node.getResponseBuffer(2) >> 8;
      hLP1HH = node.getResponseBuffer(2) & 0xFF;
      hLP1MM = node.getResponseBuffer(3) >> 8;
      // hLP1SS = node.getResponseBuffer(3) & 0xFF;

      // tweaked to 16bits. branch: LP1.
      hLP2 = node.getResponseBuffer(6);

      hLP3 = (node.getResponseBuffer(8) |
              node.getResponseBuffer(7) << 16) /
             1000.0;
      hLP4 = (node.getResponseBuffer(10) |
              node.getResponseBuffer(9) << 16) /
             1000.0;
      hLP5 = (node.getResponseBuffer(12) |
              node.getResponseBuffer(11) << 16) /
             1000.0;
      hLP6 = (node.getResponseBuffer(14) |
              node.getResponseBuffer(13) << 16) /
             1000.0;
      hLP7 = (node.getResponseBuffer(16) |
              node.getResponseBuffer(15) << 16) /
             1000.0;
      hLP8 = (node.getResponseBuffer(18) |
              node.getResponseBuffer(17) << 16) /
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
  // Contract
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 8)) {
    node.clearResponseBuffer();
    hRes = node.readInputRegisters(0x000C, 1);
    if (hRes == node.ku8MBSuccess) {
      hCT1 = (node.getResponseBuffer(1) |
              node.getResponseBuffer(0) << 16) /
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
  // Tariff
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 9)) {
    node.clearResponseBuffer();
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
  // LP ID
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 10)) {
    node.clearResponseBuffer();
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
  // EASYHAN MODBUS EOF
  // # # # # # # # # # #

  node.clearResponseBuffer();
  node.clearTransmitBuffer();

  if (hanERR > 900) {
    hanERR = 0;
  }

  if (hanIndex > 10) {
    hanIndex = 1;
  }

  // end loop

}  // end HanDoWork

void HanJson(bool json) {
  //
  if (json) {
    ResponseAppend_P(",\"EB%d\":{", hanEB);
    ResponseAppend_P("\"ErrCode\":\"%s\"", hErrCode);
    ResponseAppend_P(",\"ErrTime\":\"%s\"", hErrTime);
    ResponseAppend_P(",\"ErrCnt\":%d", hanERR);

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

    ResponseAppend_P(",\"LP1_Y\":%d", hLP1YY);
    ResponseAppend_P(",\"LP1_M\":%d", hLP1MT);
    ResponseAppend_P(",\"LP1_D\":%d", hLP1DD);
    ResponseAppend_P(",\"LP1_HH\":%d", hLP1HH);
    ResponseAppend_P(",\"LP1_MM\":%d", hLP1MM);

    ResponseAppend_P(",\"LP3_IMP\":%3_f", &hLP3);
    ResponseAppend_P(",\"LP4\":%3_f", &hLP4);
    ResponseAppend_P(",\"LP5\":%3_f", &hLP5);
    ResponseAppend_P(",\"LP6_EXP\":%3_f", &hLP6);

    ResponseAppend_P(",\"CT1\":%2_f", &hCT1);
    ResponseAppend_P(",\"Tariff\":%d", hTariff);

    ResponseAppend_P("}");

  } else {
    WSContentSend_PD("{s}<br>{m} {e}");
    WSContentSend_PD("{s}HAN V2 " HAN_VERSION " {m} {e}");
    WSContentSend_PD("{s}<br>{m} {e}");

    uint32_t tmpWait =
        ((hanRead + hanDelay) - millis()) / 1000;

    if (tmpWait > 900) {
      tmpWait = 999;
    }

    WSContentSend_PD("{s}EB Status {m} %s %ds {e}",
                     hStatus, tmpWait);

    WSContentSend_PD("{s}EB Index {m} %d {e}", hanIndex);

    if (hanERR > 0) {
      WSContentSend_PD("{s}EB Error Time {m} %s{e}",
                       hErrTime);

      WSContentSend_PD("{s}EB Error Code {m} %s {e}",
                       hErrCode);
    }

    WSContentSend_PD("{s}EB Error Count {m} %d {e}",
                     hanERR);

    WSContentSend_PD("{s}EB Serial {m} 8N%d {e}", hanCFG);
    WSContentSend_PD("{s}EB Type {m} %d {e}", hanEB);
    WSContentSend_PD("{s}<br>{m} {e}");

    char hanClock[10];
    sprintf(hanClock, "%02d:%02d:%02d", hanHH, hanMM,
            hanSS);

    WSContentSend_PD("{s}Clock {m} %s{e}", hanClock);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Voltage L1 {m} %1_f V{e}",
                     &hanVL1);

    if (hanEB == 3) {
      WSContentSend_PD("{s}Voltage L2 {m} %1_f V{e}",
                       &hanVL2);
      WSContentSend_PD("{s}Voltage L3 {m} %1_f V{e}",
                       &hanVL3);

      WSContentSend_PD("{s}<br>{m} {e}");
      WSContentSend_PD("{s}Current{m} %1_f A{e}",
                       &hanCLT);
    }

    WSContentSend_PD("{s}Current L1 {m} %1_f A{e}",
                     &hanCL1);

    if (hanEB == 3) {
      WSContentSend_PD("{s}Current L2 {m} %1_f A{e}",
                       &hanCL2);
      WSContentSend_PD("{s}Current L3 {m} %1_f A{e}",
                       &hanCL3);

      WSContentSend_PD("{s}<br>{m} {e}");
    }

    WSContentSend_PD("{s}Power Import {m} %d W{e}",
                     hanAPI);
    WSContentSend_PD("{s}Power Export {m} %d W{e}",
                     hanAPE);

    if (hanEB == 3) {
      WSContentSend_PD("{s}Power L1 {m} %d W{e}",
                       hanAPI1);
      WSContentSend_PD("{s}Power L2 {m} %d W{e}",
                       hanAPI2);
      WSContentSend_PD("{s}Power L3 {m} %d W{e}",
                       hanAPI3);
      WSContentSend_PD("{s}Power L1 Export {m} %d W{e}",
                       hanAPE1);
      WSContentSend_PD("{s}Power L2 Export {m} %d W{e}",
                       hanAPE2);
      WSContentSend_PD("{s}Power L3 Export {m} %d W{e}",
                       hanAPE3);

      WSContentSend_PD("{s}<br>{m} {e}");
    }

    WSContentSend_PD("{s}Power Factor {m} %3_f φ{e}",
                     &hanPF);

    if (hanEB == 3) {
      WSContentSend_PD("{s}Power Factor L1 {m} %3_f φ{e}",
                       &hanPF1);
      WSContentSend_PD("{s}Power Factor L2 {m} %3_f φ{e}",
                       &hanPF2);
      WSContentSend_PD("{s}Power Factor L3 {m} %3_f φ{e}",
                       &hanPF3);
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

    char hLPDate[15];
    sprintf(hLPDate, "%04d-%02d-%02d", hLP1YY, hLP1MT,
            hLP1DD);

    WSContentSend_PD("{s}LP1 Date {m} %s{e}", hLPDate);

    char hLPClock[10];
    sprintf(hLPClock, "%02d:%02d", hLP1HH, hLP1MM);

    WSContentSend_PD("{s}LP1 Time {m} %s{e}", hLPClock);

    WSContentSend_PD("{s}LP2 AMR {m} %d{e}", hLP2);

    WSContentSend_PD("{s}LP3 Import Inc  {m} %3_f kWh{e}",
                     &hLP3);
    WSContentSend_PD("{s}LP4 {m} %3_f kWh{e}", &hLP4);
    WSContentSend_PD("{s}LP5 {m} %3_f kWh{e}", &hLP5);
    WSContentSend_PD("{s}LP6 Export Inc {m} %3_f kWh{e}",
                     &hLP6);

    if (hLPid[6] != 10) {
      WSContentSend_PD(
          "{s}Error: Export Inc {m} %d != 10 {e}",
          hLPid[6]);
    }

    WSContentSend_PD("{s}LP7 {m} %3_f kWh{e}", &hLP7);
    WSContentSend_PD("{s}LP8 {m} %3_f kWh{e}", &hLP8);

    char tmpLPid[25];
    sprintf(tmpLPid, "%d %d %d %d %d %d %d %d", hLPid[1],
            hLPid[2], hLPid[3], hLPid[4], hLPid[5],
            hLPid[6], hLPid[7], hLPid[8]);

    WSContentSend_PD("{s}IDs: %s {m} {e}", tmpLPid);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Contract T1 {m} %2_f kWh{e}",
                     &hCT1);

    char tarifa[10];

    switch (hTariff) {
      case 1:
        sprintf(tarifa, "%s", "Vazio");
        break;
      case 2:
        sprintf(tarifa, "%s", "Ponta");
        break;
      case 3:
        sprintf(tarifa, "%s", "Cheias");
        break;
      default:
        sprintf(tarifa, "Error %d", hTariff);
    }

    WSContentSend_PD("{s}Tariff {m} %s{e}", tarifa);

    WSContentSend_PD("{s}<br>{m} {e}");

  }  // eof !json

}  // HanJson

// ********************************************
// ********************************************

const char HanCommands[] PROGMEM =
    "|"  // No Prefix
    "HanDelay|"
    "HanHelp";

void (*const HanCommand[])(void) PROGMEM = {&CmdHanDelay,
                                            &CmdHanHelp};

void CmdHanHelp(void) {
  AddLog(LOG_LEVEL_INFO, PSTR("HanHelp: Hello!"));
  AddLog(LOG_LEVEL_INFO,
         PSTR("HanHelp: Commands available: HanDelay"));
  ResponseCmndDone();
}

void CmdHanDelay(void) {
  if ((XdrvMailbox.payload >= 0) &&
      (XdrvMailbox.payload <= 900)) {
    hanDelay = XdrvMailbox.payload * 1000;
  } else {
    hanDelay = 300000;
  }
  AddLog(LOG_LEVEL_INFO,
         PSTR("HanDelay: Paused modbus %ds"),
         hanDelay / 1000);
  sprintf(hStatus, "Cmd");
  ResponseCmndDone();
}

// main tasmota function

bool Xdrv100(uint32_t function) {
  bool result = false;

  if (FUNC_INIT == function) {
    HanInit();
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Done !"));
  } else if (initSuccess) {
    switch (function) {
      case FUNC_LOOP:
        HanDoWork();
        break;
      case FUNC_JSON_APPEND:
        HanJson(true);
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
  }

  return result;
}

#warning **** HAN_V2 End! ****

#endif  // USE_HAN_V2
