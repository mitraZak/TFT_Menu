#include "SharedPanel.h"

// Assign serial input to repective panel
void handleSerialInput() {
    if (mySerial.available()) {
        char incomingChar = mySerial.read();
        Serial.print("Received: ");
        Serial.println(incomingChar);

        switch (currentState) {
            case First_Panels:
                handleFirstPanelsInput(incomingChar);
                break;
            case Report_Second_Panels:
                handleReportSecondPanelsInput(incomingChar);
                break;
            case Report_Third_Panels:
                handleReportThirdPanelsInput(incomingChar);
                break;
            case Setting_Second_Panels:
                handleSettingSecondPanelsInput(incomingChar);
                break;
            case Setting_Third_Panels:
                handleSettingThirdPanelsInput(incomingChar);
                break;
            case Setting_Fourth_Panels:
                handleSettingFourthPanelsInput(incomingChar);
            case Setting_Fifth_Panels:
                handleSettingFifthPanelsInput(incomingChar);
                break;
            case Help_Second_Panels:
                handleHelpSecondPanelsInput(incomingChar);
                break; 
            case Call_Second_Panels:
                handleCallSecondPanelsInput(incomingChar);
                break;
            case Call_Third_Panels:
                handleCallThirdPanelsInput(incomingChar);
                break; 
        }
    }
}

void enterReportSecondPanels() {
    currentState = Report_Second_Panels;
    button2ndIndex = 0;
    drawOptions();
}

void enterSettingSecondPanels() {
    currentState = Setting_Second_Panels;
    button2ndIndex = 0;
    tft.pushImage(0, 0, 320, 240, epd_bitmap_setting_1);
    drawCallOptions();
}

void enterHelpSecondPanels() {
    currentState = Help_Second_Panels;
    tft.pushImage(0, 0, 320, 240, epd_bitmap_help_1);
}

void enterReportThirdPanels() {
    currentState = Report_Third_Panels;
    button3rdIndex = 0;
    drawSituationOptions();
}

void enterFirstPanels() {
    currentState = First_Panels;
    button1stIndex = 0;
    tft.pushImage(0, 0, 320, 240, epd_bitmap_main); // Reset the entire display
    tft.pushImage(113, 61, 190, 109, images[button1stIndex]); // Show the first icon
}

// Second panel of Report: Show buttons based on current state
void drawOptions() {
    tft.pushImage(0, 0, 320, 240, subImages[button2ndIndex / 3]);
    for (int i = 0; i < 3; i++) {
        int index = (button2ndIndex / 3) * 3 + i;
        drawOption(index, index == button2ndIndex);
        drawStateOption(index, SubOptionState(EEPROM.read(index + REPORT_ADD_OFFSET)));
        // EEPROM.read(index + 95);
    }
}

void drawOption(int optionButton, bool isSelected) {
    int y = 71 + (optionButton % 3) * 40;
    int colorIndex = isSelected ? 0 : 1;
    const uint16_t* imageData = subOptions[optionButton * 2 + colorIndex];
    tft.pushImage(271, y, 28, 28, imageData);
}

void drawStateOption(int index, int stateIdx) {
    if (index >= 5) 
      return; // no item for index 6
    
    int y = 71 + (index % 3) * 40;
    const uint16_t* imageData = subOptionStates[index * 4 + stateIdx]; // index: clean, wheel, driver. sataeIdx: good, bad, normal, neutral
    tft.pushImage(20, y, 240, 28, imageData);

    // appearance
    if (index == 0) {
      int appearanceValues[] = {0, 3, 2, 1};
      appearance = appearanceValues[stateIdx];
      EEPROM.write(appearance_EEPROMAddress, appearance);
    }
    // clean
    if (index == 1) {
      int cleanValues[] = {0, 3, 2, 1};
      clean = cleanValues[stateIdx];
      EEPROM.write(clean_EEPROMAddress, clean);
    }
    // engine
    if (index == 2) {
      int engineValues[] = {0, 3, 2, 1};
      engine = engineValues[stateIdx];
      EEPROM.write(engine_EEPROMAddress, engine);
    }
    // wheel
    if (index == 3) {
      int wheelValues[] = {0, 3, 2, 1};
      wheel = wheelValues[stateIdx];
      EEPROM.write(wheel_EEPROMAddress, wheel);
    }
    // driver
    if (index == 4) {
      int driverValues[] = {0, 3, 2, 1};
      driver = driverValues[stateIdx];
      EEPROM.write(driver_EEPROMAddress, driver);
    }
    EEPROM.commit();
}

