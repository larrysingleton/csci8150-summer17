#include <main.h>

// Instruction 8 bytes
// Bit  opcode
// Bits 54-63 data/byte enable register address
// Bits 44-53 cpu address address
// bits 42-43 op code

int parseTestFile(FILE *file) {
    char *line = NULL;
    char *word = NULL;
    enum OP_CODE op = NOOP;

    size_t len = 0;
    int pc = 0;
    char operation[2];

    while (getline(&line, &len, file) != -1) {
        char* address;
        char* data;
        // skip comment lines
        if (line[0] == '#') {
            continue;
        }

        // trim off the trailing new lines
        line[strcspn(line, "\n\r")] = 0;
        if(DEBUG) printf("\nWhole line string: [%s]\n", line);

        // Parse operation
        word = strtok(line, " ");
        if(DEBUG) printf("Operation string: [%s]\n", word);

        if (strcasecmp("READ", word) == 0) {
            op = READ;
        } else if (strcasecmp("WRITE", word) == 0) {
            op = WRITE;
        } else {
            return ERR; // Only support read and write operations
        }

        // get address
        word = strtok(NULL, " ");
        if (NULL != word) {
            if (DEBUG) printf("Address found: [%s]\n", word);
            address = word;
        } else {
            return ERR;
        }

        // Get either data or byte enable
        word = strtok(NULL, " ");
        if(DEBUG) printf("Data found: [%s]\n", word);

        if (NULL != word) {
            data = word;
        } else {
            return ERR;
        }

        // Load data into register
        int addressRegister = loadRegister(address);
        int dataRegister = loadRegister(data);
        // load the instruction line into the cache
        int64_t instruction = op << 20 | (addressRegister << 10) | dataRegister;
        if(DEBUG) printf("Instruction data %ld\n", instruction);
        loadInstructionCache(pc, instruction);
        if(DEBUG) printf("Instruction loaded into register %ld\n", fetchInstruction(pc));
        pc++;
    }
    return OK;
}

int preLoadInstructionCache(const char *testFile) {
    FILE *file;

    if(DEBUG) printf("\n==================================================");
    if(DEBUG) printf("\nLoading instruction cache from: [%s]", testFile);
    if (file = fopen(testFile, "r")) {
        parseTestFile(file);
        fclose(file);
    } else {
        if(DEBUG) printf("\nUnable to read test file: %s", testFile);
        return ERR;
    }

    if(DEBUG) printf("\n==================================================\n\n");

    return OK;
}