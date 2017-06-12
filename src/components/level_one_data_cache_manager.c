#include <main.h>

void levelOneDataCacheManager() {
    struct Queue* frontItem = frontL1CToL1D();
    if(frontItem != NULL) {
        if(frontItem->opCode == READ) { // Read request
            // Print Status
            printf("L1D To L1C: Data(%s)\n", frontItem->address);
            // Forward data onto CPU.
            enqueueL1DToL1C(fetchFromL1Cache((int) strtoll(frontItem->address, NULL, 2)),
                           frontItem->address,
                           frontItem->instruction,
                           WRITE);

        } else { // Write Request
            loadL1Cache((int) strtoll(frontItem->address, NULL, 2),
                     frontItem->data
            );
        }

        //remove the message from the queue
        dequeueL1CToL1D();
    }
}