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
  float d;
  char charBuffer[25];
  bool km;
  lcd.clear();
  lcd.setCursor(0, 0);

  if (distance > 1100) {
    d = distance / 1000;
    km = 1;
  }
  else {
    d = distance;
    km = 0;
  }
  sprintf(charBuffer, "You are now %d ", d);
  lcd.print(F("charBuffer"));

  if (km = 1)
    lcd.print(F("km"));
  else
    lcd.print(F("m"));

  lcd.setCursor(0, 1);
  lcd.print(F(" from your target"));

  smartDelay(2000);
}

