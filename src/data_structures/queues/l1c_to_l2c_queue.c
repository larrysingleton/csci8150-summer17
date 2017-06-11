#include <main.h>

struct Queue* L1CToL2CFront;
struct Queue* L1CToL2CRear;

void enqueueL1CToL2C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L1CToL2CFront == NULL && L1CToL2CRear == NULL) {
        L1CToL2CFront = L1CToL2CRear = temp;
    }
    L1CToL2CRear->next = temp;
    L1CToL2CRear = temp;
}

void dequeueL1CToL2C() {
    struct Queue* temp = L1CToL2CFront;
    if(L1CToL2CFront == NULL) {
        return;
    }
    if(L1CToL2CFront == L1CToL2CRear) {
        L1CToL2CFront = L1CToL2CRear = NULL;
    }
    else {
        L1CToL2CFront = L1CToL2CFront->next;
    }
    free(temp);
}

struct Queue* frontL1CToL2C() {
    return L1CToL2CFront;
}

