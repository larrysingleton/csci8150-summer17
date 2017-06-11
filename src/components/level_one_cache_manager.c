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

            enqueue(CPUToL1CFront->row,
                    CPUToL1CFront->address,
                    CPUToL1CFront->instruction,
                    L1CToL1DFront,
                    L1CToL1DRear);
        } else if(isInVC(address)) {
            // Basically no matter what all we ever do is read from the victim cache.
            if(CPUToL1CFront->instruction >> 20 == READ) {
                printf("L1C to VC: Hit, Read(%s)", CPUToL1CFront->address);
            } else {
                printf("L1C to VC: Hit, Read(%s) for Write", CPUToL1CFront->address);
            }

            enqueue(CPUToL1CFront->row,
                    CPUToL1CFront->address,
                    CPUToL1CFront->instruction,
                    L1CToVCFront,
                    L1CToVCRear);
        } else if(isInL1WB(address)) {
            if(CPUToL1CFront->instruction >> 20 == READ) {
                printf("L1C to WB: Hit, Read(%s)", CPUToL1CFront->address);
            } else {
                printf("L1C to WB: Hit, Write(%s)", CPUToL1CFront->address);
            }

            enqueue(CPUToL1CFront->row,
                    CPUToL1CFront->address,
                    CPUToL1CFront->instruction,
                    L1CToL1WBFront,
                    L1CToL1WBRear);
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