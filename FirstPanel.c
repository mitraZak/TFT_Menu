#include "SharedPanel.h"
#include "FirstPanel.h"

// Handle incoming char
void handleFirstPanelsInput(char incomingChar) {
    if (incomingChar == '#') {
        button1stIndex = (button1stIndex + 1) % 4;
        tft.pushImage(113, 61, 190, 109, images[button1stIndex]);
    } else if (incomingChar == '*') {
        button1stIndex = (button1stIndex - 1 + 4) % 4;
        tft.pushImage(113, 61, 190, 109, images[button1stIndex]);
    } else if (incomingChar == 'D'){
        if (button1stIndex == 0) { // Only enter second panel when check/report icon is selected
            enterReportSecondPanels();
        }
        else if (button1stIndex == 1) { // Only enter second panel when setting icon is selected
            enterSettingSecondPanels();
        }
        else if (button1stIndex == 2) { // Only enter second panel when help icon is selected
            enterHelpSecondPanels();
        }
        else if (button1stIndex == 3) { // Only enter second panel when call icon is selected
            enterCallSecondPanels();
        }
    }
}