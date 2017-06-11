#include <main.h>

// Memory is 128 KB linearly indexed.
// so each block aka data will be 64 bytes
// which means 2048 rows

#define row(address) (address & 0b0000011111111111)

char* memory[2048];

void loadMemoryBlock(int address, char* data) {
    memory[row(address)] = data;
}

char* fetchMemoryBlock(int address) {
    return memory[row(address)];
}