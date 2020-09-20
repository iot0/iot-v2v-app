#include <ESP8266WiFi.h>
#include "Common.h";

class WifiSetup
{

public:
  static void initWiFi()
  {
    WiFi.mode(WIFI_STA);

    //Connecting to WIFI
    int retries = 0;

    Serial.print("Connecting to WiFi ..........");
    Serial.println(SSID);

    WiFi.begin(SSID, SS_PASSWORD);
    // check the status of WiFi connection to be WL_CONNECTED
    while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY))
    {
      retries++;
      delay(WIFI_RETRY_DELAY);
      Serial.print("#");
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.print("Connetted to ");
      Serial.print(SSID);
      Serial.print("--- IP: ");
      Serial.println(WiFi.localIP());

      //lcd
      lcd.setCursor(0, 0);
      lcd.print("Use this IP ");
      lcd.setCursor(0, 1);
      lcd.print(WiFi.localIP());
    }
    else
    {
      Serial.print("Error connecting to: ");
      Serial.println(SSID);
    }
  }
};
