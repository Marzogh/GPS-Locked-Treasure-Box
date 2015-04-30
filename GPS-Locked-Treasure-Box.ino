//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Libraries*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#include <Adafruit_GPS.h>                   // For gps
#include <SoftwareSerial.h>                 // For communicating with the gps
#include <math.h>                           // used by: GPS
#include <Wire.h>                           // For I2C devices
#include <LCD.h>                            // For LCD display
#include <LiquidCrystal_I2C.h>              // For LCD display
#include <Servo.h>                          // For locking servo

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Variables*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//Pins & Definitions
const int RXPin = 4, TXPin = 3;              // RX/TX for gps
#define WAYPOINT_DIST_TOLERANCE  200         // tolerance in meters to waypoint; once within this tolerance, will advance to the next waypoint
const int lidSensor = 5;                        // Pin connected to lid open sensor

//Variables
float currentLat,
      currentLong;
int distanceToTarget;                        // Current distance to target (current waypoint)
const float targetLat = 48.85826;
const float targetLong = 2.294516;
uint8_t tries = 100;
uint8_t engage = 0, disengage = 180;

//Initiate Objects
SoftwareSerial ss(RXPin, TXPin);            // Initiate Serial connection the gps
Adafruit_GPS gps(&ss);                      // Initiate gps object
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); //Initiate LiquidCrystal object for LCD. (0x27 is the I2C bus address for an unmodified I2C backpack)
Servo lock;

void setup() {
  Serial.begin(115200);
  pinMode(lidSensor, INPUT);
  startLCD();                                     //Starts the LCD
  startGPS();
  lock.attach(9);
}

void loop() {
  checkLidState();
  processGPS();
}
