#include <main.h>

struct Queue* L2DToL2CFront;
struct Queue* L2DToL2CRear;

void enqueueL2DToL2C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L2DToL2CFront == NULL && L2DToL2CRear == NULL) {
        L2DToL2CFront = L2DToL2CRear = temp;
    }
    L2DToL2CRear->next = temp;
    L2DToL2CRear = temp;
}

void dequeueL2DToL2C() {
    struct Queue* temp = L2DToL2CFront;
    if(L2DToL2CFront == NULL) {
        return;
    }
    if(L2DToL2CFront == L2DToL2CRear) {
        L2DToL2CFront = L2DToL2CRear = NULL;
    }
    else {
        L2DToL2CFront = L2DToL2CFront->next;
    }
    free(temp);
}

struct Queue* frontL2DToL2C() {
    return L2DToL2CFront;
}

