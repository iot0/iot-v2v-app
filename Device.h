#ifndef DEVICE_H
#define DEVICE_H
#include <Arduino.h>
#include <ArduinoJson.h>
class Device
{
private:
  int Id;

public:
  String Ip;
  String MacId;
  String Latitude;
  String Longitude;
  String Distance;
  void init(String ip, String macId, String latitude, String longitude, String distance);
  String toString();
  JsonObject& toJson();

  static String serialize();
  static Device getThisDevice();
  static void removeFromDevices(String ip);
  static void addToDevices(Device device);
};

#endif