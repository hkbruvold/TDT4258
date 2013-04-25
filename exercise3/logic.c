/******************************************************************************
 *
 * Logic
 *
 ******************************************************************************/

#include "logic.h"

// car size = 	______________[car_pos]-----(60 pixels)-----[car_pos+60]________
//		car is 60 pixels out.

int driver_pos = 190;

void move_driver(int direction)
{
	
	if (direction > 0 && driver_pos>1)		//move right
		driver_pos++;

	else if (direction < 0 && driver_pos<319)	//move left
		driver_pos = driver_pos - 1;
	
	paint_car_column(driver_pos);
	paint_driver(driver_pos);
}

