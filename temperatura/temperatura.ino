#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64);
#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float maxTemperatura = -1000;
float minTemperatura = 1000;

void setup() {
  display.cp437(true);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  float temperatura = dht.readTemperature();
  if (!isnan(temperatura)) {
    maxTemperatura = max(temperatura, maxTemperatura);
    minTemperatura = min(temperatura, minTemperatura);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 7);
  display.print("Temperatura: ");
  display.setTextSize(2);
  display.setCursor(0, 16);
  display.print(temperatura);
  display.print(" ");
  display.setTextSize(1);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("Max Temp: ");
  display.print(maxTemperatura);
  display.print(" ");
  display.write(167);
  display.print("C");
  display.setCursor(0, 50);
  display.print("Min Temp: ");
  display.print(minTemperatura);
  display.print(" ");
  display.write(167);
  display.print("C");

  display.display();
}
