#include <main.h>

struct Queue* VCToL1CFront;
struct Queue* VCToL1CRear;

void enqueueVCToL1C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(VCToL1CFront == NULL && VCToL1CRear == NULL) {
        VCToL1CFront = VCToL1CRear = temp;
    }
    VCToL1CRear->next = temp;
    VCToL1CRear = temp;
}

void dequeueVCToL1C() {
    struct Queue* temp = VCToL1CFront;
    if(VCToL1CFront == NULL) {
        return;
    }
    if(VCToL1CFront == VCToL1CRear) {
        VCToL1CFront = VCToL1CRear = NULL;
    }
    else {
        VCToL1CFront = VCToL1CFront->next;
    }
    free(temp);
}

struct Queue* frontVCToL1C() {
    return VCToL1CFront;
}
