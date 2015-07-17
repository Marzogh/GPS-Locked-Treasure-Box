#include <EEPROMex.h>
#include <EEPROMVar.h>

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
addresses address6;

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
  address6.latitude  = EEPROM.getAddress(sizeof(double));
  address6.longitude = EEPROM.getAddress(sizeof(double));
}

void writeCoordinates()
{
  quest1.latitude  = -27.486890;
  quest1.longitude = 153.013860;
  quest2.latitude  = -27.486890;
  quest2.longitude = 153.013860;
  quest3.latitude  = -27.486890;
  quest3.longitude = 153.013860;
  quest4.latitude  = -27.486890;
  quest4.longitude = 153.013860;
  quest5.latitude  = -27.486890;
  quest5.longitude = 153.013860;
  quest6.latitude  = -27.486890;
  quest6.longitude = 153.013860;
  
  EEPROM.update(address1.latitude, quest1.latitude);
  EEPROM.update(address1.longitude, quest1.longitude);
  EEPROM.update(address2.latitude, quest2.latitude);
  EEPROM.update(address2.longitude, quest2.longitude);
  EEPROM.update(address3.latitude, quest3.latitude);
  EEPROM.update(address3.longitude, quest3.longitude);
  EEPROM.update(address3.latitude, quest4.latitude);
  EEPROM.update(address3.longitude, quest4.longitude);
  EEPROM.update(address3.latitude, quest5.latitude);
  EEPROM.update(address3.longitude, quest5.longitude);
  EEPROM.update(address3.latitude, quest6.latitude);
  EEPROM.update(address3.longitude, quest6.longitude);
}
