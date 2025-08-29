#include "SharedPanel.h"
#include "CallPanel.h"

void handleCallSecondPanelsInput(char incomingChar) {
    if (incomingChar == '#') {
        nextCallOption();
    } else if (incomingChar == '*') {
        previousCallOption();
    } else if (incomingChar == 'D') {
      if (button2ndIndex == 0) { // Only enter second panel when check/report icon is selected
            enterCallThirdPanels();
            tft.pushImage(30, 146, 90, 29, epd_bitmap_rah);
        }
        else if (button2ndIndex == 1) { // Only enter second panel when setting icon is selected
            enterCallThirdPanels();
            tft.pushImage(30, 146, 90, 29, epd_bitmap_sarparast);
        }
        else if (button2ndIndex == 2) { // Only enter second panel when help icon is selected
            enterCallThirdPanels();
            tft.pushImage(30, 146, 90, 29, epd_bitmap_emergency);
        }
    } else if (incomingChar == 'A') {
        enterFirstPanels();
    }
}

void handleCallThirdPanelsInput(char incomingChar) {
    static bool flag = false;
    switch(incomingChar) {
        case 'D':
            if (!flag) {
                // Serial.print("Waiting for command...");
                while (!Serial.available()) {
                    delay(100);
                }
                String command = Serial.readStringUntil('\n');
                Serial.println("Received command: " + command);

                if (command.equals("call")) {
                    Serial.println("OK");
                    flag = true;
                    if (!timerRunning) {
                        // Start the timer
                        timerRunning = true;
                        timer = 0; // Reset the timer
                    }
                }
            } else {
                // Serial.print("Waiting for confirmation...");
                while (!Serial.available()) {
                    delay(100);
                }

                String response = Serial.readStringUntil('\n');
                // Serial.println("Received response: " + response);

                if (response.equals("ok")) {
                    flag = false;
                    // Serial.println("Confirmation received, resetting flag");
                }

                // Start the timer
                timerRunning = true;
                timer = 0; // Reset the timer
            }
            break;

        case 'B':
            // Stop the timer and reset immediately when 'B' is pressed
            timerRunning = false;
            displayTime(0);  // Reset display to 00:00
            break;

        case 'A':
            enterCallSecondPanels();
            break;

        default:
            // Handle other characters if needed
            break;
    }
}

void enterCallThirdPanels() {
    currentState = Call_Third_Panels;
    button3rdIndex = 0;
    tft.pushImage(0, 0, 320, 240, call_panels[1]);
}

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