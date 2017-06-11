#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

int64_t fetchInstruction(int programCounter);
void loadInstructionCache(int programCounter, int64_t instruction);

// Register File
int loadRegister(char* value);
char* fetchRegister(int registerLocation);

// Memory
void loadMemoryBlock(int address, char* data);
char* fetchMemoryBlock(int address);

// L1 Cache
int isInL1Cache(int address);
void victimizeL1(int address);
void setL1RowWaitingL2(int address);

// Victim cache
int isInVC(int address);

// L1 Writebuffer
int isInL1WB(int address);

//Queues
typedef struct Queue {
    struct Queue *next; //next on the queue
    char* row; //The data in the queue
    char* address; // The address of the data that was fetched
    int64_t instruction;
};

void enqueueCPUToL1C(char* data, char* address, int64_t instruction);
void dequeueCPUToL1C();
struct Queue* frontCPUToL1C();

void enqueueL1CToCPU(char* data, char* address, int64_t instruction);
void dequeueL1CToCPU();
struct Queue* frontCPUToL1C();

void enqueueL1DToL1C(char* data, char* address, int64_t instruction);
void dequeueL1DToL1C();
struct Queue* frontL1DToL1C();

void enqueueL1WBToL1C(char* data, char* address, int64_t instruction);
void dequeueL1WBToL1C();
struct Queue* frontL1WBToL1C();

void enqueueL2CToL1C(char* data, char* address, int64_t instruction);
void dequeueL2CToL1C();
struct Queue* frontL2CToL1C();

void enqueueVCToL1C(char* data, char* address, int64_t instruction);
void dequeueVCToL1C();
struct Queue* frontVCToL1C();

void enqueueL1CToL1D(char* data, char* address, int64_t instruction);
void dequeueL1CToL1D();
struct Queue* frontL1CToL1D();

void enqueueL1CToVC(char* data, char* address, int64_t instruction);
void dequeueL1CToVC();
struct Queue* frontL1CToVC();

void enqueueL1CToL1WB(char* data, char* address, int64_t instruction);
void dequeueL1CToL1WB();
struct Queue* frontL1CToL1WB();

enum CHACHE_STATE {
    MISS_I = 0,
    MISS_C = 1,
    MISS_D = 2,
    HIT = 3
};

enum OP_CODE {
    NOOP = 0,
    READ = 1,
    WRITE = 2
};
#endif //CSCI8150_DATA_STRUCTURES_H_H