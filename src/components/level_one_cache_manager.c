#include "main.h"

void processReturnValues(struct Queue* front, struct Queue* rear);
void processCPUToL1C();

void L1() {
    // Process values coming back from past requests
    processReturnValues(L1DToL1CFront, L1DToL1CRear);
    processReturnValues(L1WBToL1CFront, L1WBToL1CRear);
    processReturnValues(L2CToL1CFront, L2CToL1CRear);
    processReturnValues(VCToL1CFront, VCToL1CRear);

    // Process new instructions coming from CPU
    processCPUToL1C();
}

void processReturnValues(struct Queue* front, struct Queue* rear) {
    // See if there is anything in the queue.
    if(front != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", front->address);
        // Forward data onto CPU.
        enqueue(front->row,
                front->address,
                front->instruction,
                L1CToCPUFront,
                L1CToCPURear);

        // TODO: Forward data to L1D

        //remove the message from the queue
        dequeue(front, rear);
    }
}

void processCPUToL1C() {
    // See if there is anything to process
    if(CPUToL1CFront != NULL) {

        //TODO: If Read
            // TODO: If L1 Hit
                // TODO: if in L1D, send a message to L1D
                // TODO: if in VC, send a message to VC
                // TODO: if in L1WB, send a message to L1WB
            //TODO: If L1 Miss
                // TODO: If there is no data (e.g. missi) send message to L2C, set status to waiting in controller
                // TODO: If the data in L1D is missing but clean (e.g. missc) send message to L2C, set status to waiting.
                // TODO: If the data in L1D is missing but dirty (e.g. missd) victimize row, and send message to L2C, set status to waiting
        // TODO: If Write
            // TODO: If L1 hit
                // TODO: if in L1D, send a message to L1D
                // TODO: if in VC, send a message to VC
                // TODO: if in L1WB, send a message to L1WB
            // TODO: If L1 miss
                // TODO: If there is no data (e.g. missi) send message to L2C, set status to waiting in controller
                // TODO: If the data in L1D is missing but clean (e.g. missc) send message to L2C, set status to waiting.
                // TODO: If the data in L1D is missing but dirty (e.g. missd) victimize row, and send message to L2C, set status to waiting
        // Remove the processed message.
        dequeue(CPUToL1CFront, CPUToL1CRear);
    }
}