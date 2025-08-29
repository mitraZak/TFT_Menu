#include "Common.h"

const int appearance_EEPROMAddress = 4, clean_EEPROMAddress = 5, engine_EEPROMAddress = 6, wheel_EEPROMAddress = 7, driver_EEPROMAddress = 8;
int appearance = 0;
int clean = 0;
int engine = 0;
int wheel = 0;
int driver = 0; 

void handleSerialInput();
void enterReportSecondPanels();
void enterSettingSecondPanels();
void enterHelpSecondPanels();
void enterReportThirdPanels();
void enterFirstPanels();
void drawOptions();
void drawOption(int optionButton, bool isSelected);
void drawStateOption(int index, int stateIdx);
void enterCallSecondPanels();
void nextCallOption();
void previousCallOption();
void displayTime(unsigned long millis);
void displaySavedTempBat();
bool isDigitOrD(char incomingChar);
void SensorTemperature();
void BatteryVoltage();
int readBatteryVoltage();
void NumberOfReports(){return};
void NumberOfReports();
void displayDateTime();
void writeStringToEEPROM(int addrOffset, const String &strToWrite);
String readStringFromEEPROM(int addrOffset){return};
