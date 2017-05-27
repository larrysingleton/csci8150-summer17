#include "main.h"

int parseTestFile(FILE *file) {
    // TODO - parse file into instruction cache
    return OK;
}

int preLoadInstructionCache(char *testFile) {
    FILE *file;

    printf("\nLoading instruction cache from: %s", testFile);

    if (file = fopen(testFile, "r")) {
        parseTestFile(file);
        fclose(file);
    } else {
        printf("\nUnable to read test file: %s", testFile);
        return ERR;
    }

    return OK;
}
