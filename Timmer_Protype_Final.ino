// Button_Reading maximum 5 seconds.

// Two switches are used for long delay & short delay.

// Variable Resistor output pin A0.

#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

int VR ;           // Variable Rasistor reading.
#define Buzzer 5    // Buzzer pin.
unsigned int Time = 0 ;     // 1 - 1000.
#define Button_Long 2    // push to on switch.
boolean Button_Reading_Long ;
#define Button_Short 3    // push to on switch.
boolean Button_Reading_Short ;
#define LED 12
#define LED_Long 14
#define LED_Short 15
#define VR_read A5
boolean Timer_State = false;
unsigned long Millis = 0;
int i = 1;
// LED_Long = 8 ; LED_Short = 9 ;

void setup() {
  //Serial.begin(9600);
  pinMode(Button_Long, INPUT_PULLUP);
  pinMode(Button_Short, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(LED_Long, OUTPUT);
  pinMode(LED_Short, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  lcd.begin(16, 2);

  digitalWrite(LED, HIGH);
  lcd.home();
  lcd.print("Give me a time..");
  lcd.setCursor(0, 1);
  lcd.print("<<<<<<<<>>>>>>>>");

}

// Timer_State = 0; starting state
// Timer_State = 1; timer mode
// Timer_State = 2; exit from timer

void loop() {
  Read_Button () ;

  while (Button_Reading_Short == LOW || Button_Reading_Long == LOW) {        // Switch is on.
    Timer_State = true;
    VR = analogRead(VR_read);
    //Serial.print(VR);      // reading 0 - 1023.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(VR);

    if (Button_Reading_Short == LOW) {
      Time = map(VR, 30, 1002, 0, 18);
      Time = Time * 10;
      //Serial.print("\t");
      //Serial.print(Time);
      lcd.setCursor(6, 0);
      lcd.print(Time);
      Time = Time * 18;
      digitalWrite(LED_Short, HIGH);
      digitalWrite(LED_Long, LOW);
    }

    else {
      Time = map(VR, 30, 1002, 0, 18);
      Time = Time * 10;
      //Serial.print("\t");
      //Serial.print(Time);
      lcd.setCursor(6, 0);
      lcd.print(Time);
      Time = (Time * 90) + 3600 ;
      digitalWrite(LED_Short, LOW);
      digitalWrite(LED_Long, HIGH);
    }

    //Serial.print("\t");
    //Serial.println(Time);
    lcd.setCursor(10, 0);
    lcd.print(Time);
    lcd.print("s");
    Read_Button ();
    delay(100);
  }

  if ((!Time > 0) && Timer_State == true) {
    digitalWrite(LED_Short, LOW);
    digitalWrite(LED_Long, LOW);
    Timer_State = false;
    lcd.clear();
  }

  if (Time > 0) {

    tone (Buzzer, 1000, 100);
    //Serial.println("LED is ON");
    lcd.setCursor(0, 1);
    lcd.print("ON");
    Millis = millis();
    digitalWrite(LED, HIGH);

    for (i = 1; i <= Time; i++) {   // (1-18) or (10-180)

      for (int t = 1; t <= 100; t++) {
        Read_Button ();

        if (Button_Reading_Short == LOW || Button_Reading_Long == LOW) {          // Switch is on.
          break;
        }
        delay(10);

      }
      if (Button_Reading_Short == LOW || Button_Reading_Long == LOW) {          // Switch is on.
        break;
      }

    }
  }

  if (i == (Time + 1) && Time > 0) {
    AllLOW () ;
  }

  Time = 0;
}
