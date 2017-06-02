#include <tests.h>

int compareInstructions(char instruction1[], char instruction2[]);

int test_insructionCache_oneValue() {
    char i[] = {1, 0, 0, 1, 0, 0, 0, 0};
    loadCache(0, i);
    return compareInstructions(fetch(0), i) != -1;
}

int test_insructionCache_multiValue() {
    char i[] = {1, 0, 0, 1, 0, 0, 0, 0};
    int* j = 0b00010001;
    loadCache(0, i);
    loadCache(1, j);
    return compareInstructions(fetch(0), fetch(1)) == -1;
}

int compareInstructions(char instruction1[], char instruction2[]) {
    for(int i = 0; i < 8; i++) {
        if(instruction1[i] != instruction2[i]) {
            return ERR;
        }
    }
    return OK;
}