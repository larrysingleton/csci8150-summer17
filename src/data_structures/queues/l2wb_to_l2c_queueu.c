#include <main.h>

struct Queue* L2WBToL2CFront;
struct Queue* L2WBToL2CRear;

void enqueueL2WBToL2C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L2WBToL2CFront == NULL && L2WBToL2CRear == NULL) {
        L2WBToL2CFront = L2WBToL2CRear = temp;
    }
    L2WBToL2CRear->next = temp;
    L2WBToL2CRear = temp;
}

void dequeueL2WBToL2C() {
    struct Queue* temp = L2WBToL2CFront;
    if(L2WBToL2CFront == NULL) {
        return;
    }
    if(L2WBToL2CFront == L2WBToL2CRear) {
        L2WBToL2CFront = L2WBToL2CRear = NULL;
    }
    else {
        L2WBToL2CFront = L2WBToL2CFront->next;
    }
    free(temp);
}

struct Queue* frontL2WBToL2C() {
    return L2WBToL2CFront;
}

