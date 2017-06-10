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
};

void enqueue(char* data, char* address, struct Queue* front, struct Queue* rear);
void dequeue(struct Queue* front, struct Queue* rear);

enum OP_CODE {
    NOOP = 0,
    READ = 1,
    WRITE = 2
};

struct Queue* L1CToCPUFront;
struct Queue* L1CToCPURear;
struct Queue* CPUToL1CFront;
struct Queue* CPUToL1CRear;

#endif //CSCI8150_DATA_STRUCTURES_H_H