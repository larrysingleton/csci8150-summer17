#include <main.h>

struct Queue* L1CToCPUFront;
struct Queue* L1CToCPURear;

void enqueueL1CToCPU(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L1CToCPUFront == NULL) {
        L1CToCPUFront = temp;
    } else {
        L1CToCPURear->next = temp;
        L1CToCPURear = temp;
    }
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
        L1CToCPUFront = L1CToCPURear->next;
    }
    free(temp);
}

struct Queue* frontCPUToL1C() {
    return L1CToCPUFront;
}

