#include <main.h>

char* getDataByMask(int64_t instruction, char *data);
void processReturnValuesL1DToL1C();
void processCPUToL1C();
void processReturnValuesL1WBToL1C();
void processReturnValuesL2CToL1C();
void processReturnValuesVCToL1C();
void processTempQueue();


void L1() {
    //Process temporary holding queue.
    processTempQueue();

    // Process values coming back from past requests
    processReturnValuesL1DToL1C();
    processReturnValuesL1WBToL1C();
    processReturnValuesL2CToL1C();
    processReturnValuesVCToL1C();

    // Process new instructions coming from CPU
    processCPUToL1C();

    levelOneDataCacheManager();
    victimCache();
    levelOneWriteBuffer();
}

void processTempQueue() {
    // See if there is anything in the queue.
    struct Queue *frontItem = frontL1Temp();
    if(frontItem != NULL) {
        int address = (int) strtoll(frontItem->address, NULL, 2);
        enum OP_CODE operation = (enum OP_CODE) frontItem->instruction >> 20;
        if(getL1RowStatus(address) == READY && operation == READ) {
            enqueueCPUToL1C(frontItem->data,
                            frontItem->address,
                            frontItem->instruction,
                            frontItem->opCode);
            dequeueL1Temp();
        } else if((getL1RowStatus(address) == WR_ALLOC || getL1RowStatus(address) == READY)&& operation == WRITE) {
            enqueueCPUToL1C(frontItem->data,
                            frontItem->address,
                            frontItem->instruction,
                            frontItem->opCode);
            dequeueL1Temp();
        }
        // If the cache line isn't ready, just keep holding it in the queue
    }
}

