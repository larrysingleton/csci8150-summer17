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
double instructionCacheData[64][8];

double fetchInstruction(int programCounter) {
    int controllerData = instructionCacheController[programCounter];
    if((controllerData >> 15) == 0) {
        return ERR; // Cache miss
    }
    int rowMask = 0b0001111110000000;
    int row = controllerData & rowMask;
    int cellMask = 0b0000000001111000;
    int cell = (controllerData & cellMask) >> 3;
    return instructionCacheData[row][cell];
}

void loadInstructionCache(int programCounter, double instruction) {
    int cacheMask = 0b100 << 13; // Mask this to the top order bits.
    int rowMask = programCounter / 8 << 7; // Mask this to bits 4-9 for column
    int instructionMask = programCounter % 8 << 3; // Mask bits for cell
    int instructionCacheAddress = cacheMask | rowMask | instructionMask;
    instructionCacheController[programCounter] = instructionCacheAddress;
    instructionCacheData[programCounter / 8][programCounter % 8] = instruction;
}