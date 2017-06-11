
void victimCache() {
    struct Queue* frontItem = frontMemToL2C();
    if(frontItem != NULL) {
        // Print Status
        printf("L2C To L1C: Data(%s)\n", frontItem->address);
        // Forward data onto CPU.
        enqueueL2CToL1C(frontItem->row,
                        frontItem->address,
                        frontItem->instruction);

        printf("L2C To L2D: Data(%s)\n", frontItem->address);

        enqueueL2CToL2D(frontItem->row,
                        frontItem->address,
                        frontItem->instruction);

        //remove the message from the queue
        dequeueMemToL2C();
    }
}