
#define SENSORPULSE 13
#define LM35 A1
#define NSAMPLES 10

/* Global Variables */
unsigned int BPM=0,times[NSAMPLES],aux=0,iCount=0,average[NSAMPLES-1],pulse=0,heartBeat=0,cont=0;
char string[20];

void setup() {
  pinMode(LM35,INPUT);
  Serial.begin(9600);
  times[0]=millis();
  aux = times[0];
}

uint8_t Data_Sended = false;

void loop() {
  while(analogRead(A0) < 800){   
    pinMode(SENSORPULSE,INPUT);
    if(digitalRead(SENSORPULSE)==HIGH){
      while(digitalRead(SENSORPULSE)==HIGH){}
      cont++;
      iCount++;
    }
    times[1]=millis();
    if((times[1]-aux) > 10000){
      
      Data_Sended = false;
      
      Serial.write(analogRead(LM35));
      Serial.flush();
      Serial.write(iCount*6);
      aux = millis();
      iCount = 0;
    }
    if((times[1]-times[0]) > 60000){
      Serial.write(analogRead(LM35));
      Serial.flush();
      Serial.write(cont);
      times[0]=millis();
      cont = 0;
    }
  }
  if(Data_Sended == false){
    pinMode(SENSORPULSE,OUTPUT);// Only to do not receive any data in this pin
    Serial.write(0);
    Serial.flush();
    Serial.write(0);
    Data_Sended = true;
  }
}
