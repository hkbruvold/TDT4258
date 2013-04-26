/******************************************************************************
 *
 * Scroller
 *
 ******************************************************************************/

#include "scroller.h"

int main(void)
{
	init_fd();
	int t = 0;
	while (t<20)
	{
		printf("(every 6 sec)new loop! (%i) :::::::::::::::::::::::::\n", t);
		t++;
		time_loop();
	}
	close_fd();
}
	
void time_loop(void)
{
	int r = 0;
	int c = 0;
	while (r<240)
	{
		c = check_time();
		if (c > 0)
		{
			tick();
			r++;
		}
	}
	return;
}
void tick(void)
{
	move_stripes();
}
