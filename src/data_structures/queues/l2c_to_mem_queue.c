#include <main.h>

struct Queue* L2CToMemFront;
struct Queue* L2CToMemRear;

void enqueueL2CToMem(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L2CToMemFront == NULL && L2CToMemRear == NULL) {
        L2CToMemFront = L2CToMemRear = temp;
    }
    L2CToMemRear->next = temp;
    L2CToMemRear = temp;
}

void dequeueL2CToMem() {
    struct Queue* temp = L2CToMemFront;
    if(L2CToMemFront == NULL) {
        return;
    }
    if(L2CToMemFront == L2CToMemRear) {
        L2CToMemFront = L2CToMemRear = NULL;
    }
    else {
        L2CToMemFront = L2CToMemFront->next;
    }
    free(temp);
}

struct Queue* frontL2CToMem() {
    return L2CToMemFront;
}

