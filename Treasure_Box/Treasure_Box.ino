#define Lock true
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Libraries*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#include <EEPROMex.h>                       // For EEPROM
#include <EEPROMVar.h>                      // For EEPROM
#include <TinyGPS++.h>                      // For gps
#include <SoftwareSerial.h>                 // For communicating with the gps
#include <math.h>                           // used by: GPS
#include <Wire.h>                           // For I2C devices
#include <LCD.h>                            // For LCD display
#include <LiquidCrystal_I2C.h>              // For LCD display
#ifdef Lock
#include <Servo.h>                          // For locking servo
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Variables*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//Pins, Definitions & Constants
#define GPSECHO  false
//#define SERIALECHO true
#define waypointTolerance  200             // Tolerance in meters to quest; once within this tolerance, will advance to the next quest
const int lidSensor = 5;                   // Pin connected to lid open sensor
#ifdef Lock
const int servoPin = 9;
Servo lock;
const byte engage = 0, disengage = 180;
#endif
static const int RXPin = 3, TXPin = 2;
static const int GPSBaud = 9600;

//Variables
struct coordinates {
  double latitude;
  double longitude;
};
coordinates target;

struct addresses {
  int latitude;
  int longitude;
};

addresses address1;
addresses address2;
addresses address3;
addresses address4;
addresses address5;

struct dateTime {
  int Year;
  int Month;
  int Date;
};

dateTime current;
dateTime past {2015, 8, 8};
dateTime timeElapsed;

unsigned long distance;
byte currentQuest, questAddress;
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
  getAddresses();                     // Always getAddresses() first so they don't get mixed up
#ifdef SERIALECHO
  Serial.begin(115200);
#endif
  ss.begin(9600);
  lock.attach(servoPin);
  lock.write(engage);
  startLCD();
  if (!coordinateCheck()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("EEPROM error!!!"));
    lcd.setCursor(0, 0);
    lcd.print(F("Call support now"));
  }
  currentQuest = EEPROM.read(questAddress);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Loop*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void loop()
{
  switch (currentQuest) {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 1*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    case 1:
      target.latitude = EEPROM.read(address1.latitude);
      target.longitude = EEPROM.read(address1.longitude);
      distance = (unsigned long)TinyGPSPlus::distanceBetween(
                   gps.location.lat(),
                   gps.location.lng(),
                   target.latitude,
                   target.longitude);
      if (distance <= waypointTolerance) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Quest 1 complete!"));
#ifdef SERIALECHO
        Serial.println(F("Quest 1 complete!"));
#endif
        EEPROM.update(questAddress, 2);
        currentQuest = EEPROM.read(questAddress);
      }
      else {
        for (int i = 3; i >= 0; i--) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Can you hear the"));
          lcd.setCursor(0, 1);
          lcd.print(F("music in the Valley?"));
          smartDelay(2000);
        }
#ifdef SERIALECHO
        Serial.println(F("Can you hear the music in the Valley?"));
        Serial.println(F("Go to where you first met in the Valley and get a beer!"));
#endif
      }
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 2*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    case 2:
      target.latitude = EEPROM.read(address2.latitude);
      target.longitude = EEPROM.read(address2.longitude);
      distance = (unsigned long)TinyGPSPlus::distanceBetween(
                   gps.location.lat(),
                   gps.location.lng(),
                   target.latitude,
                   target.longitude);
      if (distance <= waypointTolerance*3) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Quest 2 complete!"));
#ifdef SERIALECHO
        Serial.println(F("Quest 2 complete!"));
#endif
        EEPROM.update(questAddress, 3);
        currentQuest = EEPROM.read(questAddress);
      }
      else {
        for (int i = 3; i >= 0; i--) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Remember the Bounty"));
          lcd.setCursor(0, 1);
          lcd.print(F("Hunter?"));
          lcd.setCursor(0, 2);
          lcd.print(F("Its now time to"));
          lcd.setCursor(0, 3);
          lcd.print(F("catch another!"));
          smartDelay(2000);
        }
#ifdef SERIALECHO
        Serial.println(F("Remember the Bounty Hunter?"));
        Serial.println(F("Its now time to catch another!"));
