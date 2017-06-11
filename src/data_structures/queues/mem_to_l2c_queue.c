#include <main.h>

struct Queue* MemToL2CFront;
struct Queue* MemToL2CCRear;

void enqueueMemToL2C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(MemToL2CFront == NULL && MemToL2CCRear == NULL) {
        MemToL2CFront = MemToL2CCRear = temp;
    }
    MemToL2CCRear->next = temp;
    MemToL2CCRear = temp;
}

void dequeueMemToL2C() {
    struct Queue* temp = MemToL2CFront;
    if(MemToL2CFront == NULL) {
        return;
    }
    if(MemToL2CFront == MemToL2CCRear) {
        MemToL2CFront = MemToL2CCRear = NULL;
    }
    else {
        MemToL2CFront = MemToL2CFront->next;
    }
    free(temp);
}

struct Queue* frontMemToL2C() {
    return MemToL2CFront;
}

