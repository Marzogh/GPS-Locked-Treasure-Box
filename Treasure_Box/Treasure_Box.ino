//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Libraries*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#include <EEPROMex.h>                       // For EEPROM
#include <EEPROMVar.h>                      // For EEPROM
#include <TinyGPS++.h>                      // For gps
#include <SoftwareSerial.h>                 // For communicating with the gps
#include <math.h>                           // used by: GPS
#include <Wire.h>                           // For I2C devices
#include <LCD.h>                            // For LCD display
#include <LiquidCrystal_I2C.h>              // For LCD display
#include <Servo.h>                          // For locking servo

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Variables*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//Pins, Definitions & Constants
//#define GPSECHO
//#define SERIALECHO
#define waypointTolerance  200             // Tolerance in meters to quest; once within this tolerance, will advance to the next quest
#define maxAttempts 10                     // Maximum number of attempts before distance to target is displayed
#define questResetPin 4                    // Connecting this pin to GND and pressing the Reset button on the board resets the quest counter.
#define IOPin 5                            // This pin is connected to the off pin of the Pololu pushbutton switch to turn off the system
#define emergencyOpenPin 6                 // Using the built in backdoor entry pushes this pin high causing the lock to open after two minutes
const int servoPin = 9;
Servo lock;
const byte engage = 0, disengage = 180;
static const int RXPin = 3, TXPin = 2;     //Connect TX of GPS to 3 and RX of GPS to 2
static const int GPSBaud = 9600;

//Variables
struct coordinates {                       // Stores quest coordinates
  double latitude;
  double longitude;
};
coordinates quest1;
coordinates quest2;
coordinates quest3;
coordinates quest4;
coordinates quest5;
coordinates target;

struct addresses {                        // Stores EEPROM addresses for quest coordinates
  int latitude;
  int longitude;
};

addresses Address1;
addresses Address2;
addresses Address3;
addresses Address4;
addresses Address5;

struct dateTime {                         // Stores date and time for DateTime calculations
  int Year;
  int Month;
  int Date;
};

dateTime current;
dateTime past;
dateTime timeElapsed;

float distance;
byte currentQuest, attempts;
byte questAddress, yearAddress, monthAddress, dateAddress,
     currentAttempts, quest1Attempts, quest2Attempts, quest3Attempts, quest4Attempts, quest5Attempts,
     distanceClueBoolean;
bool distanceClue;
int years, months, days;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Objects*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
//Initiate LiquidCrystal object for LCD. (0x27 is the I2C bus address for an unmodified I2C backpack)
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Setup*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(IOPin, OUTPUT);
  digitalWrite(IOPin, LOW);
  digitalWrite(13, LOW);
#ifdef SERIALECHO
  Serial.begin(115200);
#endif

  getAddresses();
  pinMode(questResetPin, INPUT_PULLUP);
  if (digitalRead(questResetPin) == LOW)
    checkForReset();

  currentQuest = EEPROM.read(questAddress);

  ss.begin(9600);
  lock.attach(servoPin);
  lock.write(engage);
  startLCD();

  pinMode(emergencyOpenPin, INPUT_PULLUP);
  if (digitalRead(emergencyOpenPin) == LOW)
    emergencyOpen();

#ifdef SERIALECHO
  Serial.print (F("The current quest is: Quest "));
  Serial.println(currentQuest);
