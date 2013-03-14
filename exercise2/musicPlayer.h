/*****************************************************************************
 * 
 * Exercise 2 - music player
 *
 *****************************************************************************/

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <string.h>

#include "melodies.h"
#include "notes.h"
#include "ex1.h"

short getNextSample();
void playMelody(int melodyNumber);

#endif
