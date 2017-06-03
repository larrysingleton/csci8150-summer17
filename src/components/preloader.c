#include "main.h"


enum OP_CODE {
    NOOP = 0x00,
    READ = 0x01,
    WRITE = 0x10
};

int parseTestFile(FILE *file) {
    char *line = NULL;
    char *word = NULL;

    enum OP_CODE op = NOOP;

    char instrBuf[8];
    unsigned char instr = 0;
    int regAddress;
    char instructionLine[64];

    size_t len = 0;
    int pc = 0;
    char operation[2];

    while (getline(&line, &len, file) != -1) {

        // skip comment lines
        if (line[0] == '#') {
            continue;
        }

        // trim off the trailing new lines
        line[strcspn(line, "\n\r")] = 0;
        if(DEBUG) printf("\nWhole line string: [%s]\n", line);

        // clear structures
        memset(instructionLine, sizeof(instructionLine), 0);
        memset(instrBuf, sizeof(instrBuf), 0);
        instr=0;
        regAddress=0;

        // Parse operation
        word = strtok(line, " ");
        if(DEBUG) printf("Operation string: [%s]\n", word);

        if (strcasecmp("READ", word) == 0) {
            strcpy(instrBuf, "01");
            op = READ;
        } else if (strcasecmp("WRITE", word) == 0) {
            strcpy(instrBuf, "10");
            op = WRITE;
        } else {
            return ERR; // Only support read and write operations
        }

        // get address
        word = strtok(NULL, " ");

        if (NULL != word) {
            if (DEBUG) printf("Address found: [%s]\n", word);

            strcat(instrBuf, word);
            if (DEBUG) printf("Instruction buffer: [%s]\n", instrBuf);

            instr = packInstruction(instrBuf);
            if (DEBUG) printf("Packed instruction: [0x%04x]\n", instr);

            // record the instruction in the 1st index of the instruction line
            instructionLine[0] = instr;
        } else {
            return ERR;
        }

        if(op == WRITE) {
            // WRITE will have a third part (value)
            word = strtok(NULL, " ");
            if(DEBUG) printf("Data found: [%s]\n", word);

            if (NULL != word) {
                // load the data into the register file.
                regAddress = loadRegister(word);
                if (DEBUG) printf("Register address: [%d]\n", regAddress);
                if (DEBUG) printf("Fetched data from register: [%s]\n", fetchRegister(regAddress));

                char regAddressArray[8];
                for(int i = 0 ; i < 8 ; i++)
                {
                    regAddressArray[i] = regAddress & (int) pow(2,7-i);
                }
                unsigned char regAddrPacked = packInstruction(regAddressArray);
                if (DEBUG) printf("Packed register address: [0x%04x]\n", regAddrPacked);

                // record the register address in the 2nd index of instruction line
                instructionLine[1] = regAddrPacked;

            } else {
                return ERR;
            }
        }

        // load the instruction line into the cache
        loadCache(pc, instructionLine);

        // TODO : fetch of the instruction isn't working yet
        // if (DEBUG) printf("Loaded instruction: [%s]\n", fetch(pc));

        ++pc;
    }
    return OK;
}

int preLoadInstructionCache(const char *testFile) {
    FILE *file;

    printf("\nLoading instruction cache from: [%s]", testFile);
    if (file = fopen(testFile, "r")) {
        parseTestFile(file);
        fclose(file);
    } else {
        printf("\nUnable to read test file: %s", testFile);
        return ERR;
    }

    // TODO - just a check to view the record
    char* instr = fetch(0);

    return OK;
}

unsigned char packInstruction(char *buf) {
    int i;
    unsigned char result = 0;
    for (i=0;i<8;i++) {
        result |= (buf[i]=='1') << (7-i);
    }
}
