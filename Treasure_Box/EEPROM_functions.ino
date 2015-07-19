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

bool coordinateCheck()
{
  getAddresses();
  double tempLatitude  = -27.486890;
  double tempLongitude = 153.013860;

  EEPROM.readBlock(address1.latitude, target);
  if (tempLatitude != target.latitude || tempLongitude != target.longitude)
    return false;
  return true;
}

