#include <main.h>

struct Queue* tempFront;
struct Queue* tempRear;

void enqueueMemTemp(char* data, char* address, int64_t instruction, int opCode, int delay) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    temp->delay = delay;
    if(tempFront == NULL && tempRear == NULL) {
        tempFront = tempRear = temp;
    }
    tempRear->next = temp;
    tempRear = temp;
}

void dequeueMemTemp() {
    struct Queue* temp = tempFront;
    if(tempFront == NULL) {
        return;
    }
    if(tempFront == tempRear) {
        tempFront = tempRear = NULL;
    }
    else {
        tempFront = tempFront->next;
    }
    free(temp);
}

struct Queue* frontMemTemp() {
    return tempFront;
}