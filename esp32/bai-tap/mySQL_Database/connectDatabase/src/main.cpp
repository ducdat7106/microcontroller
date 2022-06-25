#include <Arduino.h>

#include <WiFi.h>

const char *ssid = "Viettel Telecom";
const char *password = "dat123456789";
const char *host = "your_hostname";

unsigned int temperature, humidity;
unsigned long last, timeout1 = 1000;

void initWifi();

void setup()
{

  Serial.begin(115200);

  initWifi();
  last = millis();
}

void loop()
{
  if (millis() - last >= timeout1)
  {
    temperature++;
    humidity++;
    if (temperature >= 20)
      temperature = 0;
    if (humidity >= 50)
      humidity = 5;

    Serial.println("temperature " + String(temperature) + "\thumidity " + String(humidity));

    last = millis();
  }

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 5555;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }

  // This will send the request to the server
  client.print(String("GET http://your_hostname/iot_project/connect.php?") +
               ("&temperature=") + temperature +
               ("&humidity=") + humidity +
               " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 1000)
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}

void initWifi()
{
  delay(3000);
  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
