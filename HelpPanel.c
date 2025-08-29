#include "SharedPanel.h"
#include "HelpPanel.h"

void handleHelpSecondPanelsInput(char incomingChar) {
    switch(incomingChar) {
        case '#':
            HelpPanelcurrentIndex++;
            if (HelpPanelcurrentIndex >= 2) {
                HelpPanelcurrentIndex = 0; // to the beginning
            }
            tft.pushImage(0, 0, 320, 240, help_panels[HelpPanelcurrentIndex]);
            break;
        case '*':
            HelpPanelcurrentIndex--;
            if (HelpPanelcurrentIndex < 0) {
                HelpPanelcurrentIndex = 1; // to the end
            }
            tft.pushImage(0, 0, 320, 240, help_panels[HelpPanelcurrentIndex]);
            break;
        case 'A':
            enterFirstPanels();
            return;
    }
}
