#include <ArduinoHttpClient.h>
#include <Arduino_JSON.h>
#include "secrets.h" 


class City {
public:
  String name;
  double lat;
  double lon;

  City(String name, double lat, double lon){
    this->name = name;
    this->lat = lat;
    this->lon = lon;
  }
};

int citiesIndex = 0;
const City cities[] = {
    City("Durham", 35.902771, -78.903935),
    City("Doha", 25.2854, 51.5310),
    City("North Pole", 90.0000, -135.0000),
};

// API KEY
const String WEATHER_APIKEY = SECRET_APIKEY;

double getCurrWeather(double lat, double lon) {
    // HTTP Client
    WiFiClient wifi;
    HttpClient client = HttpClient(wifi, "api.openweathermap.org", 80);
  
    String latParam = "lat=" + String(lat);
    String lonParam = "lon=" + String(lon);
    String apiKey = "appid=" + WEATHER_APIKEY;
    
  
    client.get("/data/2.5/weather?" + latParam + "&" + lonParam + "&" + apiKey + "&units=imperial");
  
    if(client.responseStatusCode() == 200){
      JSONVar parsedRes = JSON.parse(client.responseBody());
      if (JSON.typeof(parsedRes) == "undefined") {
        Serial.println("Parsing input failed!");
        return -1;
      }
    
      client.stop();
    
      return (double) parsedRes["main"]["temp"]; 
    }else {
      Serial.println("Status code != 200");
      Serial.println(client.responseBody());
      Serial.println();
      return -1;
    }
  }
