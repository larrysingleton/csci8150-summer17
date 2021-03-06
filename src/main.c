#include <main.h>

int inProgress();

int main(int argc, char *argv[]) {
    int pc = 0;   // Keeps track of time, 1 unit of time equals 1 clock cycle.

    printf("\n Memory Subsystem starting...\n");

    if (argc!=2) {
        printf("\nMissing test case argument");
        printf("\nUsage: %s [test1 | test2 | test3]", basename(argv[0]));
        return ERR;
    }

    if (preLoadInstructionCache(argv[1]) != OK) {
        return ERR;
    }


    //execute CPU cycles until pipline is empty
    do {
        if(DEBUG) printf("Beginning clock cycle %d\n", pc);
        CPU(pc);
        L1();
        L2();
        MEM();
        pc++;
    } while (inProgress() != ERR);
}

int inProgress() {
    if( frontCPUToL1C() != NULL ||
        frontL1CToCPU() != NULL ||
        frontL1DToL1C() != NULL ||
        frontL1CToL1D() != NULL ||
        frontL1CToVC() != NULL ||
        frontVCToL1C() != NULL ||
        frontL1CToL1WB() != NULL ||
        frontL1WBToL1C() != NULL ||
        frontL1CToL2C() != NULL ||
        frontL2CToL1C() != NULL ||
        frontL2DToL2C() != NULL ||
        frontL2WBToL2C() != NULL ||
        frontL2CToL2WB() != NULL ||
        frontL2CToL2D() != NULL ||
        frontL2CToMem() != NULL ||
        frontMemToL2C() != NULL ||
        frontL1Temp() != NULL ||
        frontMemTemp() != NULL) {
        return OK;
    }
    return ERR;
}