#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

#define blockSizeInBytes 64


char* fetch(int programCounter);
void loadCache(int programCounter, char instruction[8]);


// Register File
int loadRegister(const unsigned char* value);
char* fetchRegister(int registerLocation);

// Memory
char fetchMemoryByte(int address);
void loadMemoryByte(int address, char data);
void loadMemoryBlock(int address, char* data);
char* fetchMemoryBlock(int address);

#endif //CSCI8150_DATA_STRUCTURES_H_H