/*****************************************************************************
 * 
 * Exercise 2 - music player
 *
 *****************************************************************************/

#include "musicPlayer.h"

int melPos;
long notePos = 0;
long samplesLeft;
char *currentMelody;
int curBPM;
char curNote;
int curOctave;
int silence = 1;
int newNote = 0;


short getNextSample(void) {
  if (silence) {
    clearLEDs();
    return (short) 0;
  }
  if (samplesLeft == 0) {
    if (newNote) {
      newNote = 0;
      samplesLeft = 100;
      curNote = 'p';
      curOctave = 4;
    } else {
      newNote = 1;
      melPos++;
      curNote = (char) currentMelody[melPos];
      melPos++;
      curOctave = (int) (currentMelody[melPos] - '0');
      melPos++;
      samplesLeft = (int) (48000 / (curBPM / 60.0)) / (int) (currentMelody[melPos] - '0');
      if (curNote == 'p') {
        samplesLeft = 2000;
      }
    }
    
    if (currentMelody[melPos + 1] == 'q') {
      silence = 1;
    }
  }
  notePos++;
  samplesLeft--;
  return getNoteData(curNote, 4, notePos);
}

void playMelody(int melodyNumber) {
  silence = 0;
  clearLEDs();

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
      curBPM = IsThereAnybodyOutThereBPM;
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
  melPos = -1;
  notePos = 0;
  samplesLeft = 0;
}

