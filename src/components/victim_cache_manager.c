#include <main.h>


void victimCache() {
    struct Queue* frontItem = frontL1CToVC();
    if(frontItem != NULL) {
        // Print Status
        printf("VC To L1C: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueVCToL1C(frontItem->row,
                       frontItem->address,
                       frontItem->instruction);

        //remove the message from the queue
        dequeueL1CToVC();
    }
}