#include <tests.h>

int compareInstructions(char instruction1[], char instruction2[]);

int test_insructionCache_oneValue() {
    char i[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    loadCache(1, i);
    char* j = fetch(1);
    return compareInstructions(j, i) != -1;
}

int test_insructionCache_multiValue() {
    char i[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    char j[] = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
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