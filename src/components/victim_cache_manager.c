#include <main.h>


void victimCache() {
    struct Queue* frontItem = frontL1CToVC();
    if(frontItem != NULL) {
        if(frontItem->row == NULL) { // Read request
            // Print Status
            printf("VC To L1C: Data(%s)\n", frontItem->address);
            // Forward data onto CPU.
            enqueueVCToL1C(fetchFromVC(atoi(frontItem->address)),
                           frontItem->address,
                           frontItem->instruction);

        } else { // Write Request
            loadVC((int) strtoll(frontItem->address, NULL, 2),
                   frontItem->row
            );
        }

        //remove the message from the queue
        dequeueL1CToVC();
    }
}