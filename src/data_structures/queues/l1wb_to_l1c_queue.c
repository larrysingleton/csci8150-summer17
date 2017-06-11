#include <main.h>

struct Queue* L1WBToL1CFront;
struct Queue* L1WBToL1CRear;

void enqueueL1WBToL1C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L1WBToL1CFront == NULL && L1WBToL1CRear == NULL) {
        L1WBToL1CFront = L1WBToL1CRear = temp;
    }
    L1WBToL1CRear->next = temp;
    L1WBToL1CRear = temp;
}

void dequeueL1WBToL1C() {
    struct Queue* temp = L1WBToL1CFront;
    if(L1WBToL1CFront == NULL) {
        return;
    }
    if(L1WBToL1CFront == L1WBToL1CRear) {
        L1WBToL1CFront = L1WBToL1CRear = NULL;
    }
    else {
        L1WBToL1CFront = L1WBToL1CFront->next;
    }
    free(temp);
}

struct Queue* frontL1WBToL1C() {
    return L1WBToL1CFront;
}