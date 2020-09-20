#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiUdp.h>
#include "Device.h"
#include "UltraSonic.h";
#define DBG_OUTPUT_PORT Serial
#define WIFI_RETRY_DELAY 500
#define MAX_WIFI_INIT_RETRY 50
#define PORT 80
#define UDP_PORT 4210
#define SSID "Asianet"
#define SS_PASSWORD "9567976004"

extern ESP8266WebServer server;
extern LiquidCrystal_I2C lcd;
extern std::vector<Device> devices;
extern WiFiUDP UDP;
extern UltraSonic sonic;
extern char packet[255];
extern float latitude, longitude, distance;