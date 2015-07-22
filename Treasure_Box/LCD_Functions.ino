void startLCD()
{
  lcd.begin (20, 4);                            //Settings for 20 x 4 LCD module. For the 16x2 module change to (16,2)
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  delay(50);
  //Serial.println(F("Starting LCD"));
  lcd.setCursor (2, 0);
  lcd.print(F("Congratulations!"));
  lcd.setCursor (3, 1);
  lcd.print(F("Angela & Deon"));
  lcd.setCursor (7, 3);
  lcd.print(F("- Kiri & Praj"));
  /*lcd.setCursor (8,3);
  lcd.print(F("Jenny & John"));*/
  delay(5000);
  lcd.clear();
}

void lcdPrintQuestDistance()
{
  char charBuffer[25], str_dist[6];
  bool km;
  lcd.clear();
  lcd.setCursor(0, 1);

  if (distance > 1100) {
    dtostrf(distance/1000, 4, 2, str_dist);
#ifdef SERIALECHO
    Serial.print(F("Distance to target: "));
    Serial.print(str_dist);
    Serial.println(F(" km"));
#endif
    km = 1;
  }
  else {
    km = 0;
    dtostrf(distance, 4, 2, str_dist);
#ifdef SERIALECHO
    Serial.print(F("Distance to target: "));
    Serial.print(str_dist);
    Serial.println(F(" km"));
#endif
  }
  sprintf(charBuffer, "You are now %s ", str_dist);
  lcd.print(charBuffer);

  if (km = 1)
    lcd.print(F("km"));
  else
    lcd.print(F("m"));

  lcd.setCursor(0, 2);
  lcd.print(F(" from your target"));

  smartDelay(2000);
}

