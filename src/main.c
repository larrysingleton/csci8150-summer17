#include <main.h>

struct Queue* L1CToCPUFront;
struct Queue* L1CToCPURear;

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

int main(int argc, char *argv[]) {
    int pc = 0;   // Keeps track of time, 1 unit of time equals 1 clock cycle.

    printf("\n Memory Subsystem starting...\n");

    if (argc!=2) {
        printf("\nMissing test case argument");
        printf("\nUsage: %s [test1 | test2 | test3]", basename(argv[0]));
        return ERR;
    }

    if (preLoadInstructionCache(argv[1]) != OK) {
        return ERR;
    }

    //execute CPU cycles until pipline is empty
    while(1) {
        int64_t instruction = fetchInstruction(pc);
        if(instruction == ERR &&
                inProgress() == ERR) { // Invalid instruction, means we have performed all the instructions.
            // TODO: add checks to make sure all queues are empty.
            break;
        }
        if(DEBUG) printf("Beginning clock cycle %d\n", pc);
        CPU(instruction);
        L1();
        L2();
        MEM();
        pc++;
    }
}

int inProgress() {
    if( L1CToCPUFront != NULL ||
        CPUToL1CFront != NULL ||
        L1DToL1CFront != NULL ||
        L1CToL1DFront != NULL ||
        L1CToVCFront != NULL ||
        VCToL1CFront != NULL ||
        L1CToL1WBFront != NULL ||
        L1WBToL1CFront != NULL ||
        L1CToL2CFront != NULL ||
        L2CToL1CFront != NULL ||
        L2CToL2WBFront != NULL ||
        L2WBToL2CFront != NULL ||
        L2DToL2CFront != NULL ||
        L2CToL2DFront != NULL ||
        L2CToMemFront != NULL ||
        MemToL2CFront != NULL) {
        return OK;
    }
    return ERR;
}