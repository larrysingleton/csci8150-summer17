#include <main.h>

struct Queue* CPUToL1CFront;
struct Queue* CPUToL1CRear;

void enqueueCPUToL1C(char* data, char* address, int64_t instruction, int opCode) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->data = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    temp->opCode = opCode;
    if(CPUToL1CFront == NULL && CPUToL1CRear == NULL) {
        CPUToL1CFront = CPUToL1CRear = temp;
    }
    CPUToL1CRear->next = temp;
    CPUToL1CRear = temp;
}

void dequeueCPUToL1C() {
    struct Queue* temp = CPUToL1CFront;
    if(CPUToL1CFront == NULL) {
        return;
    }
    if(CPUToL1CFront == CPUToL1CRear) {
        CPUToL1CFront = CPUToL1CRear = NULL;
    }
    else {
        CPUToL1CFront = CPUToL1CFront->next;
    }
    free(temp);
}

struct Queue* frontCPUToL1C() {
    return CPUToL1CFront;
}

