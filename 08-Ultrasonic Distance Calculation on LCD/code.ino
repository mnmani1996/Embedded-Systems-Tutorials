#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 9
#define ECHO_PIN 8

long duration;
float distance;

// Set the LCD address to 0x27 (common) and size 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();  // Turn on backlight
}

void loop() {
  // Clear trig pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by sending 10µs pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);  // Typically 10µs is enough
  digitalWrite(TRIG_PIN, LOW);

  // Read echo pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance (speed of sound = 343 m/s)
  distance = (duration * 0.0343) / 2;

  // Print result on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Print result on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  delay(2000);
}
