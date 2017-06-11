#include <main.h>

struct Queue* L1CToL1DFront;
struct Queue* L1CToL1DRear;

void enqueueL1CToL1D(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L1CToL1DFront == NULL && L1CToL1DRear == NULL) {
        L1CToL1DFront = L1CToL1DRear = temp;
    }
    L1CToL1DRear->next = temp;
    L1CToL1DRear = temp;
}

void dequeueL1CToL1D() {
    struct Queue* temp = L1CToL1DFront;
    if(L1CToL1DFront == NULL) {
        return;
    }
    if(L1CToL1DFront == L1CToL1DRear) {
        L1CToL1DFront = L1CToL1DRear = NULL;
    }
    else {
        L1CToL1DFront = L1CToL1DFront->next;
    }
    free(temp);
}

struct Queue* frontL1CToL1D() {
    return L1CToL1DRear;
}