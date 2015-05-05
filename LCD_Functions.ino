void initiateLCD()                                //Initiates LCD
{
  //Serial.println(F("GPS Treasure Box"));
  //lcd.home();
  lcd.setCursor (0,0);
  lcd.print(F("GPS Treasure Box")); 
  lcd.setCursor (8,1);                                                     
  lcd.print(F("Mark 1"));
  delay(2000);
  lcd.clear();
}

void startLCD()
{
  lcd.begin (16,2);                             //Settings for 16 x 2 LCD module. For the 16x2 module change to (20,4)
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  delay(50);
  //Serial.println(F("Starting LCD"));
  initiateLCD();
}

void displayDistanceTo(int times)
{
  int i=times;
  while (i>0, i--)
  {
  if (distanceToTarget <= 1000) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("You are now "));
      lcd.setCursor(0,1);
      lcd.print(distanceToTarget);
      lcd.print(F(" m away."));
      Serial.print(F("You are now "));
      Serial.print(distanceToTarget);
      Serial.println(F(" m away."));
    }
    if (distanceToTarget > 1000) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("You are now "));
      lcd.setCursor(0,1);
      lcd.print(distanceToTarget / 1000, DEC);
      lcd.print(F("."));
      lcd.print((distanceToTarget % 1000) / 100, DEC);
      lcd.print(F(" km away."));
      Serial.print(F("You are now "));
      Serial.print(distanceToTarget / 1000, DEC);
      Serial.print(F("."));
      Serial.print((distanceToTarget % 1000) / 100, DEC);
      Serial.println(F(" km away."));
    }
  delay(3000);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Tries left:"));
  lcd.setCursor(0,1);
  tries--;
  lcd.print(tries);                //LCD shows tries
  Serial.print(F("Tries left:"));
  Serial.println(tries);
}
