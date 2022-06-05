#include "firebase1.h"

FirebaseData fbdata;

int x1s = 10, y1s = 23;
int results, x2s, y2s;

void setFirebase()
{
    Firebase.setInt(fbdata, "Node1/Temp", x1s);
    Firebase.setInt(fbdata, "Node1/Humi", y1s);
}

void getFirebase()
{
    results = Firebase.getInt(fbdata, "/Node1/Temp");
    if (results)
    {
        x2s = fbdata.to<int>();
    }

    results = Firebase.getInt(fbdata, "/Node1/Humi");
    if (results)
    {
        y2s = fbdata.to<int>();

        Serial.println("x2= " + String(x2s) + " y2= " + String(y2s));
    }
}
