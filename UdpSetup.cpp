#include <vector>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include "Common.h";
#include "UdpSetup.h";
#include "Device.h";

void UdpSetup::init()
{
    // Begin listening to UDP port
    UDP.begin(UDP_PORT);
    Serial.print("Listening on UDP port ");
    Serial.println(UDP_PORT);
}

void UdpSetup::listen()
{
    // If packet received...
    int packetSize = UDP.parsePacket();
    if (packetSize)
    {
        Serial.print("Received packet! Size: ");
        Serial.println(packetSize);
        int len = UDP.read(packet, 255);
        if (len > 0)
        {
            packet[len] = '\0';
        }
        Serial.print("Packet received: ");
        Serial.println(packet);

        // // Send return packet
        // UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
        // UDP.write(reply);
        // UDP.endPacket();

        StaticJsonBuffer<500> jsonBuffer;
        JsonObject &jsonBody = jsonBuffer.parseObject(packet);

        if (!jsonBody.success())
        {
            Serial.println("error in parsin json body");
        }
        else
        {
            Device d;
            d.init(jsonBody["ip"], jsonBody["macId"], jsonBody["latitude"], jsonBody["longitude"], jsonBody["distance"]);
            Device::addToDevices(d);
        }
    }
}
void UdpSetup::broadcast()
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[200];
    Device thisDevice = Device::getThisDevice();
    jsonObj["ip"] = thisDevice.Ip;
    jsonObj["macId"] = thisDevice.MacId;
    jsonObj["latitude"] = thisDevice.Latitude;
    jsonObj["longitude"] = thisDevice.Longitude;
    jsonObj["distance"] = thisDevice.Distance;

    jsonObj.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

    IPAddress SendIP = WiFi.localIP();
    SendIP[3] = 255;

    UDP.beginPacketMulticast(SendIP, UDP_PORT, WiFi.localIP());
    // UDP.beginPacket(SendIP, UDP_PORT);
    UDP.write(JSONmessageBuffer);
    UDP.endPacket();
}
