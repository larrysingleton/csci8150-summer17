#include <tests.h>

int test_memoryLoadByte() {
    int address = 0b0000000000000000;
    loadMemoryByte(address, 'c');
    char value = fetchMemoryByte(address);
    if(value != 'c') {
        return ERR;
    } else return OK;
}