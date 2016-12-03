#include <stdio.h>
#include <time.h>
#include <string.h>
struct sClock{
	char time[10],date[10];
	unsigned int day,month,hour,minute;
}info;

void getClockInformation(struct sClock *times){

	unsigned int iDay,iMonth,iHour,iMinute;
	char data[10],day[5],month[5],timetable[10],hour[5],minute[5];
	
	struct tm *local;
	time_t t;
	t = time(NULL);

	local = localtime(&t);
	
	iDay = local->tm_mday;
	iMonth = local -> tm_mon + 1;

	iHour	=	local -> tm_hour;
	iMinute	= 	local -> tm_min;

	times -> day = iDay;
	times -> month = iMonth;
	times -> hour = iHour;
	times -> minute = iMinute;

	if(iDay < 10){
		snprintf(day,5,"0%d",iDay);
	}else{
		snprintf(day,5,"%d",iDay);
	}
	if(iMonth < 10){
		snprintf(month,5,"0%d",iMonth);	
	}else{
		snprintf(month,5,"%d",iMonth);	
	}

	if(iHour < 10){
		snprintf(hour,5,"0%d",iHour);
	}else{
		snprintf(hour,5,"%d",iHour);
	}
	if(iMinute < 10){
		snprintf(minute,5,"0%d",iMinute);	
	}else{
		snprintf(minute,5,"%d",iMinute);	
	}

	sprintf(data,"%s/%s",day,month);
	sprintf(timetable,"%s:%s",hour,minute);

	strcpy(times->time,timetable);
	strcpy(times->date,data);
}
