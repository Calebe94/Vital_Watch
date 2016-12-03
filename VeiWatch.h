#ifndef __VEIWATCH_H__
#define __VEIWATCH_H__
#endif
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <termios.h>

int kbhit(void);
int getch(void);
int getnum(void);

typedef struct{
	uint8_t BPM;
	uint8_t lastMinute,lastBPM;	//Armazena os últimos estados
	uint8_t mViewed,pViewed,sViewed; // Armazena estado da Tela: Se está vista[1], se não [0]
	uint8_t mWatching,pWatching,sWatching;
	float Temp;
	char *BPMState,*TempState;
}Vei_Data;

char *isNormal(float Temp);

