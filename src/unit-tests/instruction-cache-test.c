#include <main.h>

int test_insructionCache_oneValue();
int test_insructionCache_multiValue();
int compareInstructions(instruction, instruction);

int main() {
    if(!test_insructionCache_oneValue()) {
        printf("Failed to validate instruction cache oneValue test");
    }
    if(!test_insructionCache_multiValue()) {
        printf("Failed to validate instruction cache multiValue test");
    }
}

int test_insructionCache_oneValue() {
    unsigned char i[] = {1, 0, 0, 1, 0, 0, 0, 0};
    loadCache(0, (instruction*) &i);
    return compareInstruction(*fetch(0), i);
}

int test_insructionCache_multiValue() {
    unsigned char i[] = {1, 0, 0, 1, 0, 0, 0, 0};
    unsigned char j[] = {0, 0, 0, 1, 0, 0, 0, 1};
    loadCache(0, (instruction*) &i);
    loadCache(1, (instruction*) &j);
    return !compareInstruction(*fetch(0), *fetch(1));
}

int compareInstruction(instruction instruction1, instruction instruction2) {
    for(int i = 0; i < 8; i++) {
        if(instruction1[i] != instruction2[i]) {
            return 0;
        }
    }
    return 1;
}

