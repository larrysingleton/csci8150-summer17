#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

#define blockSizeInBytes 64


char* fetch(int programCounter);
void loadCache(int programCounter, char instruction[8]);


// Register File
int loadRegister(const unsigned char* value);
char* fetchRegister(int registerLocation);

// Memory
void loadMemoryBlock(long address, char* data);
char* fetchMemoryBlock(long address);

#endif //CSCI8150_DATA_STRUCTURES_H_H