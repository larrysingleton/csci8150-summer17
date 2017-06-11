#include "main.h"

void processReturnValuesL1DToL1C();
void processCPUToL1C();
void processReturnValuesL1WBToL1C();
void processReturnValuesL2CToL1C();
void processReturnValuesVCToL1C();

void L1() {
    // Process values coming back from past requests
    processReturnValuesL1DToL1C();
    processReturnValuesL1WBToL1C();
    processReturnValuesL2CToL1C();
    processReturnValuesVCToL1C();

    // Process new instructions coming from CPU
    processCPUToL1C();
}

void processReturnValuesVCToL1C() {
    // See if there is anything in the queue.
    if(frontVCToL1C() != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontVCToL1C()->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontVCToL1C()->row,
                        frontVCToL1C()->address,
                        frontVCToL1C()->instruction);

        // TODO: Forward data to L1D

        //remove the message from the queue
        dequeueVCToL1C();
    }
}

void processReturnValuesL1WBToL1C() {
    // See if there is anything in the queue.
    if(frontL1WBToL1C() != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontL1WBToL1C()->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontL1WBToL1C()->row,
                        frontL1WBToL1C()->address,
                        frontL1WBToL1C()->instruction);

        // TODO: Forward data to L1D

        //remove the message from the queue
        dequeueL1WBToL1C();
    }
}

void processReturnValuesL1DToL1C() {
    // See if there is anything in the queue.
    if(frontL1DToL1C() != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontL1DToL1C()->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontL1DToL1C()->row,
                        frontL1DToL1C()->address,
                        frontL1DToL1C()->instruction);

        // TODO: Forward data to L1D

        //remove the message from the queue
        dequeueL1DToL1C();
    }
}

void processReturnValuesL2CToL1C() {
    // See if there is anything in the queue.
    if(frontL2CToL1C() != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontL2CToL1C()->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontL2CToL1C()->row,
                        frontL2CToL1C()->address,
                        frontL2CToL1C()->instruction);

        // TODO: Forward data to L1D

        //remove the message from the queue
        dequeueL2CToL1C();
    }
}

void processCPUToL1C() {
    // See if there is anything to process
    struct Queue* frontItem = frontCPUToL1C();
    if(frontItem != NULL) {
        int address = atoi(frontItem->address);
        int inL1Cache = isInL1Cache(address);
        if (inL1Cache == HIT) {
            // If it is in L1D then enqueue a message to fetch that data.
            if(frontItem->instruction >> 20 == READ) {
                printf("L1C to L1D: Hit, Read(%s)\n", frontItem->address);
            } else {
                printf("L1C to L1D: Hit, Write (%s)\n", frontItem->address);
            }

            enqueueL1CToL1D(frontItem->row,
                    frontItem->address,
                    frontItem->instruction);
        } else if(isInVC(address) == 1) {
            // Basically no matter what all we ever do is read from the victim cache.
            if(frontCPUToL1C()->instruction >> 20 == READ) {
                printf("L1C to VC: Hit, Read(%s)\n", frontItem->address);
            } else {
                printf("L1C to VC: Hit, Read(%s) for Write\n", frontItem->address);
            }

            enqueueL1CToVC(frontItem->row,
                    frontItem->address,
                    frontItem->instruction);
        } else if(isInL1WB(address) == 1) {
            if(frontItem->instruction >> 20 == READ) {
                printf("L1C to WB: Hit, Read(%s)\n", frontItem->address);
            } else {
                printf("L1C to WB: Hit, Write(%s)\n", frontItem->address);
            }

            enqueueL1CToL1WB(frontItem->row,
                    frontItem->address,
                    frontItem->instruction);
        } else { // Cache miss
            if (inL1Cache == MISS_D) {
                printf("L1C to L1D: Miss, Victimize(%s)\n", frontItem->address);
                victimizeL1(address);
            }
            if(frontItem->instruction >> 20 == READ) {
                printf("L1C to L2C: Miss, Read(%s)\n", frontItem->address);
            } else {
                printf("L1C to L2C: Miss, Write(%s)\n", frontItem->address);
            }

            enqueueL1CToL2C(frontItem->row,
                    frontItem->address,
                    frontItem->instruction);

            setL1RowWaiting(address);
        }
        // Remove the processed message.
        dequeueCPUToL1C();
    }
}