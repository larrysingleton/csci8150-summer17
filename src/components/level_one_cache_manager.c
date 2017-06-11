#include "main.h"



struct Queue* L1DToL1CFront;
struct Queue* L1DToL1CRear;

struct Queue* L1CToL1DFront;
struct Queue* L1CToL1DRear;

struct Queue* L1CToVCFront;
struct Queue* L1CToVCRear;

struct Queue* VCToL1CFront;
struct Queue* VCToL1CRear;

struct Queue* L1CToL1WBFront;
struct Queue* L1CToL1WBRear;

struct Queue* L1WBToL1CFront;
struct Queue* L1WBToL1CRear;

struct Queue* L1CToL2CFront;
struct Queue* L1CToL2CRear;

struct Queue* L2CToL1CFront;
struct Queue* L2CToL1CRear;

struct Queue* L2CToL1CFront;
struct Queue* L2CToL1CRear;

struct Queue* L2CToL2WBFront;
struct Queue* L2CToL2WBRear;

struct Queue* L2WBToL2CFront;
struct Queue* L2WBToL2CRear;

struct Queue* L2DToL2CFront;
struct Queue* L2DToL2CRear;

struct Queue* L2CToL2DFront;
struct Queue* L2CToL2DRear;

struct Queue* L2CToMemFront;
struct Queue* L2CToMemRear;

struct Queue* MemToL2CFront;
struct Queue* MemToL2CRear;

struct Queue* CPUToL1CFront;
struct Queue* CPUToL1CRear;

struct Queue* L1CToCPUFront;
struct Queue* L1CToCPURear;


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
    struct Queue* test = frontCPUToL1C();
    if(CPUToL1CFront != NULL) {
        int address = atoi(CPUToL1CFront->address);
        int inL1Cache = isInL1Cache(address);
        if (inL1Cache == HIT) {
            // If it is in L1D then enqueue a message to fetch that data.
            if(CPUToL1CFront->instruction >> 20 == READ) {
                printf("L1C to L1D: Hit, Read(%s)", CPUToL1CFront->address);
            } else {
                printf("L1C to L1D: Hit, Write (%s)", CPUToL1CFront->address);
            }

            enqueueL1CToL1D(CPUToL1CFront->row,
                    CPUToL1CFront->address,
                    CPUToL1CFront->instruction);
        } else if(isInVC(address)) {
            // Basically no matter what all we ever do is read from the victim cache.
            if(frontCPUToL1C()->instruction >> 20 == READ) {
                printf("L1C to VC: Hit, Read(%s)", CPUToL1CFront->address);
            } else {
                printf("L1C to VC: Hit, Read(%s) for Write", CPUToL1CFront->address);
            }

            enqueueL1CToVC(CPUToL1CFront->row,
                    CPUToL1CFront->address,
                    CPUToL1CFront->instruction);
        } else if(isInL1WB(address)) {
            if(CPUToL1CFront->instruction >> 20 == READ) {
                printf("L1C to WB: Hit, Read(%s)", CPUToL1CFront->address);
            } else {
                printf("L1C to WB: Hit, Write(%s)", CPUToL1CFront->address);
            }

            enqueueL1CToL1WB(CPUToL1CFront->row,
                    CPUToL1CFront->address,
                    CPUToL1CFront->instruction);
        } else { // Cache miss
            if (inL1Cache == MISS_D) {
                printf("L1C to L1D: Miss, Victimize(%s)", CPUToL1CFront->address);
                victimizeL1(address);
            }
            if(CPUToL1CFront->instruction >> 20 == READ) {
                printf("L1C to L2C: Miss, Read(%s)", CPUToL1CFront->address);
            } else {
                printf("L1C to L2C: Miss, Write(%s)", CPUToL1CFront->address);
            }

            enqueue(CPUToL1CFront->row,
                    CPUToL1CFront->address,
                    CPUToL1CFront->instruction,
                    L1CToL2CFront,
                    L1CToL2CRear);

            setL1RowWaitingL2(address);
        }
        // Remove the processed message.
        dequeue(CPUToL1CFront, CPUToL1CRear);
    }
}