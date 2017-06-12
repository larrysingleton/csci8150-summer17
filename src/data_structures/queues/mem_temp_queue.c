#include <main.h>

struct Queue* memTempFront;
struct Queue* memTempRear;

void enqueueMemTemp(char* data, char* address, int64_t instruction, int opCode, int delay) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    temp->delay = delay;
    if(memTempFront == NULL && memTempRear == NULL) {
        memTempFront = memTempRear = temp;
    }
    memTempRear->next = temp;
    memTempRear = temp;
}

void dequeueMemTemp() {
    struct Queue* temp = memTempFront;
    if(memTempFront == NULL) {
        return;
    }
    if(memTempFront == memTempRear) {
        memTempFront = memTempRear = NULL;
    }
    else {
        memTempFront = memTempFront->next;
    }
    free(temp);
}

struct Queue* frontMemTemp() {
    return memTempFront;
}