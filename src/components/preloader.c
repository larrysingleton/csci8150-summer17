#include "main.h"

int parseTestFile(FILE *file) {
    char *line=NULL;
    size_t len=0;
    int pc = 0;

    while (getline(&line, &len, file) != -1) {
        if (line[0] != '#') {
            printf("\nRead line: %s", line);
            // TODO: load value into instruction cache
        }
    }
    return OK;
}

int preLoadInstructionCache(const char *testFile) {
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
