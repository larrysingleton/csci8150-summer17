#include <main.h>

// Memory is 128 KB linearly indexed.
// so each block aka row will be 64 bytes
// which means 2048 rows
//

#define row(address) (address >> 5)
#define cell(address) (address & 0b0000000000011111)

char memory[2048][blockSizeInBytes];

char fetchMemoryByte(int address) {
    return memory[row(address)][cell(address)];
}

void loadMemoryByte(int address, char data) {
    memory[row(address)][cell(address)] = data;
}

void loadMemoryBlock(int address, char data[blockSizeInBytes]) {
    for(int i = 0; i < blockSizeInBytes; i++) {
        loadMemoryByte(address++, data[i]);
    }
}

char* fetchMemoryBlock(int address) {
    // We want to fetch the whole block
    // every time, no matter the addresss
    // This strips the offset.
    char data[blockSizeInBytes];
    address = row(address) << 5;
    for(int i = 0; i < blockSizeInBytes; i++) {
        data[i] = fetchMemoryByte(address);
    }
    return data;
}