
void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

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
  {0,31,0,31,30,31,30,31,
  31,30,31,30,31};
  if (Month == 2) {
    if (Year % 4 == 0 || Year % 400 == 0)
      noOfDays[2] = 29;
    else if (Year % 4 != 0 || Year % 100 == 0)
      noOfDays[2] = 28;
  }
  return noOfDays[Month];
}

/* void timeSinceMarriage(int years, int months, int days)
{
  int initYear = 2015, initMonth = 8, initDate = 8;

  int cYear, cMonth, cDate;
  cYear = gps.date.year();
  cMonth = gps.date.month();
  cDate = gps.date.day();

  //Calculate years passed
  years = cYear - initYear;

  //Calculate the months passed and correct the number of years if required
  if (cMonth < initMonth) {
    years =- 1;
    months = 12 - (abs(cMonth - initMonth));
  }
  else
  months = (cMonth - initMonth);

  //Calculate the days passed and correct the number of months 
  if (cDate < initDate) {
    months =- 1;
    days = (calcNoOfDays(months, years)) - (abs(cDate - initDate));
  }
  else
  days = (cDate - initDate);
} */

struct dateTime timeSince(int c_Year, byte c_Month, byte c_Date, int p_Year, byte p_Month, byte p_Date)
{
  struct dateTime timeElapsed;
  c_Year = gps.date.year();
  c_Month = gps.date.month();
  c_Date = gps.date.day();

  //Calculate years passed
  timeElapsed.Year = c_Year - p_Year;

  //Calculate the months passed and correct the number of years if required
  if (c_Month < p_Month) {
    timeElapsed.Year =- 1;
    timeElapsed.Month = 12 - (abs(c_Month - p_Month));
  }
  else
  timeElapsed.Month = (c_Month - p_Month);

  //Calculate the days passed and correct the number of months 
  if (c_Date < p_Date) {
    timeElapsed.Month =- 1;
    timeElapsed.Date = (calcNoOfDays(timeElapsed.Month, timeElapsed.Year)) - (abs(c_Date - p_Date));
  }
  else
  timeElapsed.Date = (c_Date - p_Date);
}
