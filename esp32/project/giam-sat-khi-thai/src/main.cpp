#include "main.h"

char auth[] = BLYNK_AUTH_TOKEN;

const char ssid[] = "Viettel Telecom";
const char password[] = "dat123456789";

Sensor_Using sensor_using;

FirebaseData firebase_data;

SharpGP2Y10 dustSensor(sensor_using.Dust_Sensor.Pin_Sensor, sensor_using.Dust_Sensor.Pin_Led);

int led_connect_wifi = 2;
int led_messenger_safe = 21;
int led_messenger_danger = 22;

unsigned int maxAnalog = 1023;
unsigned int minAnalog = 0;

// Led on app blynk
WidgetLED CoAppLedSafe(V2);
WidgetLED CoAppLedDanger(V3);

WidgetLED SoundAppLedSafe(V12);
WidgetLED SoundAppLedDanger(V13);

WidgetLED DustAppLedSafe(V22);
WidgetLED DustAppLedDanger(V23);

WidgetLED GasAppLedSafe(V42);
WidgetLED GasAppLedDanger(V43);

WidgetLCD LCDs(V100);

void setup()
{
  Serial.begin(115200);

  Init_Hardware();

  Init_Sensor(&sensor_using);

  Init_Connect_Wifi();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  Current_Connect_Wifi();
  Get_Value_Set_From_Firebase(&sensor_using);
  Set_Data_To_Firebase(sensor_using);

  changeTimeReadSensor(&sensor_using);
  readSensor(&sensor_using);

  delay(1000);
}

void Init_Hardware()
{
  //----------led connect wifi
  pinMode(led_connect_wifi, OUTPUT);
  digitalWrite(led_connect_wifi, LOW);

  //------------led messenger safe or danger
  pinMode(led_messenger_safe, OUTPUT);
  digitalWrite(led_messenger_safe, LOW);

  pinMode(led_messenger_danger, OUTPUT);
  digitalWrite(led_messenger_danger, LOW);
}

void Init_Connect_Wifi()
{
  Serial.println("Connecting to: " + String(ssid));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected successful.\nIP address: ");
  Serial.println(WiFi.localIP());
}

void Current_Connect_Wifi()
{
  static uint32_t t_handle;
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(led_connect_wifi, HIGH);
    if (millis() - t_handle >= 10000)
    {
      Serial.println("Connect wifi successful.");
      t_handle = millis();
    }
  }
  else
  {
    digitalWrite(led_connect_wifi, LOW);
    if (millis() - t_handle >= 10000)
    {
      Serial.println("Lost connect wifi. Preset check connect.");
      t_handle = millis();
    }
  }
}

void Init_Sensor(Sensor_Using *sensor)
{
  // pin sensor
  sensor->Co_Sensor.Pin_Sensor = 36;
  sensor->Gas_Sensor.Pin_Sensor = 39;
  sensor->Sound_Sensor.Pin_Sensor = 32;
  sensor->Dust_Sensor.Pin_Sensor = 34;
  sensor->Dust_Sensor.Pin_Led = 35;

  pinMode(sensor->Co_Sensor.Pin_Sensor, INPUT);
  pinMode(sensor->Gas_Sensor.Pin_Sensor, INPUT);
  pinMode(sensor->Dust_Sensor.Pin_Sensor, INPUT);
  pinMode(sensor->Sound_Sensor.Pin_Sensor, INPUT);
  pinMode(sensor->Dust_Sensor.Pin_Led, OUTPUT);

  // value map function
  sensor->Co_Sensor.lowerLimit = 20;
  sensor->Co_Sensor.upperLimit = 900;

  sensor->Gas_Sensor.lowerLimit = 200;
  sensor->Gas_Sensor.upperLimit = 2000;

  sensor->Dust_Sensor.lowerLimit = 1000;
  sensor->Dust_Sensor.upperLimit = 3000;

  sensor->Sound_Sensor.lowerLimit = 3000;
  sensor->Sound_Sensor.upperLimit = 4000;

  // time read new
  sensor->time_read = 1000;
}

// void Init_Value_Set_Firebase(Sensor_Using *sensor)
// {

// }

