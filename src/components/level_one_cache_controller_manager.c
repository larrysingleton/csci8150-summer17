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

    victimCache();
    levelOneWriteBuffer();
}

void processReturnValuesVCToL1C() {
    // See if there is anything in the queue.
    struct Queue *frontItem = frontVCToL1C();
    if(frontItem != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontItem->row,
                        frontItem->address,
                        frontItem->instruction);

        printf("L1C To L1D: Data(%s)\n", frontItem->address);
        // TODO: Forward data to L1D
        // TODO: evict data from VC.

        //remove the message from the queue
        dequeueVCToL1C();
    }
}

void processReturnValuesL1WBToL1C() {
    // See if there is anything in the queue.
    struct Queue *frontItem = frontL1WBToL1C();
    if(frontItem != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontItem->row,
                        frontItem->address,
                        frontItem->instruction);

        printf("L1C To L1D: Data(%s)\n", frontItem->address);
        // TODO: Forward data to L1D
        //TODO: evic data from WB

        //remove the message from the queue
        dequeueL1WBToL1C();
    }
}

void processReturnValuesL1DToL1C() {
    // See if there is anything in the queue.
    struct Queue *frontItem = frontL1DToL1C();
    if(frontItem != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontItem->row,
                        frontItem->address,
                        frontItem->instruction);

        // TODO: Forward data to L1D

        //remove the message from the queue
        dequeueL1DToL1C();
    }
}

void processReturnValuesL2CToL1C() {
    // See if there is anything in the queue.
    struct Queue *frontItem = frontL2CToL1C();
    if(frontItem != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL1CToCPU(frontItem->row,
                        frontItem->address,
                        frontItem->instruction);

        // TODO: Forward data to L1D

        //remove the message from the queue
        dequeueL2CToL1C();
    }
}

void processCPUToL1C() {
    // See if there is anything to process
    struct Queue *frontItem = frontCPUToL1C();
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
            if(frontItem->instruction >> 20 == READ) {
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

char* getMaskedData(int64_t instruction, char* data) {
    //TODO: instruction & last 10bits
    //TODO: value from steup one will be the location in the register of the mask
    //TODO: parse the register value into an integer (atoi(string))
    //TODO: extract the specified byte from data (it will be up to 64 bytes long)
    //TODO: return the extracted value.
}