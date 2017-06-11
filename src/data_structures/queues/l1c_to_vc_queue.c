#include <main.h>

struct Queue* L1CToVCFront;
struct Queue* L1CToVCRear;

void enqueueL1CToVC(char* data, char* address, int64_t instruction, int opCode) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    if(L1CToVCFront == NULL && L1CToVCRear == NULL) {
        L1CToVCFront = L1CToVCRear = temp;
    }
    L1CToVCRear->next = temp;
    L1CToVCRear = temp;
}

void dequeueL1CToVC() {
    struct Queue* temp = L1CToVCFront;
    if(L1CToVCFront == NULL) {
        return;
    }
    if(L1CToVCFront == L1CToVCRear) {
        L1CToVCFront = L1CToVCRear = NULL;
    }
    else {
        L1CToVCFront = L1CToVCFront->next;
    }
    free(temp);
}

struct Queue* frontL1CToVC() {
    return L1CToVCRear;
}