void Get_Value_Set_From_Firebase(Sensor_Using *sensor)
{
  sensor->Co_Sensor.Value_Set = Firebase.getInt(firebase_data, "Node1/factory/value_set/co");
  if (sensor->Co_Sensor.Value_Set)
    sensor->Co_Sensor.Value_Set = firebase_data.to<unsigned int>();

  sensor->Gas_Sensor.Value_Set = Firebase.getInt(firebase_data, "Node1/factory/value_set/gas");
  if (sensor->Gas_Sensor.Value_Set)
    sensor->Gas_Sensor.Value_Set = firebase_data.to<unsigned int>();

  sensor->Dust_Sensor.Value_Set = Firebase.getInt(firebase_data, "Node1/factory/value_set/dust");
  if (sensor->Dust_Sensor.Value_Set)
    sensor->Dust_Sensor.Value_Set = firebase_data.to<unsigned int>();

  sensor->Sound_Sensor.Value_Set = Firebase.getInt(firebase_data, "Node1/factory/value_set/sound");
  if (sensor->Sound_Sensor.Value_Set)
    sensor->Sound_Sensor.Value_Set = firebase_data.to<unsigned int>();

  Serial.println("value set co-gas-dust-sound:\t" +
                 String(sensor->Co_Sensor.Value_Set) + "\t" +
                 String(sensor->Gas_Sensor.Value_Set) + "\t" +
                 String(sensor->Dust_Sensor.Value_Set) + "\t" +
                 String(sensor->Sound_Sensor.Value_Set));
}

void Set_Data_To_Firebase(Sensor_Using sensor)
{
  Firebase.setInt(firebase_data, "Node1/factory/value_use/co", sensor.Co_Sensor.Value_Use);
  Firebase.setInt(firebase_data, "Node1/factory/value_use/gas", sensor.Gas_Sensor.Value_Use);
  Firebase.setInt(firebase_data, "Node1/factory/value_use/dust", sensor.Dust_Sensor.Value_Use);
  Firebase.setInt(firebase_data, "Node1/factory/value_use/sound", sensor.Sound_Sensor.Value_Use);

  Serial.println("value use co-gas-dust-sound:\t" +
                 String(sensor.Co_Sensor.Value_Use) + "\t" +
                 String(sensor.Gas_Sensor.Value_Use) + "\t" +
                 String(sensor.Dust_Sensor.Value_Use) + "\t" +
                 String(sensor.Sound_Sensor.Value_Use));
}

void read_CoSensor(Sensor_Using *sensor)
{
  // sensor->Co_Sensor.Value_Basic = analogRead(sensor->Co_Sensor.Pin_Sensor);
  sensor->Co_Sensor.Value_Use = 30; // map(sensor->Co_Sensor.Value_Basic, minAnalog, maxAnalog, sensor->Co_Sensor.lowerLimit, sensor->Co_Sensor.upperLimit);
}

void read_GasSensor(Sensor_Using *sensor)
{
  // sensor->Gas_Sensor.Value_Basic = analogRead(sensor->Gas_Sensor.Pin_Sensor);
  sensor->Gas_Sensor.Value_Use = 40; // map(sensor->Gas_Sensor.Value_Basic, minAnalog, maxAnalog, sensor->Gas_Sensor.lowerLimit, sensor->Gas_Sensor.upperLimit);
}

void read_DustSensor(Sensor_Using *sensor)
{
  // sensor->Dust_Sensor.Value_Basic = dustSensor.getDustDensity();
  sensor->Dust_Sensor.Value_Use = 70; // map(sensor->Dust_Sensor.Value_Basic, minAnalog, maxAnalog, sensor->Dust_Sensor.lowerLimit, sensor->Dust_Sensor.upperLimit);
}

void read_SoundSensor(Sensor_Using *sensor)
{
  // sensor->Sound_Sensor.Value_Basic = analogRead(sensor->Sound_Sensor.Pin_Sensor);
  sensor->Sound_Sensor.Value_Use = 39; // map(sensor->Sound_Sensor.Value_Basic, minAnalog, maxAnalog, sensor->Sound_Sensor.lowerLimit, sensor->Sound_Sensor.upperLimit);
}

void printValueReadSensor(Sensor_Using sensor)
{
  Serial.println("\n\nCo value basic: " + String(sensor.Co_Sensor.Value_Basic) + "  value use: " + String(sensor.Co_Sensor.Value_Use));
  Serial.println("Gas value basic: " + String(sensor.Gas_Sensor.Value_Basic) + "  value use: " + String(sensor.Gas_Sensor.Value_Use));
  Serial.println("Dust value basic: " + String(sensor.Dust_Sensor.Value_Basic) + "  value use: " + String(sensor.Dust_Sensor.Value_Use));
  Serial.println("Sound value basic: " + String(sensor.Sound_Sensor.Value_Basic) + "  value use: " + String(sensor.Sound_Sensor.Value_Use));
}

void changeTimeReadSensor(Sensor_Using *sensor)
{
  if (sensor->Co_Sensor.Value_Use <= sensor->Co_Sensor.Value_Set &&
      sensor->Gas_Sensor.Value_Use <= sensor->Gas_Sensor.Value_Set &&
      sensor->Dust_Sensor.Value_Use <= sensor->Dust_Sensor.Value_Set &&
      sensor->Sound_Sensor.Value_Use >= sensor->Sound_Sensor.Value_Set)
    sensor->time_read = 10000;
  else
    sensor->time_read = 1000;
}

