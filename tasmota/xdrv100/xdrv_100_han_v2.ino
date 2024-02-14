#ifdef USE_HAN_V2

#warning **** HAN_V2 Driver is included... ****

#define XDRV_100 100

// This variable will be set to true after initialization
bool initSuccess = false;

// HAN

uint8_t hanCNT = 0;
uint8_t hanCFG = 99;
uint8_t hanEB = 99;
uint16_t hanERR = 0;
uint16_t hanDTT = 0;
bool hanWork = true;
uint32_t hanDelay = 0;
uint32_t hanDelayWait = 800;
uint32_t hanDelayError = 61000;
uint8_t hanIndex = 1;
uint32_t lastRead = 0;
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

uint32_t hLP3 = 0;
uint32_t hLP4 = 0;
uint32_t hLP5 = 0;
uint32_t hLP6 = 0;

#include <HardwareSerial.h>
#include <ModbusMaster.h>

ModbusMaster node;

void hanBlink() {
#ifdef ESP8266
  digitalWrite(2, LOW);
  delay(30);
  digitalWrite(2, HIGH);
#endif
}

void setDelayError(uint8_t hanRes) {
  hanCode = hanRes;
  if (hanERR > 1) {
    hanDelay = hanDelayError;
  } else {
    hanDelay = hanDelayWait;
  }
}

void HanInit() {
  AddLog(LOG_LEVEL_INFO, PSTR("HAN: Init..."));

#ifdef ESP8266
  pinMode(2, OUTPUT);
#endif

  HardwareSerial &serial = Serial;

  serial.begin(9600, SERIAL_8N1);

  delay(100);

  node.begin(1, serial);

  delay(100);

  uint8_t testserial;

  testserial = node.readInputRegisters(0x0001, 1);
  if (testserial == node.ku8MBSuccess) {
    hanCFG = 1;
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: 8N1 OK!"));
  } else {
    hanCode = testserial;
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Error Code %d"),
           hanCode);
    //
    serial.end();
    delay(100);
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Testing 8N2"));
    serial.begin(9600, SERIAL_8N2);
    delay(100);

    testserial = node.readInputRegisters(0x0001, 1);
    if (testserial == node.ku8MBSuccess) {
      hanCFG = 2;
      AddLog(LOG_LEVEL_INFO, PSTR("HAN: 8N2 OK!"));
    } else {
      hanCode = testserial;
      AddLog(LOG_LEVEL_INFO, PSTR("HAN: Error Code %d"),
             hanCode);
      serial.end();
      delay(100);
      AddLog(LOG_LEVEL_INFO,
             PSTR("HAN: Fail! Default to 8N1"));
      serial.begin(9600, SERIAL_8N1);
      delay(100);
      hanCFG = 1;
    }
    //
  }

  delay(100);

  // Detect EB Type

  testserial = node.readInputRegisters(0x0070, 2);
  if (testserial == node.ku8MBSuccess) {
    //
    hanDTT = node.getResponseBuffer(0);
    if (hanDTT > 0) {
      AddLog(LOG_LEVEL_INFO, PSTR("HAN: EB3!"));
      hanEB = 3;
    } else {
      AddLog(LOG_LEVEL_INFO, PSTR("HAN: EB1! Type 3"));
      hanEB = 1;
    }
    //
  } else {
    hanCode = testserial;
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: EB1! Type 1"));
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Error Code %d"),
           hanCode);
    hanEB = 1;
  }

  lastRead = millis() + 10000;

  // Set initSuccess at the very end of the init process
  // Init is successful
  initSuccess = true;

}  // end HanInit

