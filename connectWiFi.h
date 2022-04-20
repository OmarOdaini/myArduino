#include "secrets.h" 

// Global Variables
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

void wifiConnect() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  Serial.println(ssid);

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    delay(3000);
  }

  Serial.println("CONNECTED!");
}
