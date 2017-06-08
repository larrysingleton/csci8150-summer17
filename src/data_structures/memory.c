// Memory is 128 KB linearly indexed.
// so each block aka row will be 64 bytes
// which means 2048 rows
//
char memory[2048][64];

char fetchMemoryByte(int address) {
    int row = address >> 5;
    int cell = address << 11;
    return memory[row][cell];
}

void loadMemoryByte(int address, char data) {
    int row = address >> 5;
    int cell = address << 11;
    memory[row][cell] = data;
}