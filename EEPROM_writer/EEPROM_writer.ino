#include <EEPROMex.h>
#include <EEPROMVar.h>

struct locations {
  double latitude;
  double longitude;
};
locations quest1;
locations quest2;
locations quest3;
locations quest4;
locations quest5;

struct addresses {
  int latitude;
  int longitude;
};

addresses Address1;
addresses Address2;
addresses Address3;
addresses Address4;
addresses Address5;

byte questAddress, yearAddress, monthAddress, dateAddress,
     currentAttempts, quest1Attempts, quest2Attempts, quest3Attempts, quest4Attempts, quest5Attempts;
byte resetAttempts = 0;

void setup() {
  Serial.begin(115200);
  getAddresses();
  updateValues();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void getAddresses()
{
  questAddress  = EEPROM.getAddress(sizeof(byte));
  yearAddress  = EEPROM.getAddress(sizeof(int));
  monthAddress  = EEPROM.getAddress(sizeof(byte));
  dateAddress  = EEPROM.getAddress(sizeof(byte));
  Address1.latitude = EEPROM.getAddress(sizeof(double));
  Address1.longitude = EEPROM.getAddress(sizeof(double));
  Address2.latitude = EEPROM.getAddress(sizeof(double));
  Address2.longitude = EEPROM.getAddress(sizeof(double));
  Address3.latitude = EEPROM.getAddress(sizeof(double));
  Address3.longitude = EEPROM.getAddress(sizeof(double));
  Address4.latitude = EEPROM.getAddress(sizeof(double));
  Address4.longitude = EEPROM.getAddress(sizeof(double));
  Address5.latitude = EEPROM.getAddress(sizeof(double));
  Address5.longitude = EEPROM.getAddress(sizeof(double));
  currentAttempts = EEPROM.getAddress(sizeof(byte));
  quest1Attempts = EEPROM.getAddress(sizeof(byte));
  quest2Attempts = EEPROM.getAddress(sizeof(byte));
  quest3Attempts = EEPROM.getAddress(sizeof(byte));
  quest4Attempts = EEPROM.getAddress(sizeof(byte));
  quest5Attempts = EEPROM.getAddress(sizeof(byte));

  Serial.println("Addresses");
  Serial.println(questAddress);
  Serial.println(yearAddress);
  Serial.println(monthAddress);
  Serial.println(dateAddress);
  Serial.println(Address1.latitude);
  Serial.println(Address1.longitude);
  Serial.println(Address2.latitude);
  Serial.println(Address2.longitude);
  Serial.println(Address3.latitude);
  Serial.println(Address3.longitude);
  Serial.println(Address4.latitude);
  Serial.println(Address4.longitude);
  Serial.println(Address5.latitude);
  Serial.println(Address5.longitude);
  Serial.println(currentAttempts);
  Serial.println(quest1Attempts);
  Serial.println(quest2Attempts);
  Serial.println(quest3Attempts);
  Serial.println(quest4Attempts);
  Serial.println(quest5Attempts);
}

void updateValues()
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

  EEPROM.updateByte(questAddress, 1);
  EEPROM.updateInt(yearAddress, 2015);
  EEPROM.updateByte(monthAddress, 8);
  EEPROM.updateByte(dateAddress, 8);
  EEPROM.updateDouble(Address1.latitude, quest1.latitude);
  EEPROM.updateDouble(Address1.longitude, quest1.longitude);
  EEPROM.updateDouble(Address2.latitude, quest2.latitude);
  EEPROM.updateDouble(Address2.longitude, quest2.longitude);
  EEPROM.updateDouble(Address3.latitude, quest3.latitude);
  EEPROM.updateDouble(Address3.longitude, quest3.longitude);
  EEPROM.updateDouble(Address4.latitude, quest4.latitude);
  EEPROM.updateDouble(Address4.longitude, quest4.longitude);
  EEPROM.updateDouble(Address5.latitude, quest5.latitude);
  EEPROM.updateDouble(Address5.longitude, quest5.longitude);
  EEPROM.updateByte(currentAttempts, resetAttempts);
  EEPROM.updateByte(quest1Attempts, resetAttempts);
  EEPROM.updateByte(quest2Attempts, resetAttempts);
  EEPROM.updateByte(quest3Attempts, resetAttempts);
  EEPROM.updateByte(quest4Attempts, resetAttempts);
  EEPROM.updateByte(quest5Attempts, resetAttempts);

  Serial.println("Values");
  Serial.println(EEPROM.readByte(questAddress));
  Serial.println(EEPROM.readInt(yearAddress));
  Serial.println(EEPROM.readByte(monthAddress));
  Serial.println(EEPROM.readByte(dateAddress));
  Serial.println(EEPROM.readDouble(Address1.latitude), 6);
  Serial.println(EEPROM.readDouble(Address1.longitude), 6);
  Serial.println(EEPROM.readDouble(Address2.latitude), 6);
  Serial.println(EEPROM.readDouble(Address2.longitude), 6);
  Serial.println(EEPROM.readDouble(Address3.latitude), 6);
  Serial.println(EEPROM.readDouble(Address3.longitude), 6);
  Serial.println(EEPROM.readDouble(Address4.latitude), 6);
  Serial.println(EEPROM.readDouble(Address4.longitude), 6);
  Serial.println(EEPROM.readDouble(Address5.latitude), 6);
  Serial.println(EEPROM.readDouble(Address5.longitude), 6);
  Serial.println(EEPROM.readByte(currentAttempts));
  Serial.println(EEPROM.readByte(quest1Attempts));
  Serial.println(EEPROM.readByte(quest2Attempts));
  Serial.println(EEPROM.readByte(quest3Attempts));
  Serial.println(EEPROM.readByte(quest4Attempts));
  Serial.println(EEPROM.readByte(quest5Attempts));
}
