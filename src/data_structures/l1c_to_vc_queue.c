#include <main.h>

struct Queue* L1CToVCFront;
struct Queue* L1CToVCRear;

void enqueueL1CToVC(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(L1CToVCFront == NULL) {
        L1CToVCFront = temp;
    } else {
        L1CToVCFront->next = temp;
        L1CToVCFront = temp;
    }
}

void dequeueL1CToVC() {
    struct Queue* temp = L1CToVCFront;
    if(L1CToVCFront == NULL) {
        return;
    }
    if(L1CToVCFront == L1CToVCRear) {
        L1CToVCFront = L1CToVCRear = NULL;
    }
    else {
        L1CToVCFront = L1CToVCRear->next;
    }
    free(temp);
}

struct Queue* frontL1CToVC() {
    return L1CToVCRear;
}