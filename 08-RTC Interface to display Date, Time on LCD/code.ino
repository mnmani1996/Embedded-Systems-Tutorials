#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS1307 rtc;  
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Try 0x3F if not working

void setup() {
  Serial.begin(9600);
  delay(3000);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is not running, setting time...");
    // ---------- SET TIME ONLY ONCE ----------
    // Format: rtc.adjust(DateTime(year, month, day, hour, minute, second));
    rtc.adjust(DateTime(2025, 9, 11, 14, 20, 0));  // Example: 01-Jan-2000 12:00:00
    // After uploading once, comment this line and re-upload
    // ----------------------------------------
  }

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DS1307 Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  // Print to Serial Monitor
  Serial.print(now.year()); Serial.print('/');
  Serial.print(now.month()); Serial.print('/');
  Serial.print(now.day());   Serial.print("  ");
  Serial.print(now.hour());  Serial.print(':');
  Serial.print(now.minute());Serial.print(':');
  Serial.print(now.second());Serial.println();

  // Print to LCD (no clear flicker)
  lcd.setCursor(0, 0);
  lcd.print(now.year());
  lcd.print('/');
  if (now.month() < 10) lcd.print('0');
  lcd.print(now.month());
  lcd.print('/');
  if (now.day() < 10) lcd.print('0');
  lcd.print(now.day());

  lcd.setCursor(0, 1);
  if (now.hour() < 10) lcd.print('0');
  lcd.print(now.hour());
  lcd.print(':');
  if (now.minute() < 10) lcd.print('0');
  lcd.print(now.minute());
  lcd.print(':');
  if (now.second() < 10) lcd.print('0');
  lcd.print(now.second());

  delay(1000);
}