void Read_Button () {
  Button_Reading_Short = digitalRead(Button_Short);
  Button_Reading_Long = digitalRead(Button_Long);
}

void AllLOW () {
  digitalWrite(LED, LOW);
  digitalWrite(LED_Short, LOW);
  digitalWrite(LED_Long, LOW);
  //Serial.println("LED is OFF");

  Millis = millis() - Millis;
  Millis = Millis / 1000;
  lcd.setCursor(3, 1);
  lcd.print("OF");
  lcd.setCursor(6, 1);
  lcd.print(Millis);
  Timer_State = false;
  tone (Buzzer, 2000, 100);
}
