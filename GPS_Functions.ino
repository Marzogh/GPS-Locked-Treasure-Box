void startGPS()
{
  gps.begin(9600);
  gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);     // turns on RMC and GGA (fix data)
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);       // 1 Hz update rate
  gps.sendCommand(PGCMD_NOANTENNA);                // turn off antenna status info
  delay (1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Waiting for gps"));
  unsigned long startTime = millis();
  while (!gps.fix)                      // wait for fix, updating display with each new NMEA sentence received
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(F("Wait Time: "));
    lcd.print((int) (millis() - startTime) / 1000);     // show how long we have waited
    if (gps.newNMEAreceived())
      gps.parse(gps.lastNMEA());
  }
}

void processGPS(void)
{
  currentLat = convertDegMinToDecDeg(gps.latitude);
  currentLong = convertDegMinToDecDeg(gps.longitude);

  if (gps.lat == 'S')            // make them signed
    currentLat = -currentLat;
  if (gps.lon = 'W')
    currentLong = -currentLong;

  distanceToWaypoint();

}


/* Returns distance in meters between two positions, both specified as signed decimal-degrees latitude and longitude.
Uses great-circle distance computation for hypothetical sphere of radius 6372795 meters.
As Earth is no exact sphere, rounding errors may be up to 0.5%.(Copied from TinyGPS library) */
int distanceToWaypoint()
{

  float delta = radians(currentLong - targetLong);
  float sdlong = sin(delta);
  float cdlong = cos(delta);
  float lat1 = radians(currentLat);
  float lat2 = radians(targetLat);
  float slat1 = sin(lat1);
  float clat1 = cos(lat1);
  float slat2 = sin(lat2);
  float clat2 = cos(lat2);
  delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
  delta = sq(delta);
  delta += sq(clat2 * sdlong);
  delta = sqrt(delta);
  float denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
  delta = atan2(delta, denom);
  distanceToTarget =  delta * 6372795;

  // check to see if we have reached the current waypoint
  if (!distanceToTarget <= WAYPOINT_DIST_TOLERANCE) {
    displayDistanceTo(3);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("You have arrived!!!"));
    lock.write(disengage);
  }

  return distanceToTarget;
}
