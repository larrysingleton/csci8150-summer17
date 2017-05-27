#include "main.h"

instruction* instructionCache[INS_CACHE_ROWS][INS_CACHE_CELLS];

/* Macro used to decode the cache row from a program counter */
#define row(programCounter)  (programCounter / INS_CACHE_CELLS)
/* Macro used to decode the cache row cell from a program counter */
#define cell(programCounter)  (programCounter % INS_CACHE_CELLS)

instruction* fetch(int programCounter) {
    return instructionCache[row(programCounter)][cell(programCounter)];
}

void loadCache(int programCounter, instruction* instructionPointer) {
    instructionCache[row(programCounter)][cell(programCounter)] = instructionPointer;
}