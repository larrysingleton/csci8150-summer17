#include <main.h>
// Bit 5-15 address
// Bit 16 lru bit
int l1WBController[2];
char* cache[2];

int isInL2WB(int address) {
    if(l1WBController[0] >> 1 == address || l1WBController[1] >> 1 == address) {
        return 1;
    } else {
        return 0;
    }
}

void loadL2WB(int address, char* data) {
    if((l1WBController[0] & 0b000000000000001) == 0) {
        l1WBController[0] = address << 1 | 1;
        cache[0] = data;
    } else {
        l1WBController[1] = address << 1 | 1;
        cache[1] = data;
    }
}