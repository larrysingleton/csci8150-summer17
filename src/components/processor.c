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
    int addressRegisterLocation = (operation >> 10) & 0b001111111111;
    int dataRegisterLocation = (operation) & 0b0000000000001111111111;
    if(operation == READ) {
        printf("CPU to L1C: CPURead(%s)\n", fetchRegister(addressRegisterLocation));
    } else if(operation == WRITE) {
        printf("CPU to L1C: CPUWrite(%s) Data()\n", fetchRegister(addressRegisterLocation), fetchRegister(dataRegisterLocation));
    }

    // Send request off to L1C
    enqueue(fetchRegister(addressRegisterLocation),
            fetchRegister(dataRegisterLocation),
            instruction,
            CPUToL1CFront,
            CPUToL1CRear
    );
}

void processCPUIncoming() {
    if(L1CToCPUFront != NULL) { // If there is data on the queue to read.
        printf("CPU:       \taddress: '%s'\tvalue: '%s'\n", L1CToCPUFront->address, L1CToCPUFront->row);
        dequeue(L1CToCPUFront, L1CToCPURear);
    }
}