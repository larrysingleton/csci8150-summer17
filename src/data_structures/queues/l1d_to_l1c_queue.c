#include <main.h>

struct Queue* L1DToL1CFront;
struct Queue* L1DToL1CRear;

void enqueueL1DToL1C(char* data, char* address, int64_t instruction, int opCode) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    if(L1DToL1CFront == NULL && L1DToL1CRear == NULL) {
        L1DToL1CFront = L1DToL1CRear = temp;
    }
    L1DToL1CRear->next = temp;
    L1DToL1CRear = temp;
}

void dequeueL1DToL1C() {
    struct Queue* temp = L1DToL1CFront;
    if(L1DToL1CFront == NULL) {
        return;
    }
    if(L1DToL1CFront == L1DToL1CRear) {
        L1DToL1CFront = L1DToL1CRear = NULL;
    }
    else {
        L1DToL1CFront = L1DToL1CFront->next;
    }
    free(temp);
}

struct Queue* frontL1DToL1C() {
    return L1DToL1CFront;
}