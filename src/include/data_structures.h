#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

#define blockSizeInBytes 64


double fetchInstruction(int programCounter);
void loadInstructionCache(int programCounter, double instruction);

// Register File
int loadRegister(char* value);
char* fetchRegister(int registerLocation);

// Memory
void loadMemoryBlock(long address, char* data);
char* fetchMemoryBlock(long address);

#endif //CSCI8150_DATA_STRUCTURES_H_H