#endif
      }
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 3*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    case 3:
      target.latitude = EEPROM.read(address3.latitude);
      target.longitude = EEPROM.read(address3.longitude);
      distance = (unsigned long)TinyGPSPlus::distanceBetween(
                   gps.location.lat(),
                   gps.location.lng(),
                   target.latitude,
                   target.longitude);
      if (distance <= waypointTolerance*15) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Quest 3 complete!"));
#ifdef SERIALECHO
        Serial.println(F("Quest 3 complete!"));
#endif
        EEPROM.update(questAddress, 4);
        currentQuest = EEPROM.read(questAddress);
      }
      else {
        for (int i = 3; i >= 0; i--) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("Nothing beats a bit"));
          lcd.setCursor(0, 1);
          lcd.print(F("of sand, surf & sun!"));
          lcd.setCursor(0, 2);
          lcd.print(F("(Don't forget the"));
          lcd.setCursor(0, 3);
          lcd.print(F("ice cream!)"));
          smartDelay(2000);
        }
#ifdef SERIALECHO
        Serial.println(F("Nothing beats a bit of sand surf & sun"));
        Serial.println(F("(Don't forget the ice cream!"));
#endif
      }
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 4*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    case 4:
      target.latitude = EEPROM.read(address4.latitude);
      target.longitude = EEPROM.read(address4.longitude);
      distance = (unsigned long)TinyGPSPlus::distanceBetween(
                   gps.location.lat(),
                   gps.location.lng(),
                   target.latitude,
                   target.longitude);
      if (distance <= waypointTolerance*5) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Quest 4 complete!"));
#ifdef SERIALECHO
        Serial.println(F("Quest 4 complete!"));
#endif
        EEPROM.update(questAddress, 5);
        currentQuest = EEPROM.read(questAddress);
      }
      else {
        for (int i = 3; i >= 0; i--) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(F("The truth is - "));
          lcd.setCursor(3, 1);
          lcd.print(F("The Honeymoon"));
          lcd.setCursor(7, 2);
          lcd.print(F("NEVER"));
          lcd.setCursor(6, 3);
          lcd.print(F("ends! :D"));
          smartDelay(2000);
        }
#ifdef SERIALECHO
        Serial.println(F("The truth is - "));
        Serial.println(F("The Honeymoon NEVER ends! :D"));
#endif
      }
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 5*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    case 5:
      target.latitude = EEPROM.read(address5.latitude);
      target.longitude = EEPROM.read(address5.longitude);
      distance = (unsigned long)TinyGPSPlus::distanceBetween(
                   gps.location.lat(),
                   gps.location.lng(),
                   target.latitude,
                   target.longitude);
      if (distance <= waypointTolerance) {
        lcd.clear();
        lcd.setCursor(6, 0);
        lcd.print(F("Woohoo!"));
        lcd.setCursor(1, 1);
        lcd.print(F("Congratulations!!!"));
        lock.write(disengage);
#ifdef SERIALECHO
        Serial.println(F("All quests completed successfully!!!"));
#endif
        EEPROM.update(questAddress, 6);
        currentQuest = EEPROM.read(questAddress);
        smartDelay(2000);
      }
      else {
        for (int i = 3; i >= 0; i--) {
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print(F("Its time to go home!"));
          smartDelay(2000);
        }
#ifdef SERIALECHO
        Serial.println(F("Its time to go home!"));
#endif
      }
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Quest 6*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    case 6:
      lock.write(disengage);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("You have been married"));
      lcd.setCursor(8, 1);
      lcd.print(F("for"));
      //timeSinceMarriage(years, months, days);
      timeSince(current.Year, current.Month, current.Date, past.Year, past.Month, past.Date);
      char printBuffer[21];
      sprintf(printBuffer, "%d years, %d months", years, months);
      lcd.setCursor(0, 2);
      lcd.print(printBuffer);
      sprintf(printBuffer, "     & %d days      ", days);
      lcd.setCursor(0, 3);
      lcd.print(printBuffer);
      smartDelay(2000);
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Default*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    default:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Waiting for GPS"));
#ifdef SERIALECHO
      Serial.println(F("Waiting for GPS"));
#endif
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
#ifdef SERIALECHO
    Serial.println(F("No GPS data received: check wiring"));
#endif
  }
}