void enterCallSecondPanels() {
    currentState = Call_Second_Panels;
    button2ndIndex = 0;
    tft.pushImage(0, 0, 320, 240, call_panels[0]);
    tft.setCursor(25, 77);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(Rah);
    tft.setCursor(25, 117);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(Sarparast);
    tft.setCursor(25, 157);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(Emergency);
    drawCallOptions();
}

// Second panel of both Call and Setting: Go to next/previous button/page
void nextCallOption() {
  button2ndIndex = (button2ndIndex + 1) % 3;
  drawCallOptions();
}

void previousCallOption() {
  button2ndIndex = (button2ndIndex - 1 + 3) % 3;
  drawCallOptions();
}

// timer for third panel of call
void displayTime(unsigned long millis) {
    unsigned long seconds = millis / 1000;
    unsigned long minutes = seconds / 60;
    seconds = seconds % 60;
    if (millis / 1000 != lastDisplayedTime) {
        lastDisplayedTime = millis / 1000;

        // Clear previous time display (Optional: redraw only if necessary to avoid flickering)
        tft.fillRect(200, 157, 50, 20, background_color); // Adjust as per your display size

        // Format and display time as MM:SS
        char timeBuffer[6];
        sprintf(timeBuffer, "%02lu:%02lu", minutes, seconds);
        tft.setCursor(200, 157);
        tft.setTextColor(TFT_WHITE, background_color); // White text, black background
        tft.print(timeBuffer);
    }
}

void displaySavedTempBat(){
    tft.setTextColor(TFT_WHITE, background_color);
    int x = 137;
    int y = 76;
    int saved_temperature_max = EEPROM.read(temperature_max_EEPROMAddress);
    int saved_temperature_min = EEPROM.read(temperature_min_EEPROMAddress);
    int saved_battery_max = EEPROM.read(battery_max_EEPROMAddress);
    int saved_battery_min = EEPROM.read(battery_min_EEPROMAddress);
    if (saved_temperature_max != 0){
      tft.setCursor(x,y);
      tft.println(saved_temperature_max);
    }
    if (saved_temperature_min != 0){
      tft.setCursor(x,y+40);
      tft.println(saved_temperature_min);
    }
    if (saved_battery_max != 0){
      tft.setCursor(x,y+80);
      tft.println(saved_battery_max);
    }
    if (saved_battery_min != 0){
      tft.setCursor(x,y+120);
      tft.println(saved_battery_min);
    }
}

bool isDigitOrD(char incomingChar) {
  return ('0' <= incomingChar && incomingChar <= '9') || incomingChar == 'D';
}

// Temp and Battery 
void SensorTemperature() {
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    int tempInt = constrain(temperatureC, -99, 99);
    int saved_temperature_min = EEPROM.read(temperature_min_EEPROMAddress); 
    int saved_temperature_max = EEPROM.read(temperature_max_EEPROMAddress); 

    tft.pushImage(13, 60, 50, 50, tempInt >= saved_temperature_max ? epd_bitmap_temp_yellow : tempInt <= saved_temperature_min ? epd_bitmap_temp_red : saved_temperature_max < tempInt > saved_temperature_min ? epd_bitmap_temp_green : epd_bitmap_temp_gray);
    if (tempInt>=0){
    tft.fillRect(63, 60, 12, 40, background_color); 
    tft.setCursor(75, 85);
    tft.setTextColor(TFT_WHITE, background_color);
    tft.print(abs(tempInt));
    }
    else {
    tft.pushImage(63, 70, 12, 40, epd_bitmap_neg_assign);
    tft.setCursor(75, 85);
    tft.setTextColor(TFT_WHITE, background_color);
    tft.print(abs(tempInt));
    }

}

