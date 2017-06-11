#include <main.h>

struct Queue* L2CToL2DFront;
struct Queue* L2CToL2DRear;

void enqueueL2CToL2D(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L2CToL2DFront == NULL && L2CToL2DRear == NULL) {
        L2CToL2DFront = L2CToL2DRear = temp;
    }
    L2CToL2DRear->next = temp;
    L2CToL2DRear = temp;
}

void dequeueL2CToL2D() {
    struct Queue* temp = L2CToL2DFront;
    if(L2CToL2DFront == NULL) {
        return;
    }
    if(L2CToL2DFront == L2CToL2DRear) {
        L2CToL2DFront = L2CToL2DRear = NULL;
    }
    else {
        L2CToL2DFront = L2CToL2DFront->next;
    }
    free(temp);
}

struct Queue* frontL2CToL2D() {
    return L2CToL2DFront;
}

