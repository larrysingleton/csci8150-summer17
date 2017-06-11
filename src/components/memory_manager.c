
#include <main.h>

void processL2CToMEM();


void MEM() {
    processL2CToMEM();
}

void processL2CToMEM() {
    // See if there is anything to process
    struct Queue* frontItem = frontL2CToMem();
    if(frontItem != NULL) {
        int address = atoi(frontItem->address);

        // TODO: introduce the required delay into requests.
        // Send data back to L2C
        printf("MEM to L2C: Data(%s)\n", frontItem->address);

        enqueueMemToL2C(fetchMemoryBlock(address),
                        frontItem->address,
                        frontItem->instruction,
                        WRITE);

        // Remove the processed message.
        dequeueL2CToMem();
    }
}

