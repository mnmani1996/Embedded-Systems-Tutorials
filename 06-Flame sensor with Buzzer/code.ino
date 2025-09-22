// flame sensor code

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define IR_PIN 7
#define BUZZER_PIN 6

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Try 0x3F if 0x27 doesn't work

int lastState = -1;  // Track last IR state to reduce flicker

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("IR Sensor Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorState = digitalRead(IR_PIN);

  // Update only if state changes
  if(sensorState != lastState){
    lcd.setCursor(0,0);
    lcd.print("IR Status:       "); // Clear previous text

    lcd.setCursor(0,1);
    if (sensorState == LOW) {  // Flame detected
      Serial.println("Flame Detected!");
      lcd.print("Flame Detected  "); // 16 chars
      // Beep buzzer
      digitalWrite(BUZZER_PIN, HIGH);
      delay(200);                // Buzzer ON 200ms
      digitalWrite(BUZZER_PIN, LOW);
    } else {                   // No flame
      Serial.println("No flame detected.");
      lcd.print("No flame detected"); // 16 chars
      digitalWrite(BUZZER_PIN, LOW);
    }
    lastState = sensorState;
  }

  delay(100); // Small delay for stability
}