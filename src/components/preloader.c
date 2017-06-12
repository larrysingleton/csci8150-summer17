#include <main.h>

// Instruction 8 bytes
// Bit  opcode
// Bits 54-63 data/byte enable register address
// Bits 44-53 cpu address address
// bits 42-43 op code

char *strtok_r (char *s, const char *delim, char **save_ptr);
char* array[100];

int parseTestFile(FILE *file) {
    char *word = NULL;
    enum OP_CODE op = NOOP;

    size_t len = 0;
    int pc = 0;

    while (getline(&array[pc], &len, file) != -1) {
        // skip comment lines
        if (array[pc][0] == '#') {
            continue;
        }

        // trim off the trailing new lines
        array[pc][strcspn(array[pc], "\n\r")] = 0;
        if(DEBUG) printf("\nWhole line string: [%s]\n", array[pc]);

        // Parse operation
        word = strtok(array[pc], " ");
        if(DEBUG) printf("Operation string: [%s]\n", word);

        if (strcasecmp("READ", word) == 0) {
            op = READ;
        } else if (strcasecmp("WRITE", word) == 0) {
            op = WRITE;
        } else {
            return ERR; // Only support read and write operations
        }


        // get address
        int addressRegister = loadRegister(strtok(NULL, " "));

        // Get either data or byte enable
        int dataRegister = loadRegister(strtok(NULL, " "));

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

char *strtok_r (char *s, const char *delim, char **save_ptr) {
    char *token;

    if (s == NULL)
        s = *save_ptr;

    /* Scan leading delimiters.  */
    s += strspn (s, delim);
    if (*s == '\0')
    {
        *save_ptr = s;
        return NULL;
    }

    /* Find the end of the token.  */
    token = s;
    s = strpbrk (token, delim);
    if (s == NULL)
        /* This token finishes the string.  */
        *save_ptr = memchr(token, '\0', 64);
    else
    {
        /* Terminate the token and make *SAVE_PTR point past it.  */
        *s = '\0';
        *save_ptr = s + 1;
    }
    return token;
}


