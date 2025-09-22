// dht22 on lcd

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // If not working, try 0x3F

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("DHT22 Sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor Error");
    Serial.println("Failed to read from DHT22 sensor!");
    delay(2000);
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %  ");
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" *C");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1); // 1 decimal place
  lcd.print((char)223);      // ° symbol
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(humidity, 1);
  lcd.print(" %");

  delay(2000);
}