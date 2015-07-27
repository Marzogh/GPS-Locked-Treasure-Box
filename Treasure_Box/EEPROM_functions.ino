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
  distanceClueBoolean = EEPROM.getAddress(sizeof(byte));

  quest1.latitude  = EEPROM.readDouble(Address1.latitude);
  quest1.longitude = EEPROM.readDouble(Address1.longitude);
  quest2.latitude  = EEPROM.readDouble(Address2.latitude);
  quest2.longitude = EEPROM.readDouble(Address2.longitude);
  quest3.latitude  = EEPROM.readDouble(Address3.latitude);
  quest3.longitude = EEPROM.readDouble(Address3.longitude);
  quest4.latitude  = EEPROM.readDouble(Address4.latitude);
  quest4.longitude = EEPROM.readDouble(Address4.longitude);
  quest5.latitude  = EEPROM.readDouble(Address5.latitude);
  quest5.longitude = EEPROM.readDouble(Address5.longitude);

#ifdef SERIALECHO
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
  Serial.println(distanceClueBoolean);
#endif
}

void resetAllEEPROM()
{
  EEPROM.updateByte(questAddress, 100);
  EEPROM.updateByte(currentAttempts, 0);
  EEPROM.updateBit(distanceClueBoolean, 0, 0);
  blinkLED(5);
}

/*bool coordinateCheck()
{
  getAddresses();
  double tempLatitude  = -27.486890;
  double tempLongitude = 153.013860;

  EEPROM.readBlock(address1.latitude, target);
  if (tempLatitude != target.latitude || tempLongitude != target.longitude)
    return false;
  return true;
}*/