#endif

  lcd.clear();
  if (currentQuest > 0 && currentQuest < 6) {
    char printBuffer[8];
    sprintf(printBuffer, "Quest %d", currentQuest);
    lcd.setCursor(0, 0);
    lcd.print(F("Here's your clue for"));
    lcd.setCursor(6, 2);
    lcd.print(printBuffer);
    smartDelay(2000);
    lcd.clear();
    attempts = EEPROM.read(currentAttempts);
    attempts++;
    EEPROM.updateByte(currentAttempts, attempts);

    if (attempts >= maxAttempts)
      EEPROM.updateBit(distanceClueBoolean, 0, 1);
    else
      EEPROM.updateBit(distanceClueBoolean, 0, 0);

#ifdef SERIALECHO
    Serial.print(F("Current Tries: "));
    Serial.println(EEPROM.read(currentAttempts));
#endif
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Loop*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void loop()
{
  distanceClue = EEPROM.readBit(distanceClueBoolean, 0);
  updateDate();
  int repeats = 0;
  do {
    switch (currentQuest) {
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 0*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      case 0:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("5 quests to go, with"));
        lcd.setCursor(0, 1);
        lcd.print(F("fond memories galore"));
        lcd.setCursor(0, 2);
        lcd.print(F("......"));
        smartDelay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Have lots of fun on the way!"));
        smartDelay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Here we go...."));
        EEPROM.updateByte(questAddress, 1);
        currentQuest = EEPROM.read(questAddress);
        smartDelay(3000);
#ifdef SERIALECHO
        Serial.println("Here we go!! The quest begins now. Have fun!");
#endif
        break;
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 1*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      case 1:
        target.latitude = quest1.latitude;
        target.longitude = quest1.longitude;
        distance = (unsigned long)TinyGPSPlus::distanceBetween(
                     gps.location.lat(),
                     gps.location.lng(),
                     target.latitude,
                     target.longitude);
#ifdef SERIALECHO
        printQuestDistance();
#endif
        if (distance <= waypointTolerance) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Quest 1 complete!"));
          smartDelay(2000);
#ifdef SERIALECHO
          Serial.println(F("Quest 1 complete!"));
#endif
          EEPROM.updateByte(questAddress, 2);
          EEPROM.updateByte(quest1Attempts, attempts);
          EEPROM.updateByte(currentAttempts, 0);
          currentQuest = EEPROM.read(questAddress);
        }
        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Can you hear the"));
          lcd.setCursor(0, 1);
          lcd.print(F("music in the Valley?"));
          smartDelay(2000);

          if (distanceClue)
            lcdPrintQuestDistance();

#ifdef SERIALECHO
          Serial.println(F("Can you hear the music in the Valley?"));
          Serial.println(F("Go to where you first met in the Valley and get a beer!"));
#endif
        }
        break;

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 2*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      case 2:
        target.latitude = quest2.latitude;
        target.longitude = quest2.longitude;
        distance = (unsigned long)TinyGPSPlus::distanceBetween(
                     gps.location.lat(),
                     gps.location.lng(),
                     target.latitude,
                     target.longitude);
#ifdef SERIALECHO
        printQuestDistance();
#endif
        if (distance <= waypointTolerance * 3) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Quest 2 complete!"));
          smartDelay(2000);
#ifdef SERIALECHO
          Serial.println(F("Quest 2 complete!"));
#endif
          EEPROM.updateByte(questAddress, 3);
          EEPROM.updateByte(quest2Attempts, attempts);
          EEPROM.updateByte(currentAttempts, 0);
          currentQuest = EEPROM.read(questAddress);
        }
        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Remember the Bounty"));
          lcd.setCursor(6, 1);
          lcd.print(F("Hunter?"));
          lcd.setCursor(3, 2);
          lcd.print(F("Its now time to"));
          lcd.setCursor(3, 3);
          lcd.print(F("catch another!!"));
          smartDelay(2000);

          if (distanceClue)
            lcdPrintQuestDistance();

#ifdef SERIALECHO
          Serial.println(F("Remember the Bounty Hunter?"));
          Serial.println(F("Its now time to catch another!"));
#endif
        }
        break;

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 3*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      case 3:
        target.latitude = quest3.latitude;
        target.longitude = quest3.longitude;
        distance = (unsigned long)TinyGPSPlus::distanceBetween(
                     gps.location.lat(),
                     gps.location.lng(),
                     target.latitude,
                     target.longitude);
#ifdef SERIALECHO
        printQuestDistance();
#endif
        if (distance <= waypointTolerance * 15) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Quest 3 complete!"));
          smartDelay(2000);
#ifdef SERIALECHO
          Serial.println(F("Quest 3 complete!"));
#endif
          EEPROM.updateByte(questAddress, 4);
          EEPROM.updateByte(quest3Attempts, attempts);
          EEPROM.updateByte(currentAttempts, 0);
          currentQuest = EEPROM.read(questAddress);
        }
        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Nothing beats a bit"));
          lcd.setCursor(0, 1);
          lcd.print(F("of sand, surf & sun!"));
          lcd.setCursor(2, 2);
          lcd.print(F("(Don't forget the"));
          lcd.setCursor(4, 3);
          lcd.print(F("ice cream!)"));
          smartDelay(2000);

          if (distanceClue)
            lcdPrintQuestDistance();

