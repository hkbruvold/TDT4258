/******************************************************************************
 *
 * Sound player header file
 *
 ******************************************************************************/

#ifndef PLAYSOUND_H
#define PLAYSOUND_H

#include <stdio.h>
#include <math.h>
#include <linux/soundcard.h>
#include <fcntl.h> 

int playSound(char *filename);

#endif
