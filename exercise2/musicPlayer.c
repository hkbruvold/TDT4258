/*****************************************************************************
 * 
 * Exercise 2 - main file
 *
 *****************************************************************************/

#include "musicPlayer.h"
#include "melodies.h"
#include "notes.h"
#include "ex2.c"
#include <string.h>

int melPos;
long notePos;
long samplesLeft;
char *currentMelody;
int curBPM;
char curNote;
int curOctave;
int silence;


short getNextSample(void) {
  if (silence) {
    return (short) 0;
  }
  if (samplesLeft == 0) {
    melPos++;
    curNote = currentMelody[melPol];
    melPos++;
    curOctave = currentMelody[melPos];
    melPos++;
    samplesLeft = 48000 * ((double) curBPM / 60) / (int) currentMelody[melPos];

    if (melPos >= sizeof(currentMelody) / sizeof(currentMelody[0]) - 1) {
      silence = 1;
      clearLEDs();
      return (short) 0;
    }
  }
  notePos++;
  samplesLeft--;
  return getNoteData(curNote, curOctave, notePos);
}

void playMelody(int melodyNumber) {
  silence = 0;

  switch (melodyNumber) {
    case 0:
      currentMelody = GreenSleves;
      curBPM = GreenSlevesBPM;
      break;
    case 1:
      currentMelody = RickRoll;
      curBPM = RickRollBPM;
      break;
    case 2:
      currentMelody = IsThereAnybodyOutThere;
      curBPM = IsThereanybodyOutThereBPM;
      break;
    case 3:
      currentMelody = BluesLeft;
      curBPM = BluesLeftBPM;
      break;
    case 4:
      currentMelody = BluesRight;
      curBPM = BluesRightBPM;
      break;
    case 5:
      currentMelody = dunDunDUNNN1;
      curBPM = dunDunDUNNN1BPM;
      break;
    case 6:
      currentMelody = dunDunDUNNN2;
      curBPM = dunDunDUNNN2BPM;
      break;
    case 7:
      currentMelody = mario;
      curBPM = marioBPM;
      break;
    default:
      silence = 1;
      break;
  }
  melPos = 0;
  notePos = 0;
  samplesLeft = 0;
}

