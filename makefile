all: main.c RaspberryGPIO.c wiringSerial.c PCD8544.c HeartBeat.c VeiWatch.c
	gcc -std=c99 main.c RaspberryGPIO.c wiringSerial.c PCD8544.c HeartBeat.c VeiWatch.c -o exec
teste:	teste.c RaspberryGPIO.c HeartBeat.c VeiWatch.c RPiNOKIA.c wiringSerial.c
	gcc -std=c99 teste.c RaspberryGPIO.c HeartBeat.c VeiWatch.c wiringSerial.c RPiNOKIA.c -o teste
rm: 
	rm exec || rm teste
