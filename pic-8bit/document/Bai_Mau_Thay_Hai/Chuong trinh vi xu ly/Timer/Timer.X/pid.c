
#define KP_SENSOR      0.15      //0.07
#define KE_SENSOR      44.3487   //15.0256
#define KE1_SENSOR      1.023    //2.385
#define KE2_SENSOR      0.01     //0.69
//KI_SENSOR=1+T/Ti
//  T thoi gian trich mau =0.002s=2ms
// Ti He so tich phan     =0.0005s=0.5ms
#define SENSOR_MAX      10
#define SENSOR_MIN      2

//********************************************************* 
//Chuong trinh cu
//#define KP_SENSOR      0.07
 #define KI_SENSOR      10
//********************************************************


int delta_i,delta_i1,delta_i2;
extern unsigned int ADC_Value;
extern unsigned char Heso_U;
unsigned int SetpointSensor=200;

unsigned char Pid_sensor(void)// vong phan hoi trong dam bao do dong deu   0.1ms thuc hien 26ms goi 1 lan voi toc do cao
{                                                                                                 //121 ms voi toc so thap
float Value_i;
Value_i=Heso_U;
delta_i2=delta_i1;
delta_i1=delta_i;
delta_i=SetpointSensor-ADC_Value;  //Khoi luong do 100 -120 voi trong luong tu 25 den 30 g/m
Value_i=Value_i+KP_SENSOR*(delta_i*KE_SENSOR-KE1_SENSOR*delta_i1+KE2_SENSOR*delta_i2);
//*************************************************************************************
//Value_i=Value_i+KP_SENSOR*(delta_i*KI_SENSOR-delta_i1);
//************************************************************************************

  if (Value_i>SENSOR_MAX) Value_i=SENSOR_MAX;
if (Value_i<SENSOR_MIN) Value_i=SENSOR_MIN;
return((unsigned char)Value_i);
}