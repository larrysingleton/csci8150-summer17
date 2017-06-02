#include "main.h"

// Instruction Cache, 64 rows to line up for each row in the instructionDataCache
int instructionCacheController[64];
// Each row in the controller is 16 bits,
// Bit 1: valid
// Bit 2: dirty
// Bit 3: least recently used
// Bit 4-9: address of row
// Bit 10-13: address of instruction in row.
// So 64 rows of 64 bytes (each row of 64 bytes is broken into 8 sections of 8 bytes each
char* instructionCacheData[64][8]; // TODO: update this with the correct size cache.

//TODO: I think we are getting close here, I am just not sure how to store the data part now.

char * fetch(int programCounter) {
    int address = instructionCacheController[programCounter];
    return instructionCacheData[address][1];
}

void loadCache(int programCounter, char* instruction) {
    int cacheMask = 0b100 << 13; // Mask this to the top order bits.
    int rowMask = programCounter / 8 << 7; // Mask this to bits 4-9 for column
    int instructionMask = programCounter % 8 <<  3; // Mask bits for cell
    int instructionCacheAddress = cacheMask | rowMask | instructionMask;
    instructionCacheController[programCounter] = instructionCacheAddress;
    instructionCacheData[programCounter / 8][instructionCacheAddress % 8] = instruction; // TODO: this isnt correct.
}