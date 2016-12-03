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
#ifndef __RASPBERRYGPIO_H__
#define __RASPBERRYGPIO_H__
#endif

#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#define ENTRADA 1
#define SAIDA 	0
#define INPUT 1
#define OUTPUT 	0
#define HIGH 	1
#define LOW 	0
#define ALTO 	1
#define BAIXO	0
/*Protótipos das Funções*/
bool GPIOExport(unsigned int pino);
bool GPIODirection(unsigned int pino,unsigned  int direcao);
bool GPIOWrite(unsigned int pino,unsigned int valor);
bool GPIORead(unsigned int pino);
bool GPIOUnexport(unsigned int pino);
bool GPIOSetup(unsigned int pino,unsigned int direcao);
void delay_ms(unsigned int tempo);
void delay_s(unsigned int tempo);
void delay_us(unsigned int tempo);
