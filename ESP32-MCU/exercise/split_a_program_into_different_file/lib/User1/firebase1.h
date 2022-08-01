#ifndef _FIREBASE1_H_
#define _FIREBASE1_H_

#ifndef _FIREBASEESP32_H_
#define _FIREBASEESP32_H_
#include <FirebaseESP32.h>
#endif

#define FIREBASE_HOST "https://tt-iot-utc-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "I8dY6yv4GrCOAASGRfkmOy1nlM4BOrxCT5jCHXWM"

void setFirebase();
void getFirebase();

#endif