#include "Common.h"
#include <Arduino.h>
#include <ArduinoJson.h>

void Device::init(String ip, String macId, String latitude, String longitude, String distance)
{
    Ip = ip;
    MacId = macId;
    Latitude = latitude;
    Longitude = longitude;
    Distance = distance;
}

String Device::toString()
{
    return String("\"{'MacId':") + MacId + ",'Ip':'" + Ip + "}\"";
}

JsonObject &Device::toJson()
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &jsonObj = jsonBuffer.createObject();
    jsonObj["ip"] = Ip;
    jsonObj["macId"] = MacId;
    jsonObj["latitude"] = Latitude;
    jsonObj["longitude"] = Longitude;
    jsonObj["distance"] = Distance;
    return jsonObj;
}

//Static
Device Device::getThisDevice()
{
    Device d;
    d.init(WiFi.localIP().toString(), WiFi.macAddress(), String(latitude, 6), String(longitude, 6), String(sonic.distance(), 6));
    return d;
}
String Device::serialize()
{
    char JSONmessageBuffer[1000];
    StaticJsonBuffer<1000> jsonBuffer;
    JsonArray &array = jsonBuffer.createArray();

    for (int i = 0; i < devices.size(); i++)
    {
        JsonObject &jsonObj = array.createNestedObject();
        jsonObj["ip"] = devices[i].Ip;
        jsonObj["macId"] = devices[i].MacId;
        jsonObj["latitude"] = devices[i].Latitude;
        jsonObj["longitude"] = devices[i].Longitude;
        jsonObj["distance"] = devices[i].Distance;
    }
    Device thisD = getThisDevice();
    JsonObject &jsonObj = array.createNestedObject();
    jsonObj["ip"] = thisD.Ip;
    jsonObj["macId"] = thisD.MacId;
    jsonObj["latitude"] = thisD.Latitude;
    jsonObj["longitude"] = thisD.Longitude;
    jsonObj["distance"] = thisD.Distance;

    array.printTo(JSONmessageBuffer);
    return JSONmessageBuffer;
}
void Device::removeFromDevices(String ip)
{
    //delete from vector
    Serial.println("On Delete from list .");
    for (int i = 0; i < devices.size(); i++)
    {
        if (devices[i].Ip == ip)
        {
            Serial.printf(" Deleted : %s .", ip.c_str());
            devices.erase(devices.begin() + i);
        }
    }
}
void Device::addToDevices(Device device)
{
    removeFromDevices(device.Ip);
    devices.push_back(device);
}