#include <tests.h>

int main() {
    if(!test_insructionCache_oneValue()) {
        printf("Failed to validate instruction cache oneValue test");
    }
    if(!test_insructionCache_multiValue()) {
        printf("Failed to validate instruction cache multiValue test");
    }
    if(!test_registerFile()) {
        printf("Failed to validate register file test");
    }
}