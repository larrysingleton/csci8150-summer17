#include <main.h>

struct Queue* CPUToL1CFront;
struct Queue* CPUToL1CRear;

void enqueueCPUToL1C(char* data, char* address, int64_t instruction) {
    struct Queue* temp = (struct Queue*) malloc(sizeof(struct Queue));
    temp->row = data;
    temp->address = address;
    temp->instruction = instruction;
    temp->next = NULL;
    if(CPUToL1CFront == NULL) {
        CPUToL1CFront = temp;
    } else {
        CPUToL1CRear->next = temp;
        CPUToL1CRear = temp;
    }
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
        CPUToL1CFront = CPUToL1CRear->next;
    }
    free(temp);
}

struct Queue* frontCPUToL1C() {
    return CPUToL1CFront;
}

