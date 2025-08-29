#include <OneWire.h>
#include <DallasTemperature.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <EEPROM.h>
#include <elapsedMillis.h>
#include <WiFi.h>

#define ONE_WIRE_BUS 26 // temp sensor
#define REPORT_ADD_OFFSET 95 

// temp sensor
HardwareSerial mySerial(1);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// call timer
elapsedMillis timer;  

//WiFi
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASS";
IPAddress localIP;


// tft
TFT_eSPI tft = TFT_eSPI();

uint16_t background_color = 0x298b;
uint16_t gray_background_color = 0x2108;

const uint16_t* images[] = {epd_bitmap_report, epd_bitmap_setting, epd_bitmap_help, epd_bitmap_call}; // main panels
const uint16_t* subImages[] = {epd_bitmap_sub1_report, epd_bitmap_sub2_report}; // check (report) panel, first and second frames
const uint16_t* subOptions[] = {epd_bitmap_op1blue, epd_bitmap_op1gray, epd_bitmap_op2blue, epd_bitmap_op2gray, epd_bitmap_op3blue, 
                                epd_bitmap_op3gray, epd_bitmap_op4blue, epd_bitmap_op4gray, epd_bitmap_op5blue, epd_bitmap_op5gray,
                                epd_bitmap_op6blue, epd_bitmap_op6gray}; // 1 to 6 for option (gray) and selection (blue) for second panel

const uint16_t* reportImages[] = {epd_bitmap_neutral_report, epd_bitmap_good_report, epd_bitmap_normal_report, 
                                  epd_bitmap_bad_report}; // options on third panel

const uint16_t* subOptionStates[] = {epd_bitmap_neutral_report_appearance, epd_bitmap_good_report_appearance, epd_bitmap_normal_report_appearance,
                                     epd_bitmap_bad_report_appearance, epd_bitmap_neutral_report_clean, epd_bitmap_good_report_clean, 
                                     epd_bitmap_normal_report_clean, epd_bitmap_bad_report_clean, epd_bitmap_neutral_report_engine, 
                                     epd_bitmap_good_report_engine, epd_bitmap_normal_report_engine, epd_bitmap_bad_report_engine, 
                                     epd_bitmap_neutral_report_wheel, epd_bitmap_good_report_wheel, epd_bitmap_normal_report_wheel, 
                                     epd_bitmap_bad_report_wheel, epd_bitmap_neutral_report_driver, epd_bitmap_good_report_driver, 
                                     epd_bitmap_normal_report_driver, epd_bitmap_bad_report_driver}; // all situations for options in second panel when selected in first panel
                                     
const uint16_t* help_panels[] = {epd_bitmap_help_1, epd_bitmap_help_2};
const uint16_t* call_panels[] = {epd_bitmap_call_1, epd_bitmap_call_2};

enum State { First_Panels, Report_Second_Panels, Report_Third_Panels, Setting_Second_Panels, Setting_Third_Panels, Setting_Fourth_Panels, Setting_Fifth_Panels, Help_Second_Panels, Call_Second_Panels, Call_Third_Panels};
State currentState = First_Panels;

enum SubOptionState { Neutral, Good, Normal, Bad };
int currentSubOptionState[] = { Neutral, Neutral, Neutral, Neutral, Neutral };

int selectedStateIndex = 0;
int button1stIndex = 0;
int button2ndIndex = 0;
int button3rdIndex = 0;
bool isReportSubmitted = false;
int submittedOptionIndex = -1;
int button1stdIndex_call = 0;
int HelpPanelcurrentIndex = 0;

// timer for call variables:
bool timerRunning = false;    // State to track if the timer is running
unsigned long lastDisplayedTime = 0;   // To store the time when timer started