#include "SharedPanel.h"
#include "ReportPanel.h"

void handleReportSecondPanelsInput(char incomingChar) {
    if (incomingChar == '#') {
        nextOption();
    } else if (incomingChar == '*') {
        previousOption();
    } else if (incomingChar == 'D') {
        enterReportThirdPanels();
    } else if (incomingChar == 'A') {
        enterFirstPanels();
    }
}

void handleReportThirdPanelsInput(char incomingChar) {
    if (incomingChar == '#') {
        nextSituationOption();
    } else if (incomingChar == '*') {
        previousSituationOption();
    } else if (incomingChar == 'D') {
        submitReport();
    } else if (incomingChar == 'A') {
        enterReportSecondPanels();
    }
}

// Second panel of Report: Go to next/previous button/page
void nextOption() {
  button2ndIndex = (button2ndIndex + 1) % 6;
  drawOptions();
}

void previousOption() {
  button2ndIndex = (button2ndIndex - 1 + 6) % 6;
  drawOptions();
}

// Third panel of Report: Go to next/previous button
void nextSituationOption() {
    button3rdIndex = (button3rdIndex + 1) % 3;
    drawSituationOptions();
}

void previousSituationOption() {
    button3rdIndex = (button3rdIndex - 1 + 3) % 3;
    drawSituationOptions();
}

void submitReport() {
    if (selectedStateIndex == (button3rdIndex + 1)) {
      currentSubOptionState[button2ndIndex] = SubOptionState(selectedStateIndex);
      EEPROM.write(button2ndIndex + REPORT_ADD_OFFSET, selectedStateIndex);
      selectedStateIndex = 0;
      button3rdIndex = 0;
      enterReportSecondPanels();
    } else {
      selectedStateIndex = button3rdIndex + 1;
      drawSituationOptions();
    }
}

