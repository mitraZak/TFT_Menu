// bat and temp on 5th panel of setting
const int numbersCount = 4;
int numberInputIdx = 0;
int digitOfNumberInputIdx = 0;
int numberInputs[numbersCount];
int currentNumber = 0;
int pos_incomingChar = 0;
int pos_X_incomingChar = 0;
const int temperature_max_EEPROMAddress = 101, temperature_min_EEPROMAddress = 103, battery_max_EEPROMAddress = 105, battery_min_EEPROMAddress = 107; // EEPROM address 
int temperature_max, temperature_min, battery_max, battery_min;

void handleSettingSecondPanelsInput(char incomingChar);
void handleSettingThirdPanelsInput(char incomingChar);
void handleSettingFourthPanelsInput(char incomingChar);
void handleSettingFifthPanelsInput(char incomingChar);
void enterSettingFourthPanels();
void enterSettingThirdPanels();
void enterSettingFifthPanels();
void TempBatFromFifthSetting(char incomingChar);