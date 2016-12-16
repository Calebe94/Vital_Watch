
/*scp ~/Projetos/Programacao_em_C/TODO/VeiWatch/teste.c pi@192.168.0.17:~/Programacao_em_C/TODO/VeiWatch/*/
#include"RaspberryGPIO.h"
#include<stdint.h>
#include"HeartBeat.h"
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
/*
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
*/
int main(void){

	struct sGENERAL person;

	system("clear");
	printf("Deseja Sobrescrever os Dados ? S/N\n");
	unsigned int choose;
	do{choose = getchar();}while(choose != 115 && choose != 83 && choose != 110 && choose != 78);
	getchar();
	if(choose == 115 || choose == 83){
		if(healthProfile(&person) == false){
			printf("Falha ao realizar o Cadastro!\n");
			return -1;
		}
	}else{
		system("clear");
		if(importData(&person)==false){
			printf("Falha ao importar dados!\n");
			return -1;
		}
	}
	GPIOExport(changeDisplay);	GPIODirection(changeDisplay,INPUT);
	GPIOExport(backLight);		GPIODirection(backLight,INPUT);
	GPIOExport(BL);				GPIODirection(BL,OUTPUT);
	GPIOWrite(BL,HIGH);

	while(1){
		if(GPIORead(backLight) == HIGH){
			while(GPIORead(backLight) == HIGH){}
			GPIOWrite(BL,!GPIORead(BL));
		}
	}	
}
