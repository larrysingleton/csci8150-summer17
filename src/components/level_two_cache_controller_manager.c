#include <main.h>

void processMemToL2C();
void processL1ToL2();
void processL2DToL2C();
void processL2WBToL2C();

void L2() {
    processMemToL2C();
    processL2DToL2C();
    processL2WBToL2C();

    processL1ToL2();
    levelTwoDataCacheManager();
    levelTwoWriteBuffer();
}

void processL2WBToL2C() {
    // See if there is anything to process
    struct Queue* frontItem = frontL2DToL2C();
    if(frontItem != NULL) {
        // Print Status
        printf("L2C To L1C: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL2CToL1C(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        printf("L2C To L2D: Data(%s)\n", frontItem->address);
        enqueueL2CToL2D(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        evictFromL2WB((int) strtoll(frontItem->address, NULL, 2));

        //remove the message from the queue
        dequeueL2WBToL2C();
    }
}

void processL2DToL2C() {
    // See if there is anything to process
    struct Queue* frontItem = frontL2DToL2C();
    if(frontItem != NULL) {
        // Print Status
        printf("L2C To L1C: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL2CToL1C(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        //remove the message from the queue
        dequeueL2DToL2C();
    }
}

void processMemToL2C() {
    // See if there is anything to process
    struct Queue* frontItem = frontMemToL2C();
    if(frontItem != NULL) {
        // Print Status
        printf("L2C To L1C: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL2CToL1C(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        printf("L2C To L2D: Data(%s)\n", frontItem->address);

        enqueueL2CToL2D(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        //remove the message from the queue
        dequeueMemToL2C();
    }
}

void processL1ToL2() {
    // See if there is anything to process
    struct Queue* frontItem = frontL1CToL2C();
    if(frontItem != NULL) {
        int address = (int) strtoll(frontItem->address, NULL, 2);
        int inL2Cache = isInL2Cache(address);
        if (inL2Cache == HIT) {
            // If it is in L1D then enqueue a message to fetch that data.
            if(frontItem->instruction >> 20 == READ) {
                printf("L2C to L2D: Hit, Read(%s)\n", frontItem->address);
                enqueueL2CToL2D(NULL,
                                frontItem->address,
                                frontItem->instruction,
                                READ);
                setL2RowStatus(address, RD_WAIT_L2D);
            } else {
                printf("L2C to L2D: Hit, Write (%s)\n", frontItem->address);
                enqueueL2CToL2D(frontItem->data,
                                frontItem->address,
                                frontItem->instruction,
                                WRITE);
            }
        } else if(isInL2WB(address)) {
            if(frontItem->instruction >> 20 == READ) {
                printf("L2C to WB: Hit, Read(%s)\n", frontItem->address);
                enqueueL1CToL1WB(NULL,
                                 frontItem->address,
                                 frontItem->instruction,
                                READ);
                setL2RowStatus(address, RD_WAIT_WB);
            } else {
                printf("L2C to WB: Hit, Write(%s)\n", frontItem->address);
                enqueueL1CToL1WB(frontItem->data,
                                 frontItem->address,
                                 frontItem->instruction,
                                WRITE);
            }
        } else { // Cache miss
            if (inL2Cache == MISS_D) {
                printf("L2C to L2D: Miss, Victimize(%s)\n", frontItem->address);
                //victimizeL2(address); // In this case it means send to wb
            }
            if(frontItem->instruction >> 20 == READ) {
                printf("L2C to MEM: Miss, Read(%s)\n", frontItem->address);
                setL2RowStatus(address, RD_WAIT_MEM);
            } else {
                printf("L2C to MEM: Miss, Write(%s)\n", frontItem->address);
                setL2RowStatus(address, WR_WAIT_MEM);
            }

            enqueueL2CToMem(NULL,
                            frontItem->address,
                            frontItem->instruction,
                            READ);
        }
        // Remove the processed message.
        dequeueL1CToL2C();
    }
}

