#include <main.h>

void processMemToL2C();
void processL1ToL2();

void L2() {
    processMemToL2C();
    // TODO: Processing response L2D
    // TODO: Processing response L2WB

    processL1ToL2();
}

void processMemToL2C() {
    // See if there is anything to process
    struct Queue* frontItem = frontMemToL2C();
    if(frontItem != NULL) {
        // Print Status
        printf("L2C To L1C: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL2CToL1C(frontItem->row,
                        frontItem->address,
                        frontItem->instruction);

        // TODO: Forward data to L2D
        printf("L2C To L2D: Data(%s)\n", frontItem->address);

        //remove the message from the queue
        dequeueMemToL2C();
    }
}

void processL1ToL2() {
    // See if there is anything to process
    struct Queue* frontItem = frontL1CToL2C();
    if(frontItem != NULL) {
        int address = atoi(frontItem->address);
        int inL2Cache = isInL2Cache(address);
        if (inL2Cache == HIT) {
            // If it is in L1D then enqueue a message to fetch that data.
            if(frontItem->instruction >> 20 == READ) {
                printf("L2C to L2D: Hit, Read(%s)\n", frontItem->address);
            } else {
                printf("L2C to L2D: Hit, Write (%s)\n", frontItem->address);
            }

            enqueueL2CToL2D(frontItem->row,
                            frontItem->address,
                            frontItem->instruction);
        } else if(isInL2WB(address)) {
            if(frontItem->instruction >> 20 == READ) {
                printf("L2C to WB: Hit, Read(%s)\n", frontItem->address);
            } else {
                printf("L2C to WB: Hit, Write(%s)\n", frontItem->address);
            }

            enqueueL1CToL1WB(frontItem->row,
                             frontItem->address,
                             frontItem->instruction);
        } else { // Cache miss
            if (inL2Cache == MISS_D) {
                printf("L2C to L2D: Miss, Victimize(%s)\n", frontItem->address);
                victimizeL1(address);
            }
            if(frontItem->instruction >> 20 == READ) {
                printf("L2C to MEM: Miss, Read(%s)\n", frontItem->address);
            } else {
                printf("L2C to MEM: Miss, Write(%s)\n", frontItem->address);
            }

            enqueueL2CToMem(frontItem->row,
                            frontItem->address,
                            frontItem->instruction);

            setL2RowWaiting(address);
        }
        // Remove the processed message.
        dequeueL1CToL2C();
    }
}