void HanDoWork(void) {
  delay(30);

  if (lastRead + hanDelay < millis()) {
    hanWork = true;
  }

  // # # # # # # # # # #
  // EASYHAN MODBUS BEGIN
  // # # # # # # # # # #

  uint8_t hRes;

  // # # # # # # # # # #
  // Clock ( 12 bytes )
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 1)) {
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
      AddLog(LOG_LEVEL_INFO,
             PSTR("HAN: %02d:%02d:%02d !"), hanHH, hanMM,
             hanSS);
    } else {
      AddLog(LOG_LEVEL_INFO, PSTR("HAN: Error %d !"),
             hRes);

      hanERR++;
      setDelayError(hRes);
    }
    lastRead = millis();
    hanWork = false;
    hanIndex++;
  }

  // # # # # # # # # # #
  // Voltage Current
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 2)) {
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
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    }
    lastRead = millis();
    hanWork = false;
    hanIndex++;
  }

  // # # # # # # # # # #
  // Active Power Import/Export 73 (tri)
  // Power Factor (mono) (79..)
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 3)) {
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
        hanPF = node.getResponseBuffer(4);
        hanBlink();
        hanDelay = hanDelayWait;
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    }
    lastRead = millis();
    hanWork = false;
    hanIndex++;
  }

  // # # # # # # # # # #
  // Power Factor (7B) / Frequency (7F)
  // Power Factor (tri)
  // Frequency (mono)
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 4)) {
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
      } else {
        hanERR++;
        setDelayError(hRes);
      }
    }
    lastRead = millis();
    hanWork = false;
    hanIndex++;
  }

  // # # # # # # # # # #
  // Total Energy Tarifas (kWh) 26
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 5)) {
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
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    lastRead = millis();
    hanWork = false;
    hanIndex++;
  }

  // # # # # # # # # # #
  // Total Energy (total) (kWh) 16
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 6)) {
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
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    lastRead = millis();
    hanWork = false;
    hanIndex++;
  }

  // # # # # # # # # # #
  // Load Profile (test)
  // # # # # # # # # # #

  if (hanWork & (hanIndex == 7)) {
    hRes = node.readLastProfile(0x06, 0x01);
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

      hLP3 = node.getResponseBuffer(8) |
             node.getResponseBuffer(7) << 16;
      hLP4 = node.getResponseBuffer(10) |
             node.getResponseBuffer(9) << 16;
      hLP5 = node.getResponseBuffer(12) |
             node.getResponseBuffer(11) << 16;
      hLP6 = node.getResponseBuffer(14) |
             node.getResponseBuffer(13) << 16;

      hanBlink();
      hanDelay = hanDelayWait;
    } else {
      hanERR++;
      setDelayError(hRes);
    }
    lastRead = millis();
    hanWork = false;
    hanIndex++;
  }

  // # # # # # # # # # #
  // EASYHAN MODBUS EOF
  // # # # # # # # # # #

  if (hanERR > 900) {
    hanERR = 0;
  }

  if (hanIndex > 7) {
    hanIndex = 1;
  }

  // end loop

}  // end HanDoWork

