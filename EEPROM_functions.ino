void getAddresses()
{
  address1.latitude  = EEPROM.getAddress(sizeof(double));
  address1.longitude = EEPROM.getAddress(sizeof(double));
  address2.latitude  = EEPROM.getAddress(sizeof(double));
  address2.longitude = EEPROM.getAddress(sizeof(double));
  address3.latitude  = EEPROM.getAddress(sizeof(double));
  address3.longitude = EEPROM.getAddress(sizeof(double));
  questAddress       = EEPROM.getAddress(sizeof(byte));
}
bool coordinateCheck()
{
  getAddresses();
  waypoint1.latitude  = -27.486890;
  waypoint1.longitude = 153.013860;

  EEPROM.readBlock(address1.latitude, target);
  if (address1.latitude != target.latitude || address1.longitude != target.longitude) {
    if (!writeCoordinates())
    return false;
  }
  return true;
}

bool writeCoordinates()
{
  waypoint1.latitude  = -27.486890;
  waypoint1.longitude = 153.013860;
  waypoint2.latitude  = -27.486890;
  waypoint2.longitude = 153.013860;
  waypoint3.latitude  = -27.486890;
  waypoint3.longitude = 153.013860;

  EEPROM.update(address1.latitude, waypoint1.latitude);
  EEPROM.update(address1.longitude, waypoint1.longitude);
  EEPROM.update(address2.latitude, waypoint2.latitude);
  EEPROM.update(address2.longitude, waypoint2.longitude);
  EEPROM.update(address3.latitude, waypoint3.latitude);
  EEPROM.update(address3.longitude, waypoint3.longitude);

  return true;
}

