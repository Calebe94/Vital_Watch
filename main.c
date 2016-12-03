/*scp ~/Projetos/Programacao_em_C/TODO/VeiWatch/teste.c pi@192.168.0.17:~/Programacao_em_C/TODO/VeiWatch/*/
#include"RaspberryGPIO.h"
#include<stdint.h>
#include"RPiNOKIA.h"
#include"HeartBeat.h"
#include"Logo.h"
#include"wiringSerial.h"
#include"SystemClock.h"
#include"VeiWatch.h"
#include <sys/ioctl.h>
/*Segundo o Datasheet do Sensor LM35, o fabricante garante uma resolução de	10mV/°C;
  O Mesmo opera com uma tensão de 4-30V, e possui um range de medida de -55-150°C.
	Portanto, esse coeficiente representa a tensão de alimentação do arduino, dividido por 10*10^-3
	que equivale a multiplicação por 100.
	*5 é a tensão de alimentação do arduino !
 */
#define COEF 4.88*100 // Nível de Tensão sobre o sensor vezes 100

#define RST 7
#define CE 	8
#define DC 	25
#define DIN 24
#define CLK 23

#define backLight		17
#define changeDisplay	27
/*Output GPIO*/
#define BL 18

const unsigned char SERIAL_PORT[2][30] = {"/dev/ttyAMA0","/dev/ttyUSB0"};

const unsigned int BAUDS[2] = {115200,9600};

uint8_t change_Layer = 0,mWatching=0;

Vei_Data control;

Vei_Data getData(unsigned int fd, struct sGENERAL perfil){
	Vei_Data receive;

	int result=0,bpm=0,temp=0;
	
	if(ioctl (fd, FIONREAD, &result) != -1){
		if(result>2){
			int temp=0,bpm=0;
			read(fd,&temp,1);
			read(fd,&bpm,1);

			receive.Temp = (float)(temp*COEF)/1023;
			receive.BPM = (unsigned int)bpm;		
			receive.BPMState = healthState(perfil,bpm);
			receive.TempState = isNormal(temp);
		return receive;
		}
	}	
}

void lcdDisplayMain(LCD display,unsigned int fd, struct sGENERAL perfil){

	char	Nokia_Temp[10],Nokia_BPM[10],INFO1[15],INFO2[15],data[15],hora[15];
	int result;
	control = getData(fd,perfil);
	getClockInformation(&info);
	if(change_Layer == 0 && mWatching == 0){

		NOKIABitmap(display,main_display);		delay_ms(1000);	
		mWatching = 1;
		control.lastMinute = info.minute;
		printf("1-)Tela Principal!\n");
		snprintf(Nokia_Temp,10,"%.1f*C",control.Temp);
		snprintf(Nokia_BPM,10,"%dBPM",control.BPM);
		snprintf(INFO1,15,"%s",control.BPMState);
		snprintf(INFO2,15,"%s",control.TempState);
		snprintf(data,15,"%s",info.date);
		snprintf(hora,15,"%s",info.time);
		control.lastMinute = info.minute;
		control.lastBPM = control.BPM;
		NOKIAClear(display);
		
		NOKIAString(display,15,0,"PRINCIPAL");
		NOKIADrawHL(display,1,84);
		NOKIAString(display,0,2,Nokia_Temp);
		NOKIAString(display,50,2,Nokia_BPM);
		NOKIAString(display,0,3,data);
		NOKIAString(display,50,3,hora);
		NOKIAString(display,0,4,INFO1);
		NOKIAString(display,0,5,INFO2);
	}
	if(change_Layer == 0 && mWatching == 1 && (info.minute != control.lastMinute || control.BPM != control.lastBPM)){
		
		snprintf(Nokia_Temp,10,"%.1f*C",control.Temp);
		snprintf(Nokia_BPM,10,"%dBPM",control.BPM);
		snprintf(INFO1,15,"%s",control.BPMState);
		snprintf(INFO2,15,"%s",control.TempState);
		snprintf(data,15,"%s",info.date);
		snprintf(hora,15,"%s",info.time);
		NOKIAString(display,13,0,"PRINCIPAL");
		NOKIADrawHL(display,1,84);
		NOKIAString(display,0,2,Nokia_Temp);
		NOKIAString(display,50,2,Nokia_BPM);
		NOKIAString(display,0,3,data);
		NOKIAString(display,50,3,hora);
		NOKIAString(display,0,4,INFO1);
		NOKIAString(display,0,5,INFO2);
	}
}
void lcdDisplayProfile(LCD display, struct sGENERAL perfil){

	char	Nokia_Nome[25],Nokia_Genero[10],Nokia_Idade[10];

	if(change_Layer ==1 && control.pWatching == 0){	
		
		NOKIABitmap(display,profile);				delay_ms(1000);
		control.pWatching = 1;
		printf("2-)Tela de Perfil!\n");
		snprintf(Nokia_Nome,25,"Nome:%s",perfil.Name);
		snprintf(Nokia_Genero,10,"Genero:%s",perfil.Sex);
		snprintf(Nokia_Idade,10,"Idade:%d",perfil.Age); 
		NOKIAClear(display);
		NOKIAString(display,25,0,"PERFIL");
		NOKIADrawHL(display,1,84);
		NOKIAString(display,0,2,Nokia_Nome);
		NOKIAString(display,0,4,Nokia_Genero);
		NOKIAString(display,0,5,Nokia_Idade);
	}
}	 

