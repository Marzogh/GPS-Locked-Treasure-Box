#include <EEPROMex.h>
#include <EEPROMVar.h>

byte questAddress;
struct coordinates {
  double latitude;
  double longitude;
};

coordinates quest1;
coordinates quest2;
coordinates quest3;
coordinates quest4;
coordinates quest5;
coordinates quest6;
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

void setup() {
  getAddresses();
  writeCoordinates();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void getAddresses()
{
  address1.latitude  = EEPROM.getAddress(sizeof(double));
  address1.longitude = EEPROM.getAddress(sizeof(double));
  address2.latitude  = EEPROM.getAddress(sizeof(double));
  address2.longitude = EEPROM.getAddress(sizeof(double));
  address3.latitude  = EEPROM.getAddress(sizeof(double));
  address3.longitude = EEPROM.getAddress(sizeof(double));
  address4.latitude  = EEPROM.getAddress(sizeof(double));
  address4.longitude = EEPROM.getAddress(sizeof(double));
  address5.latitude  = EEPROM.getAddress(sizeof(double));
  address5.longitude = EEPROM.getAddress(sizeof(double));
  questAddress       = EEPROM.getAddress(sizeof(byte));
}

void writeCoordinates()
{
  quest1.latitude  = -27.457927;
  quest1.longitude = 153.034287;
  quest2.latitude  = -27.383030;
  quest2.longitude = 153.032767;
  quest3.latitude  = -26.668923;
  quest3.longitude = 153.107244;
  quest4.latitude  = -26.689649;
  quest4.longitude = 152.892891;
  quest5.latitude  = -27.391034;
  quest5.longitude = 153.008227;
  
  EEPROM.update(address1.latitude, quest1.latitude);
  EEPROM.update(address1.longitude, quest1.longitude);
  EEPROM.update(address2.latitude, quest2.latitude);
  EEPROM.update(address2.longitude, quest2.longitude);
  EEPROM.update(address3.latitude, quest3.latitude);
  EEPROM.update(address3.longitude, quest3.longitude);
  EEPROM.update(address4.latitude, quest4.latitude);
  EEPROM.update(address4.longitude, quest4.longitude);
  EEPROM.update(address5.latitude, quest5.latitude);
  EEPROM.update(address5.longitude, quest5.longitude);
  EEPROM.update(questAddress, 1);
}