void readSensor(Sensor_Using *sensor)
{
  static uint32_t time_wait = 0;
  if (millis() - time_wait >= sensor->time_read)
  {
    read_CoSensor(sensor);
    read_GasSensor(sensor);
    read_DustSensor(sensor);
    read_SoundSensor(sensor);

    time_wait = millis();
  }
}

void check_safe(Sensor_Using *Sensor)
{
  /*
    safe == 1
    danger == 0
  */
  if (Sensor->Co_Sensor.Value_Use < Sensor->Co_Sensor.Value_Set)
    Sensor->Co_Sensor.Safe_State = 1;
  else
    Sensor->Co_Sensor.Safe_State = 0;

  if (Sensor->Gas_Sensor.Value_Use < Sensor->Gas_Sensor.Value_Set)
    Sensor->Gas_Sensor.Safe_State = 1;
  else
    Sensor->Gas_Sensor.Safe_State = 0;

  if (Sensor->Dust_Sensor.Value_Use < Sensor->Dust_Sensor.Value_Set)
    Sensor->Dust_Sensor.Safe_State = 1;
  else
    Sensor->Dust_Sensor.Safe_State = 0;

  if (Sensor->Sound_Sensor.Value_Use < Sensor->Sound_Sensor.Value_Set)
    Sensor->Sound_Sensor.Safe_State = 1;
  else
    Sensor->Sound_Sensor.Safe_State = 0;
}

void control_led_hardware(Sensor_Using Sensor)
{
  if (Sensor.Co_Sensor.Safe_State &&
      Sensor.Gas_Sensor.Safe_State &&
      Sensor.Dust_Sensor.Safe_State &&
      Sensor.Sound_Sensor.Safe_State)
  {
    digitalWrite(led_messenger_safe, HIGH);
    digitalWrite(led_messenger_danger, LOW);
  }
  else
  {
    digitalWrite(led_messenger_safe, LOW);
    digitalWrite(led_messenger_danger, HIGH);
  }
}

void runBlynks(Sensor_Using Sensor)
{
  Blynk.run();

  // Transmit data from esp32 to Blynk App
  Blynk.virtualWrite(V1, Sensor.Co_Sensor.Value_Use);
  Blynk.virtualWrite(V11, Sensor.Gas_Sensor.Value_Use);
  Blynk.virtualWrite(V21, Sensor.Dust_Sensor.Value_Use);
  Blynk.virtualWrite(V31, Sensor.Sound_Sensor.Value_Use);
}

void controll_Led_App_Blynk(Sensor_Using Sensor)
{
  if (Sensor.Co_Sensor.Safe_State)
  {
    CoAppLedSafe.on();
    CoAppLedDanger.off();
  }
  else
  {
    CoAppLedSafe.off();
    CoAppLedDanger.on();
  }

  if (Sensor.Gas_Sensor.Safe_State)
  {
    GasAppLedSafe.on();
    GasAppLedDanger.off();
  }
  else
  {
    GasAppLedSafe.off();
    GasAppLedDanger.on();
  }

  if (Sensor.Dust_Sensor.Safe_State)
  {
    DustAppLedSafe.on();
    DustAppLedDanger.off();
  }
  else
  {
    DustAppLedSafe.off();
    DustAppLedDanger.on();
  }

  if (Sensor.Sound_Sensor.Safe_State)
  {
    SoundAppLedSafe.on();
    SoundAppLedDanger.off();
  }
  else
  {
    SoundAppLedSafe.off();
    SoundAppLedDanger.on();
  }
}

// No support for web blynk
void write_Lcd_Basic()
{
  /*
    + Transmit data up lcd in app blynk
    + Lcd on app must setup basic mode
  */
  Blynk.virtualWrite(V100, "CO_CValue Res: " + String(100));
}

void write_Lcd_Advanced(Sensor_Using Sensor)
{
  /*
    Lcd on app must setup advanced mode
  */

  LCDs.print(0, 0, "  environment:  ");

  if (Sensor.Co_Sensor.Safe_State &&
      Sensor.Gas_Sensor.Safe_State &&
      Sensor.Dust_Sensor.Safe_State &&
      Sensor.Sound_Sensor.Safe_State)
    LCDs.print(5, 1, "  safe  ");
  else
    LCDs.print(5, 1, " danger ");
}

void control_display(Sensor_Using Sensor)
{
  check_safe(&Sensor);
  control_led_hardware(Sensor);
  controll_Led_App_Blynk(Sensor);
  write_Lcd_Advanced(Sensor);
}


