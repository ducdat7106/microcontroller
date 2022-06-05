int soundSensorPin=39;//GPIO39

long valSound;
int soundArray[100];
int countSoundSmall=0;
int countSoundBig=0;
int countSoundVeryBig=0;
int countSoundMax=0; 


void setup() 
{
  Serial.begin(9600);
  //pinMode(soundSensorPin, INPUT);
}

void loop() 
{
//  valSound=analogRead(soundSensorPin);
//  Serial.println(valSound);
//  delay(10);
  
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
}
