/*****************************************************************************
 * 
 * Exercise 2 - notes
 *
 *****************************************************************************/

#include "notes.h"


short getNoteData(char note, int octave, long pos) {
  int indexFactor = pow(2, 4 - octave);
  long realPos = pos * indexFactor;
  short *noteArray;

  switch (note) {
    case 'c':
      noteArray = C4;
      break;
    case 'C':
      noteArray = Cs4;
      break;
    case 'd':
      noteArray = D4;
      break;
    case 'D':
      noteArray = Ds4;
      break;
    case 'e':
      noteArray = E4;
      break;
    case 'f':
      noteArray = F4;
      break;
    case 'F':
      noteArray = Fs4;
      break;
    case 'g':
      noteArray = G4;
      break;
    case 'G':
      noteArray = Gs4;
      break;
    case 'a':
      noteArray = A4;
      break;
    case 'A':
      noteArray = As4;
      break;
    case 'b':
      noteArray = B4;
      break;
  }
  
  return noteArray[realPos % (sizeof(noteArray) / sizeof(noteArray))];
}
