#include <main.h>

struct Queue* tempFront;
struct Queue* tempRear;

void enqueueL1Temp(char* data, char* address, int64_t instruction, int opCode) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    if(tempFront == NULL && tempRear == NULL) {
        tempFront = tempRear = temp;
    }
    tempRear->next = temp;
    tempRear = temp;
}

void dequeueL1Temp() {
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

struct Queue* frontL1Temp() {
    return tempFront;
}