void HanJson(bool json) {
  if (json) {
    ResponseAppend_P(",\"EB%d\":{", hanEB);
    ResponseAppend_P("\"Code\":%d", hanCode);

    ResponseAppend_P(",\"HH\":%d", hanHH);
    ResponseAppend_P(",\"MM\":%d", hanMM);
    ResponseAppend_P(",\"SS\":%d", hanSS);

    ResponseAppend_P(",\"VL1\":%1_f", &hanVL1);
    ResponseAppend_P(",\"VL2\":%1_f", &hanVL2);
    ResponseAppend_P(",\"VL3\":%1_f", &hanVL3);

    ResponseAppend_P(",\"CL1\":%1_f", &hanCL1);
    ResponseAppend_P(",\"CL2\":%1_f", &hanCL2);
    ResponseAppend_P(",\"CL3\":%1_f", &hanCL3);
    ResponseAppend_P(",\"CL\":%1_f", &hanCLT);

    ResponseAppend_P(",\"API\":%d", hanAPI);
    ResponseAppend_P(",\"APE\":%d", hanAPE);
    ResponseAppend_P(",\"API1\":%d", hanAPI1);
    ResponseAppend_P(",\"API2\":%d", hanAPI2);
    ResponseAppend_P(",\"API3\":%d", hanAPI3);
    ResponseAppend_P(",\"APE1\":%d", hanAPE1);
    ResponseAppend_P(",\"APE2\":%d", hanAPE2);
    ResponseAppend_P(",\"APE3\":%d", hanAPE3);

    ResponseAppend_P(",\"PF\":%3_f", &hanPF);
    ResponseAppend_P(",\"PF1\":%3_f", &hanPF1);
    ResponseAppend_P(",\"PF2\":%3_f", &hanPF2);
    ResponseAppend_P(",\"PF3\":%3_f", &hanPF3);
    ResponseAppend_P(",\"FR\":%1_f", &hanFR);

    ResponseAppend_P(",\"TET1\":%3_f", &hanTET1);
    ResponseAppend_P(",\"TET2\":%3_f", &hanTET2);
    ResponseAppend_P(",\"TET3\":%3_f", &hanTET3);

    ResponseAppend_P(",\"TEI\":%3_f", &hanTEI);
    ResponseAppend_P(",\"TEE\":%3_f", &hanTEE);

    ResponseAppend_P("}");

  } else {
    WSContentSend_PD("{s}EB Error Code {m} %d {e}",
                     hanCode);
    WSContentSend_PD("{s}EB Error Count {m} %d {e}",
                     hanERR);
    WSContentSend_PD("{s}EB Type {m} %d {e}", hanEB);
    WSContentSend_PD("{s}EB Serial {m} %d {e}", hanCFG);
    WSContentSend_PD("{s}<br>{m} {e}");

    char hanClock[10];
    sprintf(hanClock, "%02d:%02d:%02d", hanHH, hanMM,
            hanSS);

    WSContentSend_PD("{s}Clock {m} %s{e}", hanClock);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Voltage L1 {m} %1_f V{e}",
                     &hanVL1);
    WSContentSend_PD("{s}Voltage L2 {m} %1_f V{e}",
                     &hanVL2);
    WSContentSend_PD("{s}Voltage L3 {m} %1_f V{e}",
                     &hanVL3);

    WSContentSend_PD("{s}<br>{m} {e}");
    WSContentSend_PD("{s}Current{m} %1_f A{e}", &hanCLT);
    WSContentSend_PD("{s}Current L1 {m} %1_f A{e}",
                     &hanCL1);
    WSContentSend_PD("{s}Current L2 {m} %1_f A{e}",
                     &hanCL2);
    WSContentSend_PD("{s}Current L3 {m} %1_f A{e}",
                     &hanCL3);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Power Import {m} %d W{e}",
                     hanAPI);
    WSContentSend_PD("{s}Power Export {m} %d W{e}",
                     hanAPE);
    WSContentSend_PD("{s}Power L1 {m} %d W{e}", hanAPI1);
    WSContentSend_PD("{s}Power L2 {m} %d W{e}", hanAPI2);
    WSContentSend_PD("{s}Power L3 {m} %d W{e}", hanAPI3);
    WSContentSend_PD("{s}Power L1 Export {m} %d W{e}",
                     hanAPE1);
    WSContentSend_PD("{s}Power L2 Export {m} %d W{e}",
                     hanAPE2);
    WSContentSend_PD("{s}Power L3 Export {m} %d W{e}",
                     hanAPE3);

    WSContentSend_PD("{s}<br>{m} {e}");

    WSContentSend_PD("{s}Power Factor {m} %3_f φ{e}",
                     &hanPF);
    WSContentSend_PD("{s}Power Factor L1 {m} %3_f φ{e}",
                     &hanPF1);
    WSContentSend_PD("{s}Power Factor L2 {m} %3_f φ{e}",
                     &hanPF2);
    WSContentSend_PD("{s}Power Factor L3 {m} %3_f φ{e}",
                     &hanPF3);
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

  }  // eof !json

}  // HanJson

/********************************************\
 * Interface
\********************************************/

bool Xdrv100(uint32_t function) {
  bool result = false;

  if (FUNC_INIT == function) {
    HanInit();
    AddLog(LOG_LEVEL_INFO, PSTR("HAN: Done!"));
  } else if (initSuccess) {
    switch (function) {
      case FUNC_EVERY_100_MSECOND:
        HanDoWork();
        break;
      case FUNC_JSON_APPEND:
        HanJson(true);
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

#endif  // USE_HAN_V2
