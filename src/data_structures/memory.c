#include <main.h>

// Memory is 128 KB linearly indexed.
// so each block aka row will be 64 bytes
// which means 2048 rows

#define row(address) (address >> 6)

char* memory[2048];

void loadMemoryBlock(long address, char* data) {
    memory[row(address)] = data;
}

char* fetchMemoryBlock(long address) {
    return memory[row(address)];
}