#include <tests.h>

int compareInstructions(instruction instruction1, instruction instruction2);

int test_insructionCache_oneValue() {
    unsigned char i[] = {1, 0, 0, 1, 0, 0, 0, 0};
    loadCache(0, (instruction*) &i);
    return compareInstructions(*fetch(0), i) != -1;
}

int test_insructionCache_multiValue() {
    unsigned char i[] = {1, 0, 0, 1, 0, 0, 0, 0};
    unsigned char j[] = {0, 0, 0, 1, 0, 0, 0, 1};
    loadCache(0, (instruction*) &i);
    loadCache(1, (instruction*) &j);
    return compareInstructions(*fetch(0), *fetch(1)) == -1;
}

int compareInstructions(instruction instruction1, instruction instruction2) {
    for(int i = 0; i < 8; i++) {
        if(instruction1[i] != instruction2[i]) {
            return ERR;
        }
    }
    return OK;
}