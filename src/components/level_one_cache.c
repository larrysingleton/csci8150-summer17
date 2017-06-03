#include "main.h"

void L1() {
    // Pull a request from the CPU -> L1 queue
    // Call getData with address
    // Put the result on the L1 -> CPU queue.
}

void getData(char* address) { //This address argument will change to whatever datastructure the address will actually be passed in
    if(address) { //starts with 1
        return getInstructionCacheData(address);
    } else {
        return getDataCacheData(address);
    }
}

void getDataCacheData(char * address) { //This address argument will change to whatever datastructure the address will actually be passed in

}

void getInstructionCacheData(char * address) { //This address argument will change to whatever datastructure the address will actually be passed in

}