#! /usr/bin/env python

import math
import sys

args = sys.argv

notes = ["C4", "Cs4", "D4", "Ds4", "E4", "F4", "Fs4", "G4", "Gs4", "A4", "As4", "B4"]
frequencies = [261.626, 277.183, 293.665, 311.127, 329.628, 349.288, 369.994, 391.995, 415.305, 440.0, 466.164, 493.883]

helptext = "Usage: sinTableGenerator.py sample_rate max_amplitude"


try:
    if args[1] in ["--help", "-h", "-help"]:
        print(helptext)
    sampleRate = float(args[1])
    maxAmplitude = int(args[2])
except IndexError:
    print(helptext)
    sys.exit()

def generate(frequency, sampleRate, maxAmplitude):
    table = []
    deltaX = 2 * math.pi / (sampleRate/frequency)
    x = 0

    while x < 2 * math.pi:
        table.append(math.sin(x) * maxAmplitude)
        x += deltaX
    
    return table

def printTable(table):
    sys.stdout.write("[")
    for a in table:
        sys.stdout.write(", " + str(int(a)))
    sys.stdout.write("]")

for i in range(len(notes)):
    sys.stdout.write(notes[i] + " = ")
    sys.stdout.write(str(map(int, generate(frequencies[i], sampleRate, maxAmplitude))))
    sys.stdout.write("\n")

