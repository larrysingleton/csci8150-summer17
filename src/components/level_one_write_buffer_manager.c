#include <main.h>

void levelOneWriteBuffer() {
    struct Queue* frontItem = frontL1CToL1WB();
    if(frontItem != NULL) {
        if(frontItem->data == NULL) { // Read request
            // Print Status
            printf("L1WB To L1C: Data(%s)\n", frontItem->address);
            // Forward data onto CPU.
            enqueueVCToL1C(fetchFromL1WB((int) strtoll(frontItem->address, NULL, 2)),
                           frontItem->address,
                           frontItem->instruction);

        } else { // Write Request
            loadL1WB((int) strtoll(frontItem->address, NULL, 2),
                     frontItem->data
            );
        }

        //remove the message from the queue
        dequeueL1WBToL1C();
    }
}