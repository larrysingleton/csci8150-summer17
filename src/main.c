#include "main.h"

int main(int argc, char *argv[]) {
    int time = 1;   // Keeps track of time, 1 unit of time equals 1 clock cycle.

    printf("\n Memory Subsystem starting...\n");

    if (argc!=2) {
        printf("\nMissing test case argument");
        printf("\nUsage: %s [test1 | test2 | test3]", basename(argv[0]));
        return ERR;
    }

    if (preLoadInstructionCache(argv[1]) != OK) {
        return ERR;
    }

    //execute CPU cycles until pipline
    while(time) {

        CPU();
        L1();
        L2();
        MEM();

        time++;
    }
}