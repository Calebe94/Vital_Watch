
#define SENSORPULSE 13
#define LM35 A1
#define NSAMPLES 10
#define AUXSIZE 5
#define STRSIZE 10
#define delay_ms 1000
/* Global Variables */
unsigned int times[NSAMPLES],aux=0,iCount=0,cont=0;

uint8_t Data_Sended = false,First_Data = false;

void setup() {
  pinMode(LM35,INPUT);
  Serial.begin(9600);
  times[0]=millis();
  aux = times[0];
}
int analogTemp = 0;
void loop(){
  if(analogRead(A0) < 800){   
    if(First_Data == false) {
        Serial.write(0);
        Serial.flush();
        Serial.write(0);
        Serial.flush();
        First_Data = true;
    }
    pinMode(SENSORPULSE,INPUT);
    if(digitalRead(SENSORPULSE)==HIGH){
      while(digitalRead(SENSORPULSE)==HIGH){}
      cont++;
      analogTemp = analogRead(LM35)+analogTemp;
      iCount++;
    }
    times[1]=millis();
    if((times[1]-aux) > 10000){
      
      Serial.flush();
      analogTemp = analogTemp / iCount;
      Data_Sended = false;
      Serial.write(analogTemp);
      Serial.flush();
      Serial.write(iCount*6);
      Serial.flush();
      aux = millis();
      iCount = 0; analogTemp = 0;
    }
    if((times[1]-times[0]) > 60000){
      analogTemp = analogTemp / iCount;
      Serial.write(analogTemp);
      Serial.flush();
      Serial.write(cont);
      Serial.flush();
      times[0]=millis();
      cont = 0; analogTemp = 0; iCount = 0;
    }
  }
  if(analogRead(A0)>800){
    if(Data_Sended == false){
      uint8_t dataToSend = 0;
      
      pinMode(SENSORPULSE,OUTPUT);// Only to do not receive any data in this pin
      Serial.flush();
      for(unsigned int count = 0; count < 2 ; count ++){
        Serial.write(dataToSend);
        Serial.flush();
        Serial.write(dataToSend);
        Serial.flush();
        delay(1);
      }
      iCount = 0; cont = 0;  analogTemp = 0;
      Data_Sended = true;
      First_Data = false;
    }
    else if(Data_Sended == true && analogRead(A0) > 800 ) blinkLED(Data_Sended);
  }
}
void blinkLED(uint8_t Data){
  static unsigned long int currentTime = 0, previousTime = 0;
  currentTime = millis();
  if(Data == true && currentTime - previousTime > delay_ms){
    previousTime = currentTime;
    digitalWrite(SENSORPULSE,!digitalRead(SENSORPULSE));
  }
}
