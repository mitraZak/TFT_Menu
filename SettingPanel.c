#include "SharedPanel.h"
#include "SettingPanel.h"


void handleSettingSecondPanelsInput(char incomingChar) {
    if (incomingChar == '#') {
        nextCallOption();
    } else if (incomingChar == '*') {
        previousCallOption();
    } else if (incomingChar == 'D') {
      switch (button2ndIndex) {
        case 0:
          enterSettingFourthPanels();
          break;
        case 1:
          enterSettingThirdPanels();
          break;
        case 2:
          enterSettingFifthPanels();
          break;
  }
    } else if (incomingChar == 'A') {
        enterFirstPanels();
    }
}

void handleSettingThirdPanelsInput(char incomingChar) {
    Serial.print("Received in Setting Third Panels: ");
    Serial.println(incomingChar);
    if (incomingChar == 'A') {
        Serial.println("Exiting Setting Third Panels");
        enterSettingSecondPanels();
    }
    else {
        Serial.println("Unknown input in Setting Third Panels");
    }
}

void handleSettingFourthPanelsInput(char incomingChar) {
    if (incomingChar == 'A' || incomingChar == 'B' ) {
      enterSettingSecondPanels();
    }
    else if (incomingChar == 'D') {
        // ResetFactory();
        tft.fillScreen(background_color);
        tft.pushImage(0, 0, 320, 60, epd_bitmap_reset);
        delay(500);
        tft.drawCircle(90, 120, 20, ILI9341_WHITE);
        delay(500);
        tft.drawCircle(135, 120, 20, ILI9341_WHITE);
        delay(500);
        tft.drawCircle(180, 120, 20, ILI9341_WHITE);
        delay(500);
        tft.drawCircle(225, 120, 20, ILI9341_WHITE);
        delay(500);
        for (int i = 101; i <= 108; i++) { // input temp and battery
          EEPROM.write(i, 0); 
        }
        // EEPROM.write(9, 0); //number of reports
        for (int i = 4; i <= 8; i++) { // each report value for output on webserver
          EEPROM.write(i, 0); 
        }
        for (int i = REPORT_ADD_OFFSET; i <= REPORT_ADD_OFFSET+5; i++) { // each color of reports
          EEPROM.write(i, 0); 
        }
        tft.pushImage(0, 210, 320, 60, epd_bitmap_reset_2);
        delay(1500);
        tft.fillScreen(background_color);
        enterFirstPanels();
    }
}

void handleSettingFifthPanelsInput(char incomingChar) {
  if (isDigitOrD(incomingChar)) {
    TempBatFromFifthSetting(incomingChar);
  }
  else if (incomingChar == 'A') {
    enterSettingSecondPanels();
  }
}

void enterSettingFourthPanels() {
    currentState = Setting_Fourth_Panels;
    tft.pushImage(0, 0, 320, 240, epd_bitmap_setting_1_2);
}

void enterSettingThirdPanels() {
    currentState = Setting_Third_Panels;
    tft.pushImage(0, 0, 320, 240, epd_bitmap_setting_2_2);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(40, 100);
    tft.print("Password:");
    tft.setCursor(150, 100);
    tft.print(password);
    tft.setCursor(40, 150);
    tft.print("LocalIP:");
    tft.setCursor(150, 150);
    tft.print(localIP);
    tft.setCursor(40, 200);
    tft.print("SSID:");
    tft.setCursor(150, 200);
    tft.print(ssid);
}

void enterSettingFifthPanels() {
    currentState = Setting_Fifth_Panels;
    tft.pushImage(0, 0, 320, 240, epd_bitmap_setting_3_2);
}

void TempBatFromFifthSetting(char incomingChar) {
  if (numberInputIdx >= numbersCount) {
    pos_incomingChar = 0;
    pos_X_incomingChar = 0;
    numberInputIdx = 0;
    digitOfNumberInputIdx = 0;
    currentNumber = 0;
    return;
  }

  if (incomingChar == 'D') {
    numberInputs[numberInputIdx++] = currentNumber;  
    currentNumber = 0;   
    digitOfNumberInputIdx = 0;

    tft.setTextColor(TFT_WHITE, background_color);
    tft.setCursor(137, 76 + ((numberInputIdx - 1) * 40));
    tft.print(numberInputs[numberInputIdx - 1]);
    tft.pushImage(85, 70 + ((numberInputIdx - 1) * 40), 35, 35, epd_bitmap_setting_done);

    if (numberInputIdx == numbersCount) {
      temperature_max = numberInputs[0];
      temperature_min = numberInputs[1];
      battery_max = numberInputs[2];
      battery_min = numberInputs[3];
      Serial.print("temperature_max: "); Serial.print(temperature_max);
      EEPROM.write(temperature_max_EEPROMAddress, temperature_max); 
      EEPROM.write(temperature_min_EEPROMAddress, temperature_min);
      EEPROM.write(battery_max_EEPROMAddress, battery_max);
      EEPROM.write(battery_min_EEPROMAddress, battery_min);
      EEPROM.commit();
      // int saved_temperature_max = EEPROM.read(temperature_max_EEPROMAddress);
      // Serial.print("temperature_max on EEPROM: "); Serial.print(saved_temperature_max);
      tft.fillScreen(background_color);
      tft.pushImage(0, 0, 320, 239, epd_bitmap_setting_temp_bat);
      delay(1500);
      tft.fillScreen(background_color);
      enterFirstPanels();
      return; 
    }
    pos_incomingChar++;
    pos_X_incomingChar = 0;
  }

  else if ('0' <= incomingChar && incomingChar <= '9') {
    // tft.fillRect(130 + pos_X_incomingChar, 76 + (pos_incomingChar * 40), 12, 25, background_color); 
    tft.setTextColor(TFT_WHITE, background_color);
    tft.setCursor(137 + pos_X_incomingChar, 76 + (pos_incomingChar * 40));
    tft.print(incomingChar);
    if (digitOfNumberInputIdx >= 2) {
      return; // Limit input to 2 digits
    }

    currentNumber = currentNumber * 10 + (incomingChar - '0');
    digitOfNumberInputIdx++;
    pos_X_incomingChar += 12;
  }

  else if (incomingChar == 'A')
    enterFirstPanels();
}

