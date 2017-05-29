#ifndef CSCI8150_COMPONENTS_H
#define CSCI8150_COMPONENTS_H

typedef enum OP_CODE {
    NOOP = 0x00,
    READ = 0x01,
    WRITE = 0x10
};

void CPU();
void L1();
void L2();
void MEM();

int preLoadInstructionCache(const char *testFile);

#endif //CSCI8150_COMPONENTS_H
