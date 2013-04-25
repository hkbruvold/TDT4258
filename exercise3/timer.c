/******************************************************************************
 *
 * Timer
 *
 ******************************************************************************/
 
#include "timer.h"


struct timeval tim;
double newms, newsec;
double prevms = 0;
double prevsec = 0;

int check_time(void)
{
 	gettimeofday(&tim, NULL);
 	newsec = tim.tv_sec;
 	newms = tim.tv_usec / 1000;
 	if (newsec > prevsec)
 	{
 		prevsec = newsec;
 		prevms = 0;
 		return 1;
 	}
 	else if (newms > prevms + 25)
 	{
 		prevms = newms;
 		return 1;
 	}
 	else
 		return 0;
}
