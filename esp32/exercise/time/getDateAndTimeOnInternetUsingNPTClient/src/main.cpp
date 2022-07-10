#include <Arduino.h>

#include "var.h"

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

typedef enum
{
  Get_Time_And_Date,
  Get_Time,
  Get_Date
} Time_Get_State;

// Replace with your network credentials
const char *ssid = "Viettel Telecom";
const char *password = "dat123456789";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void initWifi();
void initTimeClient();

// esp32
void getCurrentTimeAndDate();

// esp8266/esp32
void getCurrentTime();
void getCurrentData();

void time_Handle(Time_Get_State *time_get_states);


void setup()
{
  Serial.begin(115200);

  initWifi();

  initTimeClient();
}

void loop()
{
  Time_Get_State time_get_state = Get_Time;

  while (!timeClient.update())
  {
    timeClient.forceUpdate();
  }

  time_Handle(&time_get_state);
}

void initWifi()
{
  delay(1000);

  Serial.print("Connecting to: " + String(ssid));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("\nWiFi connected successful.\nIP address: ");
  Serial.println(WiFi.localIP());
}

void initTimeClient()
{
  /*
    Set offset time in seconds to adjust for your timezone, for example:
    GMT 0  = 0      ( = 3600 x 0 )
    GMT +1 = 3600   ( = 3600 x 1 )
    GMT +2 = 7200   ( = 3600 x 2 )
    ....
    GMT +8 = 28800  ( = 3600 x 8 )

    GMT -1 = -3600  ( = 3600 x -1 )
    GMT -2 = -7200  ( = 3600 x -2 )


    ------------------------- GMT value = ( 3600 x value ) ----------------------------------
    */

  // Initialize a NTPClient to get time
  timeClient.begin();

  // Vietnam -- GMT +7 = 3600x7 = 25200
  timeClient.setTimeOffset(25200);
}

void getCurrentTimeAndDate()
{
  /*
    The formattedDate comes with the following format:
    2018-05-28T16:00:13Z

    so we need to extract date and time
  */
  String formattedDate = timeClient.getFormattedDate();

  // position break string
  int splitT = formattedDate.indexOf("T");

  // Extract date
  String dayStamp = formattedDate.substring(0, splitT);

  // Extract time
  String timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);

  static unsigned long time_handle = 0;
  if (millis() - time_handle >= 1000) // each 1s will print time and data once
  {
    Serial.println("\n" + formattedDate);
    Serial.println("Date: " + dayStamp);
    Serial.println("Time: " + timeStamp);

    time_handle = millis();
  }
}

void getCurrentTime()
{
  // The getFormattedTime() function returns the time in HH:MM:SS format.
  String formattedTime = timeClient.getFormattedTime();

  int currentHour = timeClient.getHours();

  int currentMinute = timeClient.getMinutes();

  int currentSecond = timeClient.getSeconds();

  static unsigned long time_handle = 0;
  if (millis() - time_handle >= 1000) // each 1s will print once
  {
    Serial.print("\n\n\n\nFormatted Time: " + formattedTime);
    Serial.print("\nHour: " + String(currentHour));
    Serial.print("\nMinutes: " + String(currentMinute));
    Serial.print("\nSeconds: " + String(currentSecond));

    time_handle = millis();
  }
}

void getCurrentData()
{
  /*
      The getDay() function returns a number from 0 to 6,
    in which 0 corresponds to Sunday and 6 to Saturday.
  */
  String weekDay = weekDays[timeClient.getDay()];

  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;

  /* The tm_mday starts at 0, we add 1 to the month so that January corresponds to 1, February to 2, and so on.*/
  int currentMonth = ptm->tm_mon + 1;

  // The arrays numbering starts at 0, that’s why we subtract 1.
  String currentMonthName = months[currentMonth - 1];

  // To get the year, we need to add 1900 because the tm_year saves the number of years after 1900.
  int currentYear = ptm->tm_year + 1900;

  // we create a String called currentDate that holds the current date in the YYYY-MM-DD format.
  String currentDate = String(monthDay) + "-" + String(currentMonth) + "-" + String(currentYear);

  static unsigned long time_handle = 0;
  if (millis() - time_handle >= 10000) // each 10s will print once
  {
    // Serial.println("Epoch Time: " + String(epochTime));
    Serial.print("\n\n\nCurrent date: " + currentDate);

    Serial.println("Week Day: " + weekDay);

    Serial.println("Month day: " + String(monthDay));

    Serial.print("Month: " + String(currentMonth));
    Serial.println("\tMonth name: " + currentMonthName);

    Serial.println("Year: " + String(currentYear));

    time_handle = millis();
  }
}

void time_Handle(Time_Get_State *time_get_states)
{
  switch (*time_get_states)
  {
  case Get_Time_And_Date:
    getCurrentTimeAndDate();
    break;
  case Get_Time:
    getCurrentTime();
    break;
  case Get_Date:
    getCurrentData();
    break;
  }
}