void processReturnValuesVCToL1C() {
    // See if there is anything in the queue.
    struct Queue *frontItem = frontVCToL1C();
    if(frontItem != NULL) {
        // Print Status
        printf("L1C To CPU: Data(%s)\n", frontItem->address);


        char *data = getDataByMask(frontItem->instruction, frontItem->data);

        // Forward data onto CPU.
        enqueueL1CToCPU(data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        printf("L1C To L1D: Data(%s)\n", frontItem->address);
        enqueueL1CToL1D(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        evictFromVC((int) strtoll(frontItem->address, NULL, 2));

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

        char *data = getDataByMask(frontItem->instruction, frontItem->data);

        // Forward data onto CPU.
        enqueueL1CToCPU(data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        printf("L1C To L1D: Data(%s)\n", frontItem->address);
        enqueueL1CToL1D(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        evictFromL1WB((int) strtoll(frontItem->address, NULL, 2));

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

        char *data = getDataByMask(frontItem->instruction, frontItem->data);

        // Forward data onto CPU.
        enqueueL1CToCPU(data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        //remove the message from the queue
        dequeueL1DToL1C();
    }
}

void processReturnValuesL2CToL1C() {
    // See if there is anything in the queue.
    struct Queue *frontItem = frontL2CToL1C();
    if(frontItem != NULL) {
        enum OP_CODE operation = (enum OP_CODE) frontItem->instruction >> 20;
        if(operation == READ) {
            char *data = getDataByMask(frontItem->instruction, frontItem->data);
            printf("L1C To CPU: Data(%s)\n", frontItem->address);
            // Forward data onto CPU.
            enqueueL1CToCPU(data,
                            frontItem->address,
                            frontItem->instruction,
                            WRITE);
        }

        printf("L1C To L1D: Data(%s)\n", frontItem->address);
        enqueueL1CToL1D(frontItem->data,
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);


        //remove the message from the queue
        dequeueL2CToL1C();
    }
}

void processCPUToL1C() {
    // See if there is anything to process
    struct Queue *frontItem = frontCPUToL1C();
    if(frontItem != NULL) {
        int address = (int) strtoll(frontItem->address, NULL, 2);
        int inL1Cache = isInL1Cache(address);
        if (inL1Cache == HIT) {
            if((getL1RowStatus(address) != READY && frontItem->opCode == READ) ||
                    (getL1RowStatus(address) != READY && getL1RowStatus(address) != WR_ALLOC && frontItem->opCode == WRITE)) {
                // Put the message at the end of the queue
                enqueueL1Temp(frontItem->data,
                              frontItem->address,
                              frontItem->instruction,
                              frontItem->opCode);
            } else {
                // If it is in L1D then enqueue a message to fetch that data.
                if(frontItem->instruction >> 20 == READ) {
                    printf("L1C to L1D: Hit, Read(%s)\n", frontItem->address);
                    enqueueL1CToL1D(NULL,
                                    frontItem->address,
                                    frontItem->instruction,
                                    READ);
                } else {
                    printf("L1C to L1D: Hit, Write (%s)\n", frontItem->address);
                    enqueueL1CToL1D(frontItem->data,
                                    frontItem->address,
                                    frontItem->instruction,
                                    WRITE);
                }
            }
        } else if(isInVC(address) == 1) {
            // Basically no matter what all we ever do is read from the victim cache.
            if(frontItem->instruction >> 20 == READ) {
                printf("L1C to VC: Hit, Read(%s)\n", frontItem->address);
            } else {
                printf("L1C to VC: Hit, Read(%s) for Write\n", frontItem->address);
            }

            enqueueL1CToVC(NULL,
                        frontItem->address,
                        frontItem->instruction,
                        READ);
        } else if(isInL1WB(address) == 1) {
            if(frontItem->instruction >> 20 == READ) {
                printf("L1C to WB: Hit, Read(%s)\n", frontItem->address);
                enqueueL1CToL1WB(NULL,
                                 frontItem->address,
                                 frontItem->instruction,
                                 READ);
            } else {
                printf("L1C to WB: Hit, Write(%s)\n", frontItem->address);
                enqueueL1CToL1WB(frontItem->data,
                                 frontItem->address,
                                 frontItem->instruction,
                                 WRITE);
            }
        } else { // Cache miss
            if (inL1Cache == MISS_D) {
                printf("L1C to L1D: Miss, Victimize(%s)\n", frontItem->address);
                char *data = fetchFromL1Cache(address);
                char* evictedAddress = NULL;
                int evictedAddressInt = victimizeL1(address);
                itoa(evictedAddressInt, evictedAddress, 2);

                printf("L1C to L1WB: Write(%s)\n", evictedAddress);
                enqueueL1CToL1WB(data,
                                 evictedAddress,
                                 0,
                                 WRITE);
            }
            if(inL1Cache == MISS_C) {
                printf("L1C to L1D: Miss, Victimize(%s)\n", frontItem->address);
                char *data = fetchFromL1Cache(address);
                char* evictedAddress = NULL;
                int evictedAddressInt = victimizeL1(address);
                itoa(evictedAddressInt, evictedAddress, 2);

                printf("L1C to VC: Write(%s)\n", evictedAddress);
                enqueueL1CToVC(data,
                                 evictedAddress,
                                 0,
                                 WRITE);
            }
            if(frontItem->instruction >> 20 == READ) {
                printf("L1C to L2C: Miss, Read(%s)\n", frontItem->address);
                setL1RowStatus(address, RD_WAIT_L2D);
            } else {
                printf("L1C to L2C: Miss, Write(%s)\n", frontItem->address);
                setL1RowStatus(address, WR_WAIT_L2D);
                enqueueL1Temp(frontItem->data,
                            frontItem->address,
                            frontItem->instruction,
                            WRITE);
            }

            enqueueL1CToL2C(NULL,
                            frontItem->address,
                            frontItem->instruction,
                            READ);
        }
        // Remove the processed message.
        dequeueCPUToL1C();
    }
}

char* getDataByMask(int64_t instruction, char *data) {
    int dataRegisterLocation = (int)(instruction) & 0b0000000000001111111111;
    char *dataMaskString = fetchRegister(dataRegisterLocation);
    int dataMask = (int) strtol(dataMaskString, NULL, 2);
    char *newData = NULL;
    if(data != NULL)
        newData = &data[dataMask];
    return newData;
}