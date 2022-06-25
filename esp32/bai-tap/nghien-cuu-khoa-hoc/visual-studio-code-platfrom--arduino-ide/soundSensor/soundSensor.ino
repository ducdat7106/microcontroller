int coSensorPin=39;//GPIO39
int gasSensorPin=36;//GPIO39
int soundSensoer= 32;

float valGas;
float valCo;
float valSound;
int soundArray[100];
int countSoundSmall=0;
int countSoundBig=0;
int countSoundVeryBig=0;
int countSoundMax=0; 


void setup() 
{
  Serial.begin(115200);
  pinMode(coSensorPin, INPUT);
  pinMode(gasSensorPin, INPUT);
  pinMode(soundSensoer, INPUT);
}

void loop() 
{
//  valGas=analogRead(gasSensorPin);
//  valCo=analogRead(coSensorPin);
  valSound = analogRead(soundSensoer);
//  Serial.println("gas  "+String(valGas));
//  Serial.println("Co   "+String(valCo));
  Serial.println("Sound   "+String(valSound));
  delay(1000);
  /*
  for(int i=0;i<50;i++)
  {
      soundArray[i]= analogRead(soundSensorPin);
      delay(2);
  }

  for(int i=0; i<50; i++)
  {
    if(soundArray[i]>2950)
      countSoundSmall++;
    if(soundArray[i]>3200)
      countSoundBig++;
    if(soundArray[i]>3500)
     countSoundVeryBig++;
    if(soundArray[i]>4000)
      countSoundMax++;
  }

  if(countSoundSmall >= 5)
  {
    Serial.println("Sound Small");
  }
  if(countSoundBig>=5)
  {
   Serial.println("sound Big");
  }
  if(countSoundVeryBig>=5)
  {
    Serial.println("sound very Big");
  }
  if(countSoundMax>=5)
  {
    Serial.println("noisy! Stop work now");
  }
   
  countSoundSmall=0;
  countSoundBig=0;
  countSoundVeryBig=0;
  countSoundMax=0;
  
  for(int i=0; i<50; i++)
    soundArray[i]=0;
    */
}
