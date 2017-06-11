#include <main.h>

void levelTwoWriteBuffer() {
    struct Queue* frontItem = frontL2CToL2WB();
    if(frontItem != NULL) {
        if(frontItem->row == NULL) { // Read request
            // Print Status
            printf("L2WB To L2C: Data(%s)\n", frontItem->address);
            // Forward data onto CPU.
            enqueueVCToL1C(fetchFromL2WB((int) strtoll(frontItem->address, NULL, 2)),
                           frontItem->address,
                           frontItem->instruction);

        } else { // Write Request
            loadL2WB((int) strtoll(frontItem->address, NULL, 2),
                     frontItem->row
            );
        }

        //remove the message from the queue
        dequeueL2WBToL2C();
    }
}