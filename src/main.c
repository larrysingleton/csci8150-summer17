#include <main.h>

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
    while(1) {
        int64_t instruction = fetchInstruction(pc);
        if(instruction == ERR) { // Invalid instruction, means we have performed all the instructions.
            // TODO: add checks to make sure all queues are empty.
            break;
        }
        if(DEBUG) printf("Beginning clock cycle %d\n", pc);
        CPU(instruction);
        L1();
        L2();
        MEM();
        pc++;
    }
}