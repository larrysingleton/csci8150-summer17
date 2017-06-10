#include <main.h>

union udouble {
    double d;
    unsigned long u;
} ;

void processCPUIncoming();

void processInstruction(int64_t instruction);

void CPU(int64_t instruction) {
    processCPUIncoming();
    processInstruction(instruction);
}

void processInstruction(int64_t instruction) {
    enum OP_CODE operation = (enum OP_CODE) instruction >> 20; // Extract opcode from instruction.
    if(operation == READ) {
        int registerLocation = (operation >> 10) & 0b001111111111;
        printf("CPU to L1C: CPURead(%s)\n", fetchRegister(registerLocation));
    } else if(operation == WRITE) {

    }
    return;
}

void processCPUIncoming() {
    if(L1CToCPUFront != NULL) { // If there is data on the queue to read.
        printf("CPU:       \taddress: '%s'\tvalue: '%s'\n", L1CToCPUFront->row, L1CToCPUFront->address);
        dequeue(L1CToCPUFront, L1CToCPURear);
    }
}