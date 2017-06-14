#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

#include "main.h"

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
int victimizeL1(int address);
void setL1RowStatus(int address, int status);
void loadL1Cache(int address, char* data);
char* fetchFromL1Cache(int address);
int getL1RowStatus(int address);

// Victim cache
int isInVC(int address);
void loadVC(int address, char* data);
char* fetchFromVC(int address);
void evictFromVC(int address);

// L1 Writebuffer
int isInL1WB(int address);
void loadL1WB(int address, char* data);
void evictFromL1WB(int address);
char* fetchFromL1WB(int address);

// L2 Cache
int isInL2Cache(int address);
void setL2RowStatus(int address, int cacheState);
char* fetchFromL2Cache(int address);
void loadL2Cache(int address, char* data);

// L2 WriteBuffer
int isInL2WB(int address);
void loadL2WB(int address, char* data);
char* fetchFromL2WB(int address);
void evictFromL2WB(int address);

//Queues
typedef struct Queue {
    struct Queue *next; //next on the queue
    char* data; //The data in the queue
    char* address; // The address of the data that was fetched
    int opCode;
    int64_t instruction;
} queue;

void enqueueCPUToL1C(char* data, char* address, int64_t instruction, int opCode);
void dequeueCPUToL1C();
struct Queue* frontCPUToL1C();

void enqueueL1CToCPU(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1CToCPU();
struct Queue* frontL1CToCPU();

void enqueueL1DToL1C(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1DToL1C();
struct Queue* frontL1DToL1C();

void enqueueL1WBToL1C(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1WBToL1C();
struct Queue* frontL1WBToL1C();

void enqueueL2CToL1C(char* data, char* address, int64_t instruction, int opCode);
void dequeueL2CToL1C();
struct Queue* frontL2CToL1C();

void enqueueVCToL1C(char* data, char* address, int64_t instruction, int opCode);
void dequeueVCToL1C();
struct Queue* frontVCToL1C();

void enqueueL1CToL1D(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1CToL1D();
struct Queue* frontL1CToL1D();

void enqueueL1CToVC(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1CToVC();
struct Queue* frontL1CToVC();

void enqueueL1CToL1WB(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1CToL1WB();
struct Queue* frontL1CToL1WB();

void enqueueL1CToL2C(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1CToL2C();
struct Queue* frontL1CToL2C();

void enqueueL2CToL2D(char* data, char* address, int64_t instruction, int opCode);
void dequeueL2CToL2D();
struct Queue* frontL2CToL2D();

void enqueueL2DToL2C(char* data, char* address, int64_t instruction, int opCode);
void dequeueL2DToL2C();
struct Queue* frontL2DToL2C();

void enqueueL2WBToL2C(char* data, char* address, int64_t instruction, int opCode);
void dequeueL2WBToL2C();
struct Queue* frontL2WBToL2C();

void enqueueL2CToL2WB(char* data, char* address, int64_t instruction, int opCode);
void dequeueL2CToL2WB();
struct Queue* frontL2CToL2WB();

void enqueueL2CToMem(char* data, char* address, int64_t instruction, int opCode);
void dequeueL2CToMem();
struct Queue* frontL2CToMem();

void enqueueMemToL2C(char* data, char* address, int64_t instruction, int opCode);
void dequeueMemToL2C();
struct Queue* frontMemToL2C();

void enqueueL1Temp(char* data, char* address, int64_t instruction, int opCode);
void dequeueL1Temp();
struct Queue* frontL1Temp();

typedef struct node {
    char* data; //The data in the queue
    char* address; // The address of the data that was fetched
    int opCode;
    int64_t instruction;
    int delay;
    struct node *next;
    struct node *prev;
};

struct node* deleteMemTemp(char* address);
void insertLastMemTemp(char* data, char* address, int64_t instruction, int opCode, int delay);
struct node* frontMemTemp();


enum CHACHE_STATE {
    MISS_I = 0,
    MISS_C = 1,
    MISS_D = 2,
    HIT = 3,
    BUSY = 4
};

enum TRANS_STATE {
    RD_WAIT_L1D = 0,
    RD_WAIT_L2D = 1,
    RD_WAIT_WB = 2,
    RD_WAIT_VC = 3,
    RD_WAIT_MEM = 4,
    WR_WAIT_L2D = 5,
    WR_WAIT_VC = 6,
    WR_ALLOC = 7,
    READY = 8,
    WR_WAIT_MEM = 9
};

enum OP_CODE {
    NOOP = 0,
    READ = 1,
    WRITE = 2
};
#endif //CSCI8150_DATA_STRUCTURES_H_H