void startLCD()
{
  lcd.begin (20,4);                             //Settings for 16 x 2 LCD module. For the 16x2 module change to (20,4)
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  delay(50);
  //Serial.println(F("Starting LCD"));
  lcd.setCursor (0,0);
  lcd.print(F("GPS Treasure Box")); 
  lcd.setCursor (8,1);                                                     
  lcd.print(F("Mark 1"));
  delay(2000);
  lcd.clear();
}
