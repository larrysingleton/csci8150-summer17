#include <main.h>

int main() {
    //TODO: load instruction cache from file in arguments

    // Keeps track of time, 1 unit of time equals 1 clock cylce.
    int time = 1;
    //execute CPU cycles until pipline
    while(1) {
        CPU();
        L1();
        L2();
        MEM();
        time++;
    }
}