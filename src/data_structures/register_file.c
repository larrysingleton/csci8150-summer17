#include <main.h>

unsigned char registerFile[2^REGISER_ADDRESS_SIZE][512]; // 1024 rows of 512 bits = 64 KB register

int nextFreeRegister = 0;

int loadRegister(unsigned char* value) {
    int valueSize = sizeof(value);
    if(valueSize <= 512) {
        for(int i = 0; i < valueSize; i++) {
            registerFile[nextFreeRegister][i] = value[i];
        }
        return nextFreeRegister++;
    } else {
        return ERR;
    }
}