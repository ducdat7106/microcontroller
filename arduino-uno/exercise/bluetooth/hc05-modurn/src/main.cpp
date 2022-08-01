#include <Arduino.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

char w=' ';
char *ch;

int value = 0;

char *receiveDataString();
char ReceiveCharData();


void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000); // wait to start the device properly
  Serial.println("Start bluetooth.");
}

void loop()
{

  // ch = receiveDataString();
  // if (value == 0)
  // {
  //   Serial.println("return string receive: " + String(ch) );
  // }

  w = ReceiveCharData();
  if (value == 2)
  {
    Serial.print("return char receive: ");
    Serial.println(w);
    Serial.println(w);
  }

  value = 1;

  // delete[] ch;
  // ch=NULL;
}

char *receiveDataString()
{
  static int flag = 0;
  int i = 0;
  char *str = NULL;
  String S = "";

  if (mySerial.available())
  {
    S = mySerial.readString();
    flag = 1;
  }
  size_t len = S.length() - 2;

  str = new char[len];
  if (!str)
    return NULL;

  for (i = 0; i < (int)len; i++)
    str[i] = S[i];
  str[i] = '\0';

  if (flag == 1)
  {
    flag = 0;
    value = 0;
  }

  return str;
}

void ReceiveString()
{
  String s = "";
  if (mySerial.available())
  {
    s = mySerial.readString();
    value = s.length();
    Serial.println("receive" + s + String(value));
  }
}

char ReceiveCharData()
{
  char ch;

  if (mySerial.available())
  {
    ch = mySerial.read();
    Serial.print("char receive : ");
    Serial.println(ch);
    value = 2;
  }

  return ch;
}

void ReceiveChar()
{
  char ch;

  if (mySerial.available())
  {
    ch = mySerial.read();
    Serial.println("char receive" + ch);
  }
}