/******************************************************************************
 *
 * Logic
 *
 ******************************************************************************/

#include "logic.h"

// car size = ______________[car_pos]-----(60 pixels)-----[car_pos+60]________

int car_pos = 190;

void move_car(int direction)
{
	if (direction > 0)	//move right
	{
		paint_column(car_pos);
		car_pos++;
