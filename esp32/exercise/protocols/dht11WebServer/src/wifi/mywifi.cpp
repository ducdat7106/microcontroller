#include "mywifi.h"

// Replace with your network credentials
const char *ssid = "Viettel Telecom";
const char *password = "dat123456789";

void initConnectWifi()
{
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWifi: \n\t" + String(ssid));
    Serial.print("IP Address :\n\t");
    Serial.println(WiFi.localIP());
}