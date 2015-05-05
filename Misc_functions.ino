#ifndef Lock
void blinkLED(uint8_t times, uint16_t wait)
{
  uint8_t i = times;
  uint8_t t = wait;
  while (i<0, i--)
  {
  digitalWrite(LEDPin, HIGH);
  delay(t);
  digitalWrite(LEDPin, LOW);
  delay(t);
  }
}
#endif

boolean lidIsOpen(void)
{
  if (lidSensor == LOW) {
    return false;
  }
  else {
    return true;
  }
}

void checkLidState()
{
  if (!lidIsOpen) {
    #ifdef Lock
    lock.write(engage);
    #endif
    #ifndef Lock
    blinkLED(1,500);
    #endif
  }
  else {
    Serial.println(F("Close the lid!"));
    while (1);
  }
}
