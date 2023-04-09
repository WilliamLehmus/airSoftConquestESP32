/*
Airsoft Zone Conquest
Hardware and Software by William Lehmus (william_lehmus@hotmail.com)

Prerequisities
4 Push buttons that control both the setup flow and the in-game actions for capturing zones. 

Setup flow:
- Set hours the game is going to run. 
- Set minutes the game is going to run
- Setup capture time. For how long does a button have to be pressed before the zone is capped. 
- Confirm settings

Main game: 
- The game starts with no owner on the zone and no scores are counted, the game timer will still run though. 
- When a zone is captured by holding the corresponding button for the team, the zone is captured. 

LED logic:
No Lights - The game has just started and the zone has no owner
Blinking Light - During capture the LED on the arcade button will blink on and off until the zone is captured
Solid light - When a zone is captured, the corresponding LED will light up. 


GPIO Overview
https://www.botnroll.com/en/esp/3639-wemos-d1-r32-w-esp32-uno-r3-pinout.html
https://bpb-ap-se2.wpmucdn.com/blogs.auckland.ac.nz/dist/9/698/files/2021/08/2_Pinout_D1_R32.png

Hardware: ESP32 Uno based on Weemos ESP32 D1
Board in Arduino IDE board manager: ESP32 Dev Module
CPU Frequency 240MHZ (Wifi / Bt)
Core Debug Level: None 
Erase all flash before upload: Disabled
Events Run on Core: 1
Flash Frequecy: 80 Mhz
Flash Size 4 MB (32mb)
Flash Mode: QIO
Arduino Runs on Core: 1
Partition Scheme: Default 4Mb with Spiffs (1.2MB App / 1.5MB Spiffs)
PSRAM: Disabled
Upload Sped: 921600 baud



Dependencies:
ButtonDebounce by Maykon L. Capellari V1.0.1
Adafruit SSD1306 by Adafruit v.2.5.7
Adafruit GFX by Adafruit
SimpleTimer by Natan Lisowski v2.1.7


*/

//OLED & I2C
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ButtonDebounce.h>  //Easy button debounce

bool skipSetup = true; //Bypass setup for debugging


//OLED SETUP
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);


//Arcade Button Pins
int redButtonPin = 26;
int blueButtonPin = 25;
int yellowButtonPin = 17;
int greenButtonPin = 16;

//Arcade Light Pins
int redButtonLEDPin = 12;
int blueButtonLEDPin = 13;
int yellowButtonLEDPin = 5;
int greenButtonLEDPin = 23;

//Game logic and configuration
int gameState = 0;  //0 = setup, 1 = running, 3 = gameOver Game first enters config and when it's complete goes to running.
int setupFlow = 0;  //Goes from 0 = setup game time hours, 1 = setup gametime minutes, 2 = setup capturetime to hold button

//Score counters
int redScore = 0;             // the current score of the red team 
int blueScore = 0;            // the current score of the blue team 
int greenScore = 0;           // the current score of the green team 
int yellowScore = 0;          // the current score of the yellow team 

//Zone and capture settings
const int scoreIntervalSeconds = 30;  // the time interval to update the score. 60 is 1 minute.
bool anyCaptureButtonPressedFlag = false;
ButtonDebounce *activeButton = NULL; //Pointer to button
String zoneOwnerShip = ""; //redTeam, blueTeam, yellowTeam, greenTeam
String currentlyCapturing = "";

//Default values
int gameTimeHours = 1;  //Initual Setup of game time in hours
int gameTimeMinutes = 0; //Initual Setup of game time in hours
int remainingTimeMinutes = 0; //Game time converted to minutes
int captureTimeSeconds = 30;  //Time in seconds needed to hold the arcade capture buttons
unsigned long remainingGameTimeInMillis = 0;

//Debounce for buttons setup
ButtonDebounce redButton(redButtonPin, 150);  //Button, debounce with INPUT_PULLUP
ButtonDebounce blueButton(blueButtonPin, 150);
ButtonDebounce yellowButton(yellowButtonPin, 150);
ButtonDebounce greenButton(greenButtonPin, 150);

//Extra debounce option to avoid insta clicking through setup flow
bool blockEnterButton = true;

//Main game timer variables
unsigned long previousMillis = 0; // stores the previous time the loop was run
const long interval = 60000; // the interval at which to update the timer (in milliseconds)
unsigned long startTime;
int hoursRemaining;     
int minutesRemaining;

void setup() {
  pinMode(redButtonLEDPin, OUTPUT);
  pinMode(blueButtonLEDPin, OUTPUT);
  pinMode(yellowButtonLEDPin, OUTPUT);
  pinMode(greenButtonLEDPin, OUTPUT);

  //Setup timers


  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  splashScreen();
  startupLEDsequence();

  //Extra ground
  Serial.println("Setup Done");
}

void loop() {
  if (gameState == 0 && skipSetup) byPassSetup();
  else if (gameState == 0) setupGameMode();
  if (gameState == 1) gameRunning();
  if (gameState == 2) gameOver();
}
