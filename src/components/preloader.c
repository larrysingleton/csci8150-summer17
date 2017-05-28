#include "main.h"

char *parseTokenField(const char *str, int num, char *tokens) {
    char entry[80];
    char *tok;
    strcpy(entry, str);
    for (tok = strtok(entry, tokens); tok && *tok; tok = strtok(NULL, "\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

int parseTestFile(FILE *file) {
    char *line = NULL;
    char *word = NULL;
    char *instrStr = NULL;
    int instrCounter = 1;
    size_t len = 0;
    int pc = 0;
    instruction instr = NOOP;

    while (getline(&line, &len, file) != -1) {

        fprintf(stdout, "\nparseTestFile: %s", line);

        // skip comment lines
        if (line[0] == '#') {
            continue;
        }

        for (instrCounter = 1; instrCounter <= 8; instrCounter++) {
            instrStr = parseTokenField(line, instrCounter, ";");

            // check if done processing instructions
            if (NULL == instrStr) {
                break;
            }

            // zero out instr struct
            memset(instr, 0, sizeof(unsigned char) * INS_SIZE_IN_BYTES);

            word = parseTokenField(instrStr, 1, " ");
            if (strcasecmp("READ", word) == 0) {
                strcpy((char *) instr, READ);
            } else if (strcasecmp("WRITE", word) == 0) {
                strcpy((char *) instr, WRITE);
            } else {
                continue;
            }
            fprintf(stdout, "\t[ic=%d] %s", instrCounter, word);

            // READ & WRITE will both have a second part (address)
            word = parseTokenField(instrStr, 2, " ");
            if (NULL != word) {
                strcat((char *) instr, word);
                fprintf(stdout, "\t[%d] %s", instrCounter, word);
            }

            // WRITE will have a third part (value)
            word = parseTokenField(instrStr, 3, " ");
            if (NULL != word) {
                strcat((char *) instr, word);
                fprintf(stdout, "\t[%d] %s", instrCounter, word);
            }

            fflush(stdout);
            loadCache(pc, &instr);

            ++pc;
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

    // TODO - just a check to view the record
    instruction *instr = fetch(0);

    return OK;
}
