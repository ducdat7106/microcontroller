#include <Arduino.h>
#include "var.h"

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid = "Viettel Telecom";
const char *password = "dat123456789";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void initWifi();
void initTimeClient();
// esp32
void currentTimeAndDate();

// esp8266/esp32
void currentTime();
void currentData();

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(115200);

  initWifi();

  initTimeClient();
}

void loop()
{
  while (!timeClient.update())
  {
    timeClient.forceUpdate();
  }
  // currentTimeAndDate();
  //currentTime();
  currentData();
}

void initWifi()
{
  delay(1000);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("\nWiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void initTimeClient()
{
  // Initialize a NTPClient to get time
  timeClient.begin();

  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0

  // GMT 0 = 0
  // timeClient.setTimeOffset(0);

  //--> VIET NAM GMT +7 = 3600x7=25200
  timeClient.setTimeOffset(25200);
}

void currentTimeAndDate()
{
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  String formattedDate = timeClient.getFormattedDate();
  Serial.println("\n" + formattedDate);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  String dayStamp = formattedDate.substring(0, splitT);
  Serial.println("DATA: " + dayStamp);

  // Extract time
  String timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
  Serial.println("HOUR: " + timeStamp);

  delay(1000); // each 1s will print time and data once
}

void currentTime()
{
  // The getFormattedTime() function returns the time in HH:MM:SS format.
  String formattedTime = timeClient.getFormattedTime();
  Serial.println("\n\nFormatted Time: " + formattedTime);

  int currentHour = timeClient.getHours();
  Serial.print(" Hour: " + String(currentHour));

  int currentMinute = timeClient.getMinutes();
  Serial.print(" Minutes: " + String(currentMinute));

  int currentSecond = timeClient.getSeconds();
  Serial.print(" Seconds: " + String(currentSecond));

  delay(1000);
}

/*
The getDay() function returns a number from 0 to 6, in which 0 corresponds to Sunday and 6 to Saturday.
*/
void currentData()
{
  String weekDay = weekDays[timeClient.getDay()];
  Serial.println("\n\nWeek Day: " + weekDay);

  unsigned long epochTime = timeClient.getEpochTime();
  //Serial.println("Epoch Time: " + String(epochTime));

  struct tm *ptm = gmtime((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  Serial.println("Month day: " + String(monthDay));

  /* the tm_mday starts at 0, we add 1 to the month so that January corresponds to 1, February to 2, and so on.*/
  int currentMonth = ptm->tm_mon + 1;
  Serial.print("Month: " + String(currentMonth)+"\t");

  // The arrays numbering starts at 0, that’s why we subtract 1.
  String currentMonthName = months[currentMonth - 1];
  Serial.println("Month name: " + currentMonthName);

  // To get the year, we need to add 1900 because the tm_year saves the number of years after 1900.
  int currentYear = ptm->tm_year + 1900;
  Serial.println("Year: " + String(currentYear));

  // we create a String called currentDate that holds the current date in the YYYY-MM-DD format.
  String currentDate = String(monthDay) + "-" + String(currentMonth) + "-" + String(currentYear);
  Serial.println("Current date: " + currentDate);

  delay(10000);
}