#include "wifis.h"

void initConnectWifi()
{
    delay(1000);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Dang ket noi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("Da ket noi WiFi!");
    Serial.println(WiFi.localIP());
}