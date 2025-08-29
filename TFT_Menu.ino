// my panel functions
#include "FirstPanel.h"
#include "ReportPanel.h"
#include "SettingPanel.h"
#include "HelpPanel.h"
#include "SharedPanel.h"
// my display pictures converted to bitmap
#include "back.h"
#include "icon.h"
#include "panel.h"
#include "report.h"
#include "call.h"
#include "setting.h"
#include "help.h"

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  pinMode(21, OUTPUT);
  pinMode(27, OUTPUT);
  delay(1000);
  digitalWrite(21, LOW);
  Serial.print("Pin 21 state in setup: ");
  Serial.println(digitalRead(21)); // Read and print pin state
  delay(1000);
  tft.begin();
  tft.setTextSize(2);
  tft.setSwapBytes(true);
  tft.setRotation(1);
  tft.pushImage(0, 0, 320, 240, epd_bitmap_main);
  sensors.begin();
  mySerial.begin(115200, SERIAL_8N1, 16, 17);
  //WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point created!");
  localIP = WiFi.localIP();
  Serial.print("Local IP: ");
  Serial.println(localIP);
}

void loop() {
    handleSerialInput();
    if (currentState == First_Panels) {
        SensorTemperature();
        readBatteryVoltage();
        NumberOfReports();
        displayDateTime();
    }
    else if (currentState == Call_Third_Panels) {
      if (timerRunning) {
        // Continuously update the timer display while it's running
        displayTime(timer);
        }
    }
    else if (currentState == Setting_Fifth_Panels && currentState != First_Panels){
      displaySavedTempBat();
    }
 
}