#ifndef CSCI8150_COMPONENTS_H
#define CSCI8150_COMPONENTS_H

typedef enum OP_CODE {
    NOOP = 0,
    READ = 1,
    WRITE = 2
};

void CPU();
void L1();
void L2();
void MEM();

int preLoadInstructionCache(const char *testFile);

#endif //CSCI8150_COMPONENTS_H
