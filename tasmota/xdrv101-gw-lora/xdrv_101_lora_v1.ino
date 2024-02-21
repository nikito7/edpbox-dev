// Tasmota LoRa driver
// easyhan.pt

#define LORA_VERSION "2024.02.21.0151"

#ifdef USE_LORA_V1

#warning **** LORA_V1 Driver is included... ****

#define XDRV_101 101

// This variable will be set to true after initialization
bool initSuccess = false;

char *topic = nullptr;
size_t topic_size = 50;

#include <ArduinoJson.h>

static char jsonBuffer[512];
StaticJsonDocument<512> LORAdata;

// LoRa

#include <LoRa.h>

// esp8266
#define LORA_SCK 14
#define LORA_MISO 12
#define LORA_MOSI 13
#define LORA_SS 15
#define LORA_RST -1
#define LORA_DI0 5

// ### CHA_CHA_POLY ###

#include "../../easyhan_secrets_cha.h"
#include "ChaChaPolyHelper.h"

byte iv[CHA_CHA_POLY_IV_SIZE];

// ### CHA_CHA_POLY EOF ###

// **********************

void LoRaInit() {
  //
  topic = (char *)calloc(topic_size, sizeof(char));

  if (!topic) {
    AddLog(LOG_LEVEL_INFO, PSTR("LORA: out of memory"));
    return;
  }

  AddLog(LOG_LEVEL_INFO, PSTR("LORA: Init..."));

  SPI.begin();

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DI0);
  LoRa.setSyncWord(0x12);

  if (!LoRa.begin(868E6)) {
    while (true)
      ;
  }

  AddLog(LOG_LEVEL_INFO, PSTR("LORA: SCK  %d"), LORA_SCK);
  AddLog(LOG_LEVEL_INFO, PSTR("LORA: MISO %d"),
         LORA_MISO);
  AddLog(LOG_LEVEL_INFO, PSTR("LORA: MOSI %d"),
         LORA_MOSI);
  AddLog(LOG_LEVEL_INFO, PSTR("LORA: SS   %d"), LORA_SS);
  AddLog(LOG_LEVEL_INFO, PSTR("LORA: RST  %d"), LORA_RST);
  AddLog(LOG_LEVEL_INFO, PSTR("LORA: DI0  %d"), LORA_DI0);

  LoRa.receive();

  // Set initSuccess at the very end of the init process
  // Init is successful
  initSuccess = true;

}  // end LoRaInit

