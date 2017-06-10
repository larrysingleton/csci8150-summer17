#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

int64_t fetchInstruction(int programCounter);
void loadInstructionCache(int programCounter, int64_t instruction);

// Register File
int loadRegister(char* value);
char* fetchRegister(int registerLocation);

// Memory
void loadMemoryBlock(long address, char* data);
char* fetchMemoryBlock(long address);

//Queues

typedef struct Queue {
    struct Queue* next; //next on the queue
    char* row; //The data in the queue
    char* address; // The address of the data that was fetched
    int64_t instruction;
};

void enqueue(char* data, char* address, int64_t instruction, struct Queue* front, struct Queue* rear);
void dequeue(struct Queue* front, struct Queue* rear);

enum OP_CODE {
    NOOP = 0,
    READ = 1,
    WRITE = 2
};


// All of the required queues.
struct Queue* L1CToCPUFront;
struct Queue* L1CToCPURear;

struct Queue* CPUToL1CFront;
struct Queue* CPUToL1CRear;

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


#endif //CSCI8150_DATA_STRUCTURES_H_H