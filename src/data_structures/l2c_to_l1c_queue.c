#include <main.h>

struct Queue* L2CToL1CFront;
struct Queue* L2CToL1CRear;

void enqueueL2CToL1C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L2CToL1CFront == NULL) {
        L2CToL1CFront = temp;
    } else {
        L2CToL1CRear->next = temp;
        L2CToL1CRear = temp;
    }
}

void dequeueL2CToL1C() {
    struct Queue* temp = L2CToL1CFront;
    if(L2CToL1CFront == NULL) {
        return;
    }
    if(L2CToL1CFront == L2CToL1CRear) {
        L2CToL1CFront = L2CToL1CRear = NULL;
    }
    else {
        L2CToL1CFront = L2CToL1CRear->next;
    }
    free(temp);
}

struct Queue* frontL2CToL1C() {
    return L2CToL1CFront;
}