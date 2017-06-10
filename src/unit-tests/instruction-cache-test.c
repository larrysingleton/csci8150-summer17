#include <tests.h>

int compareInstructions(char instruction1[], char instruction2[]);

int test_insructionCache_oneValue() {
    char i[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    loadInstructionCache(1, i);
    char* j = fetchInstruction(1);
    return compareInstructions(j, i) != -1;
}

int test_insructionCache_multiValue() {
    char i[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    char j[] = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    loadInstructionCache(0, i);
    loadInstructionCache(1, j);
    return compareInstructions(fetchInstruction(0), fetchInstruction(1)) == -1;
}

int compareInstructions(char instruction1[], char instruction2[]) {
    for(int i = 0; i < 8; i++) {
        if(instruction1[i] != instruction2[i]) {
            return ERR;
        }
    }
    return OK;
}