void printQuestDistance()
{
  Serial.print(F("Current location: "));
  Serial.print(gps.location.lat(), 6);
  Serial.print(F("\t"));
  Serial.println(gps.location.lng(), 6);
  Serial.print(F("Target location: "));
  Serial.print(target.latitude, 6);
  Serial.print(F("\t"));
  Serial.println(target.longitude, 6);
  Serial.print(F("Distance to Quest location is: "));
  Serial.print(distance);
  Serial.println(F("m"));
}

void blinkLED(int times)
{
  for (int i = 0; i <= times ; ++i)
  {
    digitalWrite(13, HIGH);
    smartDelay(100);
    digitalWrite(13, LOW);
  }
}


/*#ifndef Lock
void blinkLED(uint8_t times, uint16_t wait)
{
  uint8_t i = times;
  uint8_t t = wait;
  while (i < 0, i--)
  {
    digitalWrite(LEDPin, HIGH);
    delay(t);
    digitalWrite(LEDPin, LOW);
    delay(t);
  }
}
#endif

void checkLidState()
{
  if (!lidIsOpen) {
#ifdef Lock
    lock.write(engage);
#endif
#ifndef Lock
    blinkLED(1, 500);
#endif
  }
  else {
    Serial.println(F("Close the lid!"));
    while (1);
  }
}

boolean lidIsOpen(void)
{
  if (lidSensor == LOW) {
    return false;
  }
  else {
    return true;
  }
}*/
