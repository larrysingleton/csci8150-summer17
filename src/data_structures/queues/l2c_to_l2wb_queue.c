#include <main.h>

struct Queue* L2CToL2WBFront;
struct Queue* L2CToL2WBRear;

void enqueueL2CToL2WB(char* data, char* address, int64_t instruction, int opCode) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    if(L2CToL2WBFront == NULL && L2CToL2WBRear == NULL) {
        L2CToL2WBFront = L2CToL2WBRear = temp;
    }
    L2CToL2WBRear->next = temp;
    L2CToL2WBRear = temp;
}

void dequeueL2CToL2WB() {
    struct Queue* temp = L2CToL2WBFront;
    if(L2CToL2WBFront == NULL) {
        return;
    }
    if(L2CToL2WBFront == L2CToL2WBRear) {
        L2CToL2WBFront = L2CToL2WBRear = NULL;
    }
    else {
        L2CToL2WBFront = L2CToL2WBFront->next;
    }
    free(temp);
}

struct Queue* frontL2CToL2WB() {
    return L2CToL2WBFront;
}

