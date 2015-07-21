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
  #endif
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

