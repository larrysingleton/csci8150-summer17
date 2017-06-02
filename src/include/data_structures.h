#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

char* fetch(int programCounter);
void loadCache(int programCounter, char instruction[8]);


// Register File
int loadRegister(const unsigned char* value);
char* fetchRegister(int registerLocation);

#endif //CSCI8150_DATA_STRUCTURES_H_H