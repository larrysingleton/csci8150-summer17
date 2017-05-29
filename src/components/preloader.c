#include <main.h>

int parseTestFile(FILE *file) {
    char *line = NULL;
    char *word = NULL;
    char *instrStr = NULL;
    int instrCounter = 1;
    size_t len = 0;
    int pc = 0;
    enum OP_CODE operation = NOOP;

    while (getline(&line, &len, file) != -1) {
        if(DEBUG) {
            printf("Whole line string: %s\n", line);
        }
        // skip comment lines
        if (line[0] == '#') {
            continue;
        }

        // Parse operation
        word = strtok(line, " ");
        if(DEBUG) {
            printf("Operation string: %s\n", word);
        }
        if (strcasecmp("READ", word) == 0) {
            operation = READ;
        } else if (strcasecmp("WRITE", word) == 0) {
            operation = WRITE;
        } else {
            return ERR; // Only support read and write operations
        }


        // get address
        word = strtok(NULL, " ");
        if(DEBUG) {
            printf("Address found: %s\n", word);
        }
        if (NULL != word) {
            int address = atoi(word);
            if(word == "0") { // atoi returns 0 if it can't parse the integer
                address = 0;
            } else if(address == 0) {
                return ERR; // atoi returns 0 if it can't parse the value.
            }
            // TODO: load the address into the register file.
            // TODO: record the location in the register file of the address into the instruction that will be loaded into the instruction cache.
        } else {
            return ERR;
        }

        if(operation == WRITE) {
            // WRITE will have a third part (value)
            word = strtok(NULL, " ");
            if(DEBUG) {
                printf("Data found: %s\n", word);
            }
            if (NULL != word) {
                // TODO: load the data into the register file.
                // TODO: record the location in the register file of the data into the instruction that will be loaded into the instruction cache.
            } else {
                return ERR;
            }
        }

        // TODO: build an instruction made up of the operation, and the location(s) in the register for the address and potentially the data.
        // TODO: call loadCache to load the instruction cache with the 8 byte instruction

        ++pc;
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

    // TODO - just a check to view the record
    instruction *instr = fetch(0);

    return OK;
}
