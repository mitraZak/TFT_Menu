// Phone Numbers
const int Rah_EEPROMAddress = 60, Sarparast_EEPROMAddress = 72, Emergency_EEPROMAddress = 83;
String Rah = "PHONE_NUMBER";
String Sarparast = "PHONE_NUMBER";
String Emergency = "PHONE_NUMBER";

void handleCallSecondPanelsInput(char incomingChar);
void handleCallThirdPanelsInput(char incomingChar);
void enterCallThirdPanels();
void displayTime(unsigned long millis);