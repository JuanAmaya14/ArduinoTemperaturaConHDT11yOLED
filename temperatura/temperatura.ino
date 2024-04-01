#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

Adafruit_SSD1306 pantalla(128, 64);
#define PIN_DHT 2
#define TIPO_DHT DHT11

DHT dht(PIN_DHT, TIPO_DHT);

float maxTemperatura = -1000;
float minTemperatura = 1000;
int desplazamientoX = 0;
bool moverDerecha = true;

void setup() {
  pantalla.cp437(true);
  dht.begin();
  pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pantalla.clearDisplay();
  pantalla.setTextColor(SSD1306_WHITE);
}

void loop() {
  float temperatura = dht.readTemperature();
  if (!isnan(temperatura)) {
    maxTemperatura = max(temperatura, maxTemperatura);
    minTemperatura = min(temperatura, minTemperatura);
  }

  pantalla.clearDisplay();

  pantalla.setTextSize(1);
  pantalla.setCursor(desplazamientoX, 7);
  pantalla.print("Temperatura: ");
  pantalla.setTextSize(2);
  pantalla.setCursor(desplazamientoX, 16);
  pantalla.print(temperatura);
  pantalla.print(" ");
  pantalla.setTextSize(1);
  pantalla.write(167);
  pantalla.setTextSize(2);
  pantalla.print("C");

  pantalla.setTextSize(1);
  pantalla.setCursor(desplazamientoX, 40);
  pantalla.print("Max Temp: ");
  pantalla.print(maxTemperatura);
  pantalla.print(" ");
  pantalla.write(167);
  pantalla.print("C");
  pantalla.setCursor(desplazamientoX, 50);
  pantalla.print("Min Temp: ");
  pantalla.print(minTemperatura);
  pantalla.print(" ");
  pantalla.write(167);
  pantalla.print("C");

  pantalla.display();

  if (moverDerecha) {
    desplazamientoX++;
    if (desplazamientoX >= 22) {
      moverDerecha = false;
    }
  } else {
    desplazamientoX--;
    if (desplazamientoX <= -2) {
      moverDerecha = true;
    }
  }

  delay(50);
}
