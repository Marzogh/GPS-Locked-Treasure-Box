//#define LOCK
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Libraries*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
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

//Pins & Definitions
#define waypointTolerance  50             // tolerance in meters to waypoint; once within this tolerance, will advance to the next waypoint
const int lidSensor = 5;                        // Pin connected to lid open sensor
#ifdef Lock
const int servoPin = 9;
#endif
#ifndef Lock
const int LEDPin = 9;
#endif
#define GPSECHO  false
#define SERIALECHO true

//Variables
static const int RXPin = 3, TXPin = 2;
static const uint32_t GPSBaud = 9600;
//static const double targetLat = 51.508131, targetLong = -0.128002;
static const double targetLat = -27.486890, targetLong = 153.013860;
unsigned long distance;
uint8_t tries = 101;
#ifdef Lock
uint8_t engage = 0, disengage = 180;
#endif

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); //Initiate LiquidCrystal object for LCD. (0x27 is the I2C bus address for an unmodified I2C backpack)

#ifdef Lock
Servo lock;
#endif

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  startLCD();
}

void loop()
{
  //static const double targetLat = 51.508131, targetLong = -0.128002;

   distance =
     (unsigned long)TinyGPSPlus::distanceBetween(
       gps.location.lat(),
       gps.location.lng(),
       targetLat,
       targetLong);
   printInt(distance, gps.location.isValid(), 9);
   Serial.println();
   uint8_t i = 3;
   while (i > 0, i--) {
     if (distance <= waypointTolerance) {
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(F("You have arrived!"));
       Serial.println(F("You have arrived!"));
     }
     else if (distance <= 1000) {
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(F("You are now "));
       lcd.setCursor(0, 1);
       lcd.print(distance);
       lcd.print(F(" m away."));
       Serial.print(F("You are now "));
       Serial.print(distance);
       Serial.println(F(" m away."));
     }
     else if (distance < 5000 && distance > 1000) {
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(F("You are now "));
       lcd.setCursor(0, 1);
       lcd.print(distance / 1000, DEC);
       lcd.print(F("."));
       lcd.print((distance % 1000) / 100, DEC);
       lcd.print(F(" km away."));
       Serial.print(F("You are now "));
       Serial.print(distance / 1000, DEC);
       Serial.print(F("."));
       Serial.print((distance % 1000) / 100, DEC);
       Serial.println(F(" km away."));
     }
     else {
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(F("Waiting for GPS"));
       Serial.println(F("Waiting for GPS"));
     }

     delay(2000);
   }
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(F("Tries left:"));
   lcd.setCursor(0, 1);
   tries--;
   lcd.print(tries);                //LCD shows tries
   Serial.print(F("Tries left:"));
   Serial.println(tries);

   //displayDistanceTo(3);
   smartDelay(1000);

   if (millis() > 5000 && gps.charsProcessed() < 10)
     Serial.println(F("No GPS data received: check wiring"));
}
