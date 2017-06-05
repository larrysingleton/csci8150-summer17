#include <tests.h>

int main() {
    // If you don't get any output then it was successful.
    if(!test_insructionCache_oneValue()) {
        printf("Failed to validate instruction cache oneValue test\n");
    }
    if(!test_insructionCache_multiValue()) {
        printf("Failed to validate instruction cache multiValue test\n");
    }
    if(!test_registerFile() == -1) {
        printf("Failed to validate register file test\n");
    }
}