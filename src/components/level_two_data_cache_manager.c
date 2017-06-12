#include <main.h>

void levelTwoDataCacheManager() {
    struct Queue* frontItem = frontL2CToL2D();
    if(frontItem != NULL) {
        if(frontItem->opCode == READ) { // Read request
            // Print Status
            printf("L2D To L2C: Data(%s)\n", frontItem->address);
            // Forward data onto CPU.
            enqueueL2DToL2C(fetchFromL2Cache((int) strtoll(frontItem->address, NULL, 2)),
                           frontItem->address,
                           frontItem->instruction,
                            WRITE);

        } else { // Write Request
            loadL2Cache((int) strtoll(frontItem->address, NULL, 2),
                     frontItem->data
            );
        }

        //remove the message from the queue
        dequeueL2CToL2D();
    }
}