void lcdDisplaySensors(LCD display, unsigned int fd,struct sGENERAL patient){
	char Nokia_Temp[10],Nokia_BPM[10],TempState[15],BPMState[15];
	control = getData(fd,patient);
	if(change_Layer == 2 && control.sWatching == 0){

		NOKIABitmap(display,sensors);				delay_ms(1000);
		control.sWatching = 1;
		control.lastBPM = control.BPM;
		printf("3-)Tela de Sensores!\n");
		snprintf(Nokia_Temp,10,"%.1f*C",control.Temp);
		snprintf(Nokia_BPM,10,"%dBPM",control.BPM);	
		snprintf(TempState,15,"%s",control.TempState);
		snprintf(BPMState,15,"%s",control.BPMState);
		NOKIAClear(display);
		NOKIAString(display,20,0,"SENSORES");
		NOKIADrawHL(display,1,84);
		NOKIAString(display,25,2,Nokia_Temp);
		NOKIAString(display,20,3,TempState);
		NOKIAString(display,25,4,Nokia_BPM);
		NOKIAString(display,20,5,BPMState);
	}

	if(change_Layer == 2 && control.sWatching == 1 && control.BPM != control.lastBPM){
		control.lastBPM = control.BPM;
		snprintf(Nokia_Temp,10,"%.1f*C",control.Temp);
		snprintf(Nokia_BPM,10,"%dBPM",control.BPM);	
		snprintf(TempState,15,"%s",control.TempState);
		snprintf(BPMState,15,"%s",control.BPMState);
		NOKIAString(display,20,0,"SENSORES");
		NOKIADrawHL(display,1,84);
		NOKIAString(display,25,2,Nokia_Temp);
		NOKIAString(display,20,3,control.TempState);
		NOKIAString(display,25,4,Nokia_BPM);
		NOKIAString(display,20,5,control.BPMState);
	}
}	

int main(void){
	LCD	nokia= NOKIAInit(CE,RST,DC,DIN,CLK);

	NOKIABitmap(nokia,RPi);	delay_ms(1000);

	struct sGENERAL person;

	system("clear");
	printf("Deseja Sobrescrever os Dados ? S/N\n");
	unsigned int choose;
	do{choose = getchar();}while(choose != 115 && choose != 83 && choose != 110 && choose != 78);
	getchar();
	if(choose == 115 || choose == 83){
		NOKIABitmap(nokia,profile);
		if(healthProfile(&person) == false){
			printf("Falha ao realizar o Cadastro!\n");
			return -1;
		}else{
			change_Layer = 2;
			lcdDisplayProfile(nokia, person);
			delay_ms(1000);
			change_Layer = 0;
		}
	}else{
		system("clear");
		NOKIABitmap(nokia,profile);
		if(importData(&person)==false){
			printf("Falha ao importar dados!\n");
			return -1;
		}else{
			change_Layer = 2;
			lcdDisplayProfile(nokia, person);
			delay_ms(1000);
			change_Layer = 0;					
		}
	}
	NOKIABitmap(nokia,sensors);
	int raspDuino = serialOpen(SERIAL_PORT[1],BAUDS[1]);
	if(raspDuino == -1){
		printf("Houve um erro ao Abrir a porta Serial!\n");
		return -1;
	}

	serialFlush(raspDuino);
	
	GPIOExport(changeDisplay);	GPIODirection(changeDisplay,INPUT);
	GPIOExport(backLight);		GPIODirection(backLight,INPUT);
	GPIOExport(BL);				GPIODirection(BL,OUTPUT);
	GPIOWrite(BL,HIGH);

	change_Layer = 0; 
	mWatching = 0;
	while(1){
		if(GPIORead(backLight) == HIGH){
			while(GPIORead(backLight) == HIGH){}
			GPIOWrite(BL,!GPIORead(BL));
		}
		lcdDisplayMain(nokia,raspDuino,person);
	}	
}
