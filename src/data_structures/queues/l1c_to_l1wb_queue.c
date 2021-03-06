#include <main.h>

struct Queue* L1CToL1WBFront;
struct Queue* L1CToL1WBRear;

void enqueueL1CToL1WB(char* data, char* address, int64_t instruction, int opCode) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    if(L1CToL1WBFront == NULL && L1CToL1WBRear == NULL) {
        L1CToL1WBFront = L1CToL1WBRear = temp;
    }
    L1CToL1WBRear->next = temp;
    L1CToL1WBRear = temp;
}

void dequeueL1CToL1WB() {
    struct Queue* temp = L1CToL1WBFront;
    if(L1CToL1WBFront == NULL) {
        return;
    }
    if(L1CToL1WBFront == L1CToL1WBRear) {
        L1CToL1WBFront = L1CToL1WBRear = NULL;
    }
    else {
        L1CToL1WBFront = L1CToL1WBFront->next;
    }
    free(temp);
}

struct Queue* frontL1CToL1WB() {
    return L1CToL1WBFront;
}

