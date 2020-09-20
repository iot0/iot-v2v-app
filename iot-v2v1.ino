#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiUdp.h>
#include <Ticker.h>
#include "UltraSonic.h";
#include "Common.h";
#include "WifiSetup.h";
#include "ApiSetup.h";
#include "UdpSetup.h";
#include "Device.h";

TinyGPS gps;
SoftwareSerial sgps(12, 13); //GPIO D6-- D7--- RX GPS)--D7 NodeMcu), TX (GPS)--D6 (NodeMcu) for  module
ESP8266WebServer server(PORT);
LiquidCrystal_I2C lcd(0x27, 16, 2);
std::vector<Device> devices;
char packet[255];
float latitude, longitude, distance;
UltraSonic sonic;
Ticker ticker;

// UDP
WiFiUDP UDP;

void setup()
{
    sonic.init(5, 4);

    Serial.begin(115200);
    delay(10);
    Serial.println("\r\n");

    sgps.begin(9600);
    Wire.begin(0, 2);
    lcd.begin();

    WifiSetup::initWiFi();

    ApiSetup::initRoutingConfig();

    server.begin();
    Serial.println("HTTP REST Server Started");

    UdpSetup::init();

    ticker.attach_ms(2000, UdpSetup::broadcast);
}

void loop()
{
    server.handleClient();
    UdpSetup::listen();
    //GPS
    while (sgps.available())
    {
        int c = sgps.read();
        if (gps.encode(c))
        {
            gps.f_get_position(&latitude, &longitude);
        }
    }

    // UdpSetup::broadcast();
    // delay(2000);
}
