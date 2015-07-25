long getDistance()
{
  long dist =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      target.latitude,
      target.longitude);
  printInt(distance, gps.location.isValid(), 9);
  Serial.println();
  return dist;
}

int calcNoOfDays(int Month, int Year)
{
  int noOfDays[] =
  { 0, 31, 0, 31, 30, 31, 30, 31,
    31, 30, 31, 30, 31
  };
  if (Month == 2) {
    if (Year % 4 == 0 || Year % 400 == 0)
      noOfDays[2] = 29;
    else if (Year % 4 != 0 || Year % 100 == 0)
      noOfDays[2] = 28;
  }
  return noOfDays[Month];
}

void updateDate()
{
  current.Year = gps.date.year();
  current.Month = gps.date.month();
  current.Date = gps.date.day();
  
  past.Year = EEPROM.readInt(yearAddress);
  past.Month = EEPROM.readByte(monthAddress);
  past.Date = EEPROM.readByte(dateAddress);
}

void timeSince()
{

#ifdef SERIALECHO
  char Date[50];
  sprintf(Date, "The current date is: %d/%d/%d", current.Date, current.Month, current.Year);
  Serial.println(Date);
  sprintf(Date, "The previous date is: %d/%d/%d", past.Date, past.Month, past.Year);
  Serial.println(Date);
#endif
  //Calculate years passed
  timeElapsed.Year = current.Year - past.Year;

  //Calculate the months passed and correct the number of years if required
  if (current.Month < past.Month) {
#ifdef SERIALECHO
    Serial.println(F("Current Month < Past Month"));
#endif
    timeElapsed.Year -= 1;
    timeElapsed.Month = 12 - (abs(current.Month - past.Month));
  }
  else
    timeElapsed.Month = (current.Month - past.Month);

  //Calculate the days passed and correct the number of months
  if (current.Date < past.Date) {
#ifdef SERIALECHO
    Serial.println(F("Current Date < Past Date"));
#endif
    timeElapsed.Month -= 1;
    timeElapsed.Date = (calcNoOfDays(months, years)) - (abs(current.Date - past.Date));
  }
  else
    timeElapsed.Date = (current.Date - past.Date);
#ifdef SERIALECHO
  sprintf(Date, "The time elapsed is: %d days %d months %d years", timeElapsed.Date, timeElapsed.Month, timeElapsed.Year);
  Serial.println(Date);
#endif
}

/*struct dateTime timeSince(int current.Year, byte current.Month, byte current.Date, int p_Year, byte p_Month, byte p_Date)
{
  dateTime timeElapsed;

  char Date[50];
  sprintf(Date, "The current date is: %02x/%02x/%04x", current.Date, current.Month, current.Year);
  Serial.println(Date);
  sprintf(Date, "The previous date is: %02x/%02x/%04x", p_Date, p_Month, p_Year);
  Serial.println(Date);

  //Calculate years passed
  timeElapsed.Year = current.Year - p_Year;

  //Calculate the months passed and correct the number of years if required
  if (current.Month < p_Month) {
    timeElapsed.Year = - 1;
    timeElapsed.Month = 12 - (abs(current.Month - p_Month));
  }
  else
    timeElapsed.Month = (current.Month - p_Month);

  //Calculate the days passed and correct the number of months
  if (current.Date < p_Date) {
    timeElapsed.Month = - 1;
    timeElapsed.Date = (calcNoOfDays(timeElapsed.Month, timeElapsed.Year)) - (abs(current.Date - p_Date));
  }
  else
    timeElapsed.Date = (current.Date - p_Date);

  sprintf(Date, "The time elapsed is: %02x days %02x months %04x years", timeElapsed.Date, timeElapsed.Month, timeElapsed.Year);
  Serial.println(Date);
}*/