void LoRaWork(void) {
  //
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    //
    AddLog(LOG_LEVEL_INFO,
           PSTR("LORA: Packet Received ! %d bytes"),
           packetSize);

    byte rxArray[packetSize];

    for (uint8_t i = 0; i < packetSize; i++) {
      rxArray[i] = (char)LoRa.read();
    }

    bool noVerify = false;
    uint8_t polySize =
        CHA_CHA_POLY_TAG_SIZE + CHA_CHA_POLY_IV_SIZE;

    if (packetSize > polySize & packetSize < 250) {
      // ### if packet size is Cha Cha ###

      byte tag[CHA_CHA_POLY_TAG_SIZE];
      byte plainText[sizeof(rxArray) - polySize];
      byte cipherText[sizeof(plainText)];

      // copy arrays
      memcpy(cipherText, rxArray, sizeof(cipherText));
      memcpy(tag, &rxArray[sizeof(cipherText)],
             sizeof(tag));
      memcpy(iv,
             &rxArray[sizeof(cipherText) + sizeof(tag)],
             sizeof(iv));

      // clear array
      for (uint8_t i = 0; i < sizeof(plainText); i++) {
        plainText[i] = 0xff;
      }

      // decrypt message from cipherText to plainText
      // output is valid only if result is true
      bool verify = ChaChaPolyCipher.decrypt(
          key, iv, auth, cipherText, plainText, tag);

      if (verify) {
        // hex to json

        uint16_t fport16 =
            plainText[0] << 8 | plainText[1];

        switch (fport16) {
          case 7001: {
            //

            char hanID[20];

            sprintf(
                hanID, "%d_EB%d",
                (plainText[2] << 24 | plainText[3] << 16 |
                 plainText[4] << 8 | plainText[5]),
                plainText[6]);

            LORAdata["id"] = hanID;

            // LORAdata["EBx"] = plainText[6];
            LORAdata["Ser"] = plainText[7];

            LORAdata["ERR"] =
                plainText[8] << 8 | plainText[9];

            LORAdata["up"] = plainText[10] << 24 |
                             plainText[11] << 16 |
                             plainText[12] << 8 |
                             plainText[13];

            // LORAdata["HH"] = plainText[14];
            // LORAdata["MM"] = plainText[15];
            // LORAdata["SS"] = plainText[16];

            char hanClock[10];
            sprintf(hanClock, "%02d:%02d:%02d",
                    plainText[14], plainText[15],
                    plainText[16]);

            LORAdata["Clock"] = hanClock;

            LORAdata["VL1"] =
                (plainText[17] << 8 | plainText[18]) /
                10.0;
            LORAdata["CL1"] =
                (plainText[19] << 8 | plainText[20]) /
                10.0;
            LORAdata["VL2"] =
                (plainText[21] << 8 | plainText[22]) /
                10.0;
            LORAdata["CL2"] =
                (plainText[23] << 8 | plainText[24]) /
                10.0;
            LORAdata["VL3"] =
                (plainText[25] << 8 | plainText[26]) /
                10.0;
            LORAdata["CL3"] =
                (plainText[27] << 8 | plainText[28]) /
                10.0;
            LORAdata["CLT"] =
                (plainText[29] << 8 | plainText[30]) /
                10.0;

            LORAdata["FR"] =
                (plainText[31] << 8 | plainText[32]) /
                10.0;

            LORAdata["PF"] =
                (plainText[33] << 8 | plainText[34]) /
                1000.0;
            LORAdata["PF1"] =
                (plainText[35] << 8 | plainText[36]) /
                1000.0;
            LORAdata["PF2"] =
                (plainText[37] << 8 | plainText[38]) /
                1000.0;
            LORAdata["PF3"] =
                (plainText[39] << 8 | plainText[40]) /
                1000.0;

            LORAdata["API"] = plainText[41] << 24 |
                              plainText[42] << 16 |
                              plainText[43] << 8 |
                              plainText[44];

            LORAdata["APE"] = plainText[45] << 24 |
                              plainText[46] << 16 |
                              plainText[47] << 8 |
                              plainText[48];

            // 32bits to 16bits
            LORAdata["API1"] =
                plainText[49] << 8 | plainText[50];
            LORAdata["APE1"] =
                plainText[51] << 8 | plainText[52];
            LORAdata["API2"] =
                plainText[53] << 8 | plainText[54];
            LORAdata["APE2"] =
                plainText[55] << 8 | plainText[56];
            LORAdata["API3"] =
                plainText[57] << 8 | plainText[58];
            LORAdata["APE3"] =
                plainText[59] << 8 | plainText[60];
            // back to normal size

            // Total Energy Tarifas Import kWh
            LORAdata["TET1"] =
                (plainText[61] << 24 |
                 plainText[62] << 16 |
                 plainText[63] << 8 | plainText[64]) /
                1000.0;

            LORAdata["TET2"] =
                (plainText[65] << 24 |
                 plainText[66] << 16 |
                 plainText[67] << 8 | plainText[68]) /
                1000.0;

            LORAdata["TET3"] =
                (plainText[69] << 24 |
                 plainText[70] << 16 |
                 plainText[71] << 8 | plainText[72]) /
                1000.0;

            // Total Energy kWh
            LORAdata["TEI"] =
                (plainText[73] << 24 |
                 plainText[74] << 16 |
                 plainText[75] << 8 | plainText[76]) /
                1000.0;

            LORAdata["TEE"] =
                (plainText[77] << 24 |
                 plainText[78] << 16 |
                 plainText[79] << 8 | plainText[80]) /
                1000.0;
            //
            char tmpHexCode[5];
            sprintf(tmpHexCode, "%02X", plainText[81]);
            LORAdata["Code"] = tmpHexCode;
            //

            size_t loralen = measureJson(LORAdata) + 1;
            serializeJson(LORAdata, jsonBuffer, loralen);

            AddLog(
                LOG_LEVEL_INFO,
                PSTR("LORA: Valid! Fport: %d"),
                fport16);

            snprintf_P(topic, topic_size,
                       PSTR("home/lora/%s_p1"), hanID);

            MqttPublishPayload(topic, jsonBuffer,
                               strlen(jsonBuffer),
                               false);  // retain = true

            LORAdata.clear();
            break;
          }  // eof 7001

          case 7002: {
            //

            char hanID[20];

            sprintf(
                hanID, "%d_EB%d",
                (plainText[2] << 24 | plainText[3] << 16 |
                 plainText[4] << 8 | plainText[5]),
                plainText[6]);

            LORAdata["id"] = hanID;

            //

            LORAdata["LP1YY"] =
                plainText[7] << 8 | plainText[8];
            LORAdata["LP1MT"] = plainText[9];
            LORAdata["LP1DD"] = plainText[10];
            LORAdata["LP1HH"] = plainText[11];
            LORAdata["LP1MM"] = plainText[12];

            // needed to confirm mb tweak
            LORAdata["LP2"] =
                plainText[13] << 8 | plainText[14];

            LORAdata["LP3"] =
                (plainText[15] << 24 |
                 plainText[16] << 16 |
                 plainText[17] << 8 | plainText[18]) /
                1000.0;

            //

            size_t loralen = measureJson(LORAdata) + 1;
            serializeJson(LORAdata, jsonBuffer, loralen);

            AddLog(
                LOG_LEVEL_INFO,
                PSTR("LORA: Valid! Fport: %d"),
                fport16);

            snprintf_P(topic, topic_size,
                       PSTR("home/lora/%s_p2"), hanID);

            MqttPublishPayload(topic, jsonBuffer,
                               strlen(jsonBuffer),
                               false);  // retain = true

            LORAdata.clear();
            break;
          }  // 7002

          default: {
            AddLog(LOG_LEVEL_INFO,
                   PSTR("LORA: Unknown Fport ! %d"),
                   fport16);
          }  // eof default

        }  // eof switch

      }  // eof if verify
      else {
        noVerify = true;
      }  // eof else if verify
    }    // eof if packet size is cha cha true
    else {
      noVerify = true;
    }

    if (noVerify) {
      //
      AddLog(LOG_LEVEL_INFO,
             PSTR("LORA: Packet Invalid !"));
    }  // if noVerify

  }  // end if packetSize

}  // end LoRaWork

void LoRaJson(bool json) {
  if (json) {
    //

  } else {
    WSContentSend_PD("{s}LoRa Gateway {m} {e}");
    WSContentSend_PD("{s}Build: " LORA_VERSION
                     " {m} {e}");
    WSContentSend_PD("{s}<br>{m} {e}");

    float tmpHeap = ESP.getFreeHeap() / 1000.0;

    WSContentSend_PD("{s}Free Heap{m} %1_f kB{e}",
                     &tmpHeap);
    WSContentSend_PD("{s}<br>{m} {e}");

  }  // eof !json

}  // HanJson

/********************************************\
 * Interface
\********************************************/

bool Xdrv101(uint32_t function) {
  bool result = false;

  if (FUNC_INIT == function) {
    LoRaInit();
  } else if (initSuccess) {
    switch (function) {
      case FUNC_LOOP:
        LoRaWork();
        break;
      case FUNC_JSON_APPEND:
        LoRaJson(true);
        break;
#ifdef USE_WEBSERVER
      case FUNC_WEB_SENSOR:
        LoRaJson(false);
        break;
#endif  // USE_WEBSERVER
    }
  }

  return result;
}

#warning **** LORA_V1 End! ****

#endif  // USE_LORA_V1

