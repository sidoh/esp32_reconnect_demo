#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define WIFI_SSID "wifissid"
#define WIFI_PASSWD "wifipasswd"

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

void setup() {
  Serial.begin(115200);

  WiFi.setAutoReconnect(false);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  WiFi.waitForConnectResult();

  timeClient.begin();

  Serial.println("Setup completed");
}

void loop() {
  timeClient.forceUpdate();

  printf("[%d] ssid=%s\n", timeClient.getEpochTime(), WiFi.SSID().c_str());

  if (! WiFi.isConnected()) {
    Serial.println("Attempting to reconnect...");
    WiFi.begin();
    Serial.printf("Connection result: %d\n", WiFi.waitForConnectResult());
  }
}
