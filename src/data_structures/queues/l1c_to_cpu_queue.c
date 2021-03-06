#include <main.h>

struct Queue* L1CToCPUFront;
struct Queue* L1CToCPURear;

void enqueueL1CToCPU(char* data, char* address, int64_t instruction, int opCode) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    if(L1CToCPUFront == NULL && L1CToCPURear == NULL) {
        L1CToCPUFront = L1CToCPURear = temp;
    }
    L1CToCPURear->next = temp;
    L1CToCPURear = temp;
}

void dequeueL1CToCPU() {
    struct Queue* temp = L1CToCPUFront;
    if(L1CToCPUFront == NULL) {
        return;
    }
    if(L1CToCPUFront == L1CToCPURear) {
        L1CToCPUFront = L1CToCPURear = NULL;
    }
    else {
        L1CToCPUFront = L1CToCPUFront->next;
    }
    free(temp);
}

struct Queue* frontL1CToCPU() {
    return L1CToCPUFront;
}

