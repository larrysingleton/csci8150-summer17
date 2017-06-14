
#include <main.h>

void processMemTemp();
void processL2CToMEM();

void MEM() {
    processMemTemp();
    processL2CToMEM();
}

void processMemTemp() {
    struct node* frontItem = frontMemTemp();
    while(frontItem != NULL) {
        if(frontItem->delay == 0) { // If it has waited enough cycles.
            int address = atoi(frontItem->address);
            if(frontItem->opCode == READ) {
                printf("MEM to L2C: Data(%s)\n", frontItem->address);

                enqueueMemToL2C(fetchMemoryBlock(address),
                                frontItem->address,
                                frontItem->instruction,
                                WRITE);
            } else { // Write request.
                loadMemoryBlock(address, frontItem->data);
            }
            deleteMemTemp(frontItem->address);
        } else { // Still transferring data.
            frontItem->delay--;
        }
        frontItem = frontItem->next;
    }
}

void processL2CToMEM() {
    // See if there is anything to process
    struct Queue* frontItem = frontL2CToMem();
    if(frontItem != NULL) {
        // Put the request in the delay queue.
        insertLastMemTemp(frontItem->data,
                       frontItem->address,
                       frontItem->instruction,
                       frontItem->opCode,
                       16);
        // Remove the processed message.
        dequeueL2CToMem();
    }
}