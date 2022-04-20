#include <WiFiNINA.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobot_DHT20.h>


#include "getCityWeather.h"
#include "connectWiFi.h"
#include "getDistance.h"
#include "utils.h"

// Vars
LiquidCrystal_I2C lcd(0x27, 20, 4);
DFRobot_DHT20 dht20;
#define PHOTO_CELL_PIN A0
const int tempLine = 0, distanceLine = 1, lightLine = 2, weatherLine = 3;

void setup(){
  Serial.begin(9600);

  // lcd
  lcd.init();
  lcd.backlight();

  // wifi
  wifiConnect();

  // get distance
  ultraSonicSetup();

  // DHT Setup
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
  }
}

void loop(){
  // Print local temp and humidity
  lcdClearLine(tempLine, lcd);
  lcd.print("temp: " + String(tempConvert(dht20.getTemperature())) + "F, " + String(dht20.getHumidity()*100) + "%RH"); 
  /////////////////


  // Print distance second line
  lcdClearLine(distanceLine, lcd);
  lcd.print("Distance: " + String(getDistanceInInches()) + " in");
  /////////////////


  // Print Light intensity second line
  lcdClearLine(lightLine, lcd);
  lcd.print("Light: " + String(analogRead(PHOTO_CELL_PIN)));
  /////////////////


  // Print weather API first line
  double weather = getCurrWeather(cities[citiesIndex].lat, cities[citiesIndex].lon);
  lcdClearLine(weatherLine, lcd);   
  lcd.print(cities[citiesIndex].name + ": " + int(weather) + " F");
  
  citiesIndex++;
  if(citiesIndex + 1 == sizeof(cities) / sizeof(cities[0])) citiesIndex = 0;
  /////////////////

    delay(1000);
}
