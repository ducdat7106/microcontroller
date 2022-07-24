/*
 * *
 */
#define PWM_FREQUENCY  50 //Hz // this variable is used to define the time period 
#define PWM_CHANNEL  0 // this variable is used to select the channel number
#define PWM_RESOUTION  8 // this will define the resolution of the signal which is 8 in this case
#define GPIOPIN  23  // GPIO to which we want to attach this channel signal

/*With 8 bit resolution, we can specify the duty cycle between 0 and (2^8-) = 255.
So if we use 255 as a duty cycle parameter, the duty cycle will be 100% and with 127 duty cycle 
will be 50% and similarly for other values.
*/
#define dutyCycle  10 // it will define the width of signal or also the one time

void setup()
{

ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOUTION);
ledcAttachPin(GPIOPIN, PWM_CHANNEL);


}

void loop() 
{
 /*
 255          20ms
 ?            0.5ms/1.5ms/2.5ms

 0.5ms --> ? = 6
 1.5ms --> ? = 19
 2.5ms --> ? = 32
 */
  //ledcWrite(PWM_CHANNEL, 6);//vi tri 180 degree (khong biet tai sao no bi nguoc voi vi tri 0)
  //delay(1000);

  //ledcWrite(PWM_CHANNEL, 19);//vi tri 90 degree
  //delay(1000);

  //ledcWrite(PWM_CHANNEL, 32);//vi tri 0 degree (khong biet tai sao no bi nguoc voi vi tri 180)
  //delay(1000);

  for(int i=5; i<=32; i++)
  {
    ledcWrite(PWM_CHANNEL, i);
    delay(100);
  }
  ledcWrite(PWM_CHANNEL, 5);
  delay(2000);
}
