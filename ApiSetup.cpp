#include <vector>
#include <ArduinoJson.h>
#include "Common.h";
#include "ApiSetup.h";
#include "Device.h";

void ApiSetup::initRoutingConfig()
{
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html",
                    "Welcome to the IOT v2v Communication");
    });
    server.on("/status", HTTP_GET, getStatus);
    // server.on("/updateEventAlert", HTTP_POST, updateEventAlert); // Call the 'update_alertmode' function when a POST request is made to URI "//update_alertmode"

    server.onNotFound(handleNotFound);
}
void ApiSetup::getStatus()
{
    prepareHeader();
    server.send(200, "application/json",  Device::serialize());
}
void ApiSetup::prepareHeader()
{
    // ... some code to prepare the response data...
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "*");
}
void ApiSetup::handleNotFound()
{
    if (server.method() == HTTP_OPTIONS)
    {
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.sendHeader("Access-Control-Max-Age", "10000");
        server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
        server.sendHeader("Access-Control-Allow-Headers", "*");
        server.send(204);
    }
    else
    {
        String message = "File Not Found\n\n";
        message += "URI: ";
        message += server.uri();
        message += "\nMethod: ";
        message += (server.method() == HTTP_GET) ? "GET" : "POST";
        message += "\nArguments: ";
        message += server.args();
        message += "\n";

        for (uint8_t i = 0; i < server.args(); i++)
        {
            message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
        }

        server.send(404, "text/plain", message);
    }
}