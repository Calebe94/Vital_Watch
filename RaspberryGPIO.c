/*
				ASCII Art Raspberry Pi 2 B2 GPIO
			              	  PINOS
					   +3V3 [01] [02] +5V
			 SDA1 / GPIO  2 [03] [04] +5V
			 SCL1 / GPIO  3 [05] [06] GND
   				    GPIO  4 [07] [08] GPIO 14 / TXD0
   			            GND [09] [10] GPIO 15 / RXD0
   				    GPIO 17 [11] [12] GPIO 18
					GPIO 27 [13] [14] GND
					GPIO 22 [15] [16] GPIO 23
					   +3V3 [17] [18] GPIO 24
		     MOSI / GPIO 10 [19] [20] GND
		     MISO / GPIO  9 [21] [22] GPIO 25
 			 SCLK / GPIO 11 [23] [24] GPIO  8 / CE0#
					    GND [25] [26] GPIO  7 / CE1#
			ID_SD / GPIO  0 [27] [28] GPIO  1 / ID_SC
					GPIO  5 [29] [30] GND
					GPIO  6 [31] [32] GPIO 12
					GPIO 13 [33] [34] GND
	 		 MISO / GPIO 19 [35] [36] GPIO 16 / CE2#
					GPIO 26 [37] [38] GPIO 20 / MOSI
		    			GND [39] [40] GPIO 21 / SCLK
*/
#include"RaspberryGPIO.h"
void delay_us(unsigned int tempo){
	for(int cont=0;cont<tempo;cont++)	usleep(1);
}
void delay_ms(unsigned int tempo){
	for(int cont=0;cont<tempo;cont++)	usleep(1000);
}
void delay_s(unsigned int tempo){
	for(int cont=0;cont<tempo;cont++)	usleep(1000000);
}
bool GPIOExport(unsigned int pino){
	char buffer[3];
	int arquivo;
	arquivo = open("/sys/class/gpio/export",O_WRONLY);
	if( arquivo == -1)	return false;
	snprintf( buffer, 3 , "%d", pino);
	if( write(arquivo,buffer,3) == -1 ){
		close(arquivo);
		return false;
	}
	close(arquivo);
	return true;
}
bool GPIOUnexport(unsigned int pino){
	char buffer[3];
	int arquivo;
	arquivo = open("/sys/class/gpio/unexport",O_WRONLY);
	if( arquivo == -1)	return false;
	snprintf( buffer, 3 , "%d", pino);
	if( write(arquivo,buffer,3) == -1 ){
		close(arquivo);
		return false;
	}
	close(arquivo);
	return true;
}
bool GPIODirection(unsigned int pino,unsigned int direcao){
	char caminho[35];
	int arquivo;
	snprintf(caminho,35,"/sys/class/gpio/gpio%d/direction",pino);
	arquivo = open( caminho, O_WRONLY);
	if(arquivo == -1)	return false;
	if( write(arquivo,(direcao == 1)?"in":"out",(direcao== 1)?2:3) == -1 ){
		close(arquivo);
		return false;
	}
	close(arquivo);
	return true;
}
bool GPIOWrite(unsigned int pino,unsigned int valor){
	char caminho[35];
	int arquivo;
	snprintf(caminho,35,"/sys/class/gpio/gpio%d/value",pino);
	arquivo = open(caminho,O_WRONLY);
	if(arquivo == -1)	return false;
	if( write(arquivo,valor == 1?"1":"0",1) == -1 ){
		close(arquivo);
		return false;
	}
	close(arquivo);
	return true;
}
bool GPIORead(unsigned int pino){
	char caminho[35];
	int arquivo;
	char retorno[2];
	snprintf(caminho,35,"/sys/class/gpio/gpio%d/value",pino);
	arquivo = open(caminho,O_RDONLY);
	if(arquivo == -1) return false;
	if( read(arquivo,retorno,2) == -1){
		close(arquivo);
		return false;
	}
	close(arquivo);
	return (int)retorno[0]-48;
	//return retorno[0]-'0';
}
bool GPIOSetup(unsigned int pino,unsigned int direcao){
	if(GPIOExport(pino) == false)	return false;
	else{
		if(GPIODirection(pino,direcao)== false)	return false;
		else 	return true;
	}
}
