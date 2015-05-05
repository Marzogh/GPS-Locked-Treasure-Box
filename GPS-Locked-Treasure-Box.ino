//#define LOCK
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*Libraries*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#include <Adafruit_GPS.h>                   // For gps
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
//const int RXPin = 4, TXPin = 3;              // RX/TX for gps
#define WAYPOINT_DIST_TOLERANCE  20         // tolerance in meters to waypoint; once within this tolerance, will advance to the next waypoint
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
float currentLat,
      currentLong;
int distanceToTarget;                        // Current distance to target (current waypoint)
const float targetLat = -27.486844;
const float targetLong = 153.013882;
//int distanceToDestination;
//unsigned long timer;
uint8_t tries = 100;
#ifdef Lock
uint8_t engage = 0, disengage = 180;
#endif
//boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

// If you're using a GPS module:
// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// If using software serial (sketch example default):
//   Connect the GPS TX (transmit) pin to Digital 3
//   Connect the GPS RX (receive) pin to Digital 2
// If using hardware serial (e.g. Arduino Mega):
//   Connect the GPS TX (transmit) pin to Arduino RX1, RX2 or RX3
//   Connect the GPS RX (receive) pin to matching TX1, TX2 or TX3

// If you're using the Adafruit GPS shield, change 
// SoftwareSerial mySerial(3, 2); -> SoftwareSerial mySerial(8, 7);
// and make sure the switch is set to SoftSerial

// If using software serial, keep this line enabled
// (you can change the pin numbers to match your wiring):
SoftwareSerial mySerial(3, 2);

// If using hardware serial (e.g. Arduino Mega), comment out the
// above SoftwareSerial line, and enable this line instead
// (you can change the Serial number to match your wiring):


Adafruit_GPS GPS(&mySerial);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); //Initiate LiquidCrystal object for LCD. (0x27 is the I2C bus address for an unmodified I2C backpack)
#ifdef Lock
Servo lock;
#endif


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  false
#define SERIALECHO true

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

void setup()  
{
  Serial.begin(115200);
  startGPS();
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  processGPS();
}
