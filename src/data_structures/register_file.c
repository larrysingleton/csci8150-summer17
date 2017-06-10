#include <main.h>

char * registerFile[2^10]; // 1024 rows of 8 bytes = 64 KB register

int nextFreeRegister = 0;

int loadRegister(char* value) {
    registerFile[nextFreeRegister] = value;
    return nextFreeRegister++;
}

char* fetchRegister(int registerLocation) {
    return registerFile[registerLocation];
}
