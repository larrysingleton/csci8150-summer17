#include <tests.h>

int test_insructionCache_oneValue() {
    double i = 0b1111111111111111111111111111111111111111111111111111111111111111;
    loadInstructionCache(1, i);
    double j = fetchInstruction(1);
    return i == j;
}

int test_insructionCache_multiValue() {
    double i = 0b1111111111111111111111111111111111111111111111111111111111111111;
    double j = 0b0111111111111111111111111111111111111111111111111111111111111111;
    loadInstructionCache(0, i);
    loadInstructionCache(1, j);
    return fetchInstruction(0) != fetchInstruction(1);
}