// battery
void BatteryVoltage() {
    int adcValue = analogRead(37); //GPIO23
    int voltage = (adcValue * 3.3) / 4095.0f;
    Serial.print("voltage"); Serial.print(voltage);
    int saved_battery_min = EEPROM.read(battery_min_EEPROMAddress); 
    int saved_battery_max = EEPROM.read(battery_max_EEPROMAddress); 

    tft.pushImage(13, 120, 50, 50, voltage >= saved_battery_max ? epd_bitmap_bat_yellow : voltage <= saved_battery_min ? epd_bitmap_bat_red : saved_battery_max < voltage > saved_battery_min ? epd_bitmap_bat_green : epd_bitmap_bat_gray);
    tft.setCursor(70, 138);
    tft.setTextColor(ILI9341_WHITE, background_color);
    tft.print(abs(voltage));
}

int readBatteryVoltage() {
    pinMode(23, INPUT_PULLDOWN);
    int voltageLevel = digitalRead(23);
    int result = (voltageLevel == HIGH) ? 1 : 0; //if it's 3.3v or high, the result is 1. else 0.
    // Serial.print("Battery voltage: ");
    digitalWrite(27, result);
    // Serial.println(result);
    tft.setCursor(70, 138);
    tft.print(result);
    return result;
}

// number of reported checks
void NumberOfReports() {
    int count = 0;
    for (int i = REPORT_ADD_OFFSET; i < REPORT_ADD_OFFSET + 5; i++){
      if (EEPROM.read(i) == 0)
        count++;
    } 

    tft.pushImage(13, 180, 50, 50, count >= 1 ? epd_bitmap_check_yellow : epd_bitmap_check_green);
    tft.setCursor(70, 198);
    tft.setTextColor(ILI9341_WHITE, background_color);
    tft.print(count);
}

// display date and time 
void displayDateTime() {
    writeStringToEEPROM(currentDate_EEPROMAddress, currentDate);
    writeStringToEEPROM(currentTime_EEPROMAddress, currentTime);
    writeStringToEEPROM(currentDay_EEPROMAddress, currentDay);
    EEPROM.commit();
    String saved_currentDate = readStringFromEEPROM(currentDate_EEPROMAddress); 
    String saved_currentTime = readStringFromEEPROM(currentTime_EEPROMAddress); 
    String saved_currentDay = readStringFromEEPROM(currentDay_EEPROMAddress); 
    tft.setCursor(78, 22);
    tft.setTextColor(ILI9341_WHITE, background_color);
    tft.print(saved_currentDate);
    tft.setCursor(206, 22);
    tft.setTextColor(ILI9341_WHITE, background_color);
    tft.print(saved_currentTime);
    tft.setCursor(272, 22);
    tft.setTextColor(ILI9341_WHITE, background_color);
    tft.print(saved_currentDay);
}

void writeStringToEEPROM(int addrOffset, const String &strToWrite) {
    byte len = strToWrite.length();
    EEPROM.write(addrOffset, len); // Write string length
    for (int i = 0; i < len; i++) {
        EEPROM.write(addrOffset + 1 + i, strToWrite[i]); // Write characters
    }
    EEPROM.commit();
}

String readStringFromEEPROM(int addrOffset) {
    int newStrLen = EEPROM.read(addrOffset); // Read length of string
    char data[newStrLen + 1]; // Allocate buffer
    
    for (int i = 0; i < newStrLen; i++) {
        data[i] = EEPROM.read(addrOffset + 1 + i); // Read characters
    }
    data[newStrLen] = '\0'; // Proper null termination
    
    return String(data); // Convert to String object and return
}
