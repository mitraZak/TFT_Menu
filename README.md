# TFT_Menu
This repository contains a menu system with bitmap-based display screens, shown on a TFT ILI9341 and navigated through a 4x4 matrix keypad. The bitmaps are converted and embedded directly into C code.

# System Architecture

- Input Handling: To optimize memory, keypad input is processed on an STM32F103C8T6, which sends the selected key to the ESP32 Dev Module via UART.

- Display: The ESP32 controls the TFT ILI9341 over SPI and manages the menu interface.

- Menu Logic: Each keypad input triggers specific menu functions, while background features (e.g., DS18B20 1-Wire temperature sensor) run automatically.

- Data Storage: User configurations are saved in EEPROM to ensure data persistence during power loss.

# Extendability
The system includes placeholders for future functionality, such as storing emergency contact numbers and integrating a SIM868 module for calling and GPS tracking.
