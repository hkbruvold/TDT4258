/*****************************************************************************
 * 
 * Exercise 2 - notes
 *
 *****************************************************************************/

#include "notes.h"


short getNoteData(char note, int octave, long pos) {
  double indexFactor = pow(2, octave - 3);
  long realPos = pos * indexFactor;
  short *noteArray;
  int sinLen;
  
  switch (note) {
    case 'c':
      noteArray = C4;
      sinLen = 184;
      break;
    case 'C':
      noteArray = Cs4;
      sinLen = 174;
      break;
    case 'd':
      noteArray = D4;
      sinLen = 164;
      break;
    case 'D':
      noteArray = Ds4;
      sinLen = 155;
      break;
    case 'e':
      noteArray = E4;
      sinLen = 146;
      break;
    case 'f':
      noteArray = F4;
      sinLen = 138;
      break;
    case 'F':
      noteArray = Fs4;
      sinLen = 130;
      break;
    case 'g':
      noteArray = G4;
      sinLen = 123;
      break;
    case 'G':
      noteArray = Gs4;
      sinLen = 116;
      break;
    case 'a':
      noteArray = A4;
      sinLen = 110;
      break;
    case 'A':
      noteArray = As4;
      sinLen = 103;
      break;
    case 'h':
      noteArray = B4;
      sinLen = 98;
      break;
    case 'p':
      noteArray = pause;
      sinLen = 16;
      break;
    default:
      noteArray = A4;
      sinLen = 110;
      break;
      }
  
  return noteArray[realPos % sinLen];
}