#ifdef SERIALECHO
          Serial.println(F("Nothing beats a bit of sand surf & sun"));
          Serial.println(F("(Don't forget the ice cream!)"));
#endif
        }
        break;

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 4*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      case 4:
        target.latitude = quest4.latitude;
        target.longitude = quest4.longitude;
        distance = (unsigned long)TinyGPSPlus::distanceBetween(
                     gps.location.lat(),
                     gps.location.lng(),
                     target.latitude,
                     target.longitude);
#ifdef SERIALECHO
        printQuestDistance();
#endif
        if (distance <= waypointTolerance * 5) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Quest 4 complete!"));
          smartDelay(2000);
#ifdef SERIALECHO
          Serial.println(F("Quest 4 complete!"));
#endif
          EEPROM.updateByte(questAddress, 5);
          EEPROM.updateByte(quest4Attempts, attempts);
          EEPROM.updateByte(currentAttempts, 0);
          currentQuest = EEPROM.read(questAddress);
        }
        else {
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print(F("The truth is - "));
          lcd.setCursor(3, 1);
          lcd.print(F("The Honeymoon"));
          lcd.setCursor(7, 2);
          lcd.print(F("NEVER"));
          lcd.setCursor(8, 3);
          lcd.print(F("ends! :D"));
          smartDelay(2000);

          if (distanceClue)
            lcdPrintQuestDistance();

#ifdef SERIALECHO
          Serial.println(F("The truth is - "));
          Serial.println(F("The Honeymoon NEVER ends! :D"));
#endif
        }
        break;

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 5*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      case 5:
        target.latitude = quest5.latitude;
        target.longitude = quest5.longitude;
        distance = (unsigned long)TinyGPSPlus::distanceBetween(
                     gps.location.lat(),
                     gps.location.lng(),
                     target.latitude,
                     target.longitude);
#ifdef SERIALECHO
        printQuestDistance();
#endif
        if (distance <= waypointTolerance) {
          lcd.clear();
          lcd.setCursor(5, 1);
          lcd.print(F("Woohoo!!!"));
          lcd.setCursor(1, 2);
          lcd.print(F("Congratulations!!!"));
          lock.write(disengage);
          smartDelay(2000);
#ifdef SERIALECHO
          Serial.println(F("All quests completed successfully!!!"));
#endif
          EEPROM.updateByte(questAddress, 6);
          EEPROM.updateByte(quest5Attempts, attempts);
          EEPROM.updateByte(currentAttempts, 0);
          currentQuest = EEPROM.read(questAddress);
          smartDelay(2000);

          if (distanceClue)
            lcdPrintQuestDistance();

        }
        else {
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print(F("Home is where"));
          lcd.setCursor(3, 1);
          lcd.print(F("the heart is."));
          lcd.setCursor(0, 3);
          lcd.print(F("Its time to go home!"));
          smartDelay(2000);
#ifdef SERIALECHO
          Serial.println(F("Its time to go home!"));
#endif
        }
        break;

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 6*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      case 6:
        lock.write(disengage);
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print(F("You have been"));
        lcd.setCursor(5, 1);
        lcd.print(F("married for"));
        timeSince();                    // Calculates and prints time elapsed since event on LCD
        char printBuffer[21];
        sprintf(printBuffer, "%d years, %d months", timeElapsed.Year, timeElapsed.Month);
        lcd.setCursor(2, 2);
        lcd.print(printBuffer);
        sprintf(printBuffer, "     & %d days      ", timeElapsed.Date);
        lcd.setCursor(0, 3);
        lcd.print(printBuffer);
        smartDelay(2000);
        break;

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Default*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
      default:
        EEPROM.updateByte(questAddress, 0);
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print(F("GPS Treasure Box"));
        lcd.setCursor(7, 2);
        lcd.print(F("Mark I"));
        break;
    }
    smartDelay(2000);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*No GPS*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    if (millis() > 5000 && gps.charsProcessed() < 10) {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(F("No GPS data received"));
      lcd.setCursor(4, 2);
      lcd.print(F("Check Wiring"));
      smartDelay(2000);
#ifdef SERIALECHO
      Serial.println(F("No GPS data received: check wiring"));
#endif
    }
  } while (repeats < 4);
  digitalWrite(IOPin, HIGH);
}
