#include <main.h>

char* registerFile[1024]; // 1024 rows of 8 bytes = 64 KB register

int nextFreeRegister = 0;

int loadRegister(char* value) {
    registerFile[nextFreeRegister] = value;
    return nextFreeRegister++;
}

char* fetchRegister(int registerLocation) {
    for(int i = 0; i < 4; i ++) {
        if (DEBUG) printf("Register location %d: %s\n", i, registerFile[i]);
    }
    return registerFile[registerLocation];
}
