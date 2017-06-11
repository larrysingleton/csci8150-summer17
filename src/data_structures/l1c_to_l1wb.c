#include <main.h>

struct Queue* L1CToL1WBFront;
struct Queue* L1CToL1WBRear;

void enqueueL1CToL1WB(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L1CToL1WBFront == NULL) {
        L1CToL1WBFront = temp;
    } else {
        L1CToL1WBRear->next = temp;
        L1CToL1WBRear = temp;
    }
}

void dequeueCPUToL1C() {
    struct Queue* temp = L1CToL1WBFront;
    if(L1CToL1WBFront == NULL) {
        return;
    }
    if(L1CToL1WBFront == L1CToL1WBRear) {
        L1CToL1WBFront = L1CToL1WBRear = NULL;
    }
    else {
        L1CToL1WBFront = L1CToL1WBRear->next;
    }
    free(temp);
}

struct Queue* frontCPUToL1C() {
    return L1CToL1WBFront;
}

