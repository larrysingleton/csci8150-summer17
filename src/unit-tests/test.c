#include <tests.h>

int main() {
    // If you don't get any output then it was successful.
//    if(!test_insructionCache_oneValue()) {
//        printf("Failed to validate instruction cache oneValue test\n");
//    }
//    if(!test_insructionCache_multiValue()) {
//        printf("Failed to validate instruction cache multiValue test\n");
//    }
//    if(!test_registerFile() == -1) {
//        printf("Failed to validate register file test\n");
//    }

    int programCounter = 1;
    int cacheMask = 0b100 << 13; // Mask this to the top order bits.
    int rowMask = programCounter / 8 << 7; // Mask this to bits 4-9 for column
    int instructionMask = programCounter % 8 <<  3; // Mask bits for cell
    int instructionCacheAddress = cacheMask | rowMask | instructionMask;
    printf("%06x\n", cacheMask);
    printf("%06x\n", rowMask);
    printf("%06x\n", instructionMask);
    printf("%06x\n", instructionCacheAddress);
}