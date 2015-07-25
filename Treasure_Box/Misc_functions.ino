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

void emergencyOpen()
{
  long currentTime = millis();
  long maxTime = 120000;
  while ((millis() - currentTime) <= maxTime)
  {
    lcd.setCursor(0, 0);
    lcd.print(F("!!!!!!!DANGER!!!!!!!"));
    lcd.setCursor(0, 1);
    lcd.print(F("Voltage too high!!!"));
    lcd.setCursor(0, 2);
    lcd.print(F("Disconnect now!!!"));
    lcd.setCursor(0, 0);
    lcd.print(F("%gn 9AoD0_~'';.~@>,'][a|/zF5ZglcmzG$0qs,m  ajfva~`%gn 9AoD0_~'';.~@>,'][a|zF5Zgls,m  ajfva~` %gn9AoD0_~'';.~@>zF5ZglcmzG$0qs,m  ajfva~`%gn 9AoD0_~'';.~@>,'][a|zF5Zglcmn 9AoD0_~'';.~@>,'][a|zF5ZglcmzG$0qs,m  aa~` %0_~'][a|zF5ZglcmzG$0qsAoD0_~'';.~@>,'][a|zF5ZglcmzG$0qs,m  ajfva~`%gn 9AoD0_~'';.~@>,'][a|zF5ZglcmzG$0qs,m  a~`%gn 9AoD0_~'';][aglcmzG$0qs,m  ajfva~`%gn 9AoD0_~'';.~@>,'][a|zF5Zglcm  ajfva~`%gn D0_~'';.~@>,'][a|zF5Zglm  ajfva~` %gn 9AoD0_~'';.~@>cmzG$0qs,m  aja|zF5ZglcmzG$0qs,m  ajfva~`%gn 9AoD0_~'';.~@>,'][a|zF5ZglcmzG$0qs,m  jfa~`%gn 9AoD0_~'';.~@>5ZglcmzG$0qs,m  ajfva~`%gn 9AoD0_~'';.~@>,']n 9AoD0_~'';.~@>,'][a|zF5ZglcmzG$0qs,m #)&!^#(&____________________!!~&$#^"));
  }
  lock.write(disengage);
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
