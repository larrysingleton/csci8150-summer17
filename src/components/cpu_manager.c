#include <main.h>

void processCPUIncoming();
void processInstruction(int64_t instruction);

void CPU(int pc) {
    processCPUIncoming();
    int64_t instruction = fetchInstruction(pc);
    if(instruction != ERR) {
        processInstruction(instruction);
    }
}

void processInstruction(int64_t instruction) {
    enum OP_CODE operation = (enum OP_CODE) instruction >> 20; // Extract opcode from instruction.
    int addressRegisterLocation = (int) (instruction >> 10) & 0b001111111111;
    int dataRegisterLocation = (int) instruction & 0b0000000000001111111111;
    if(operation == READ) {
        printf("CPU to L1C: CPURead(%s)\n", fetchRegister(addressRegisterLocation));
    } else if(operation == WRITE) {
        printf("CPU to L1C: CPUWrite(%s) Data(%s)\n", fetchRegister(addressRegisterLocation), fetchRegister(dataRegisterLocation));
    }

    // Send request off to L1C
    enqueueCPUToL1C(fetchRegister(dataRegisterLocation),
            fetchRegister(addressRegisterLocation),
            instruction,
            operation
    );
}

void processCPUIncoming() {
    struct Queue* l1CToCPUFront = frontL1CToCPU();
    if(l1CToCPUFront != NULL) { // If there is data on the queue to read.
        printf("CPU: address: (%s) value: %s\n", l1CToCPUFront->address, l1CToCPUFront->data);
        dequeueL1CToCPU();
    }
}