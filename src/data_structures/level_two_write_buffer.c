#include <main.h>
// Bit 5-15 address
// Bit 16 lru bit
int l2wbController[2];
char* cache[2];

int isInL2WB(int address) {
    if(l2wbController[0] >> 1 == address || l2wbController[1] >> 1 == address) {
        return 1;
    } else {
        return 0;
    }
}

void evictFromL2WB(int address) {
    if((l2wbController[0] >> 1) == address) {
        l2wbController[0] = 0;
    } else {
        l2wbController[1] = 0;
    }
}

char* fetchFromL2WB(int address) {
    if((l2wbController[0] >> 1) == address) {
        l2wbController[0] = address << 1 | 1; // Set LRU bit
        return cache[0];
    } else {
        l2wbController[1] = address << 1 | 1; // Set LRU bit
        return cache[1];
    }
}

void loadL2WB(int address, char* data) {
    if((l2wbController[0] & 0b000000000000001) == 0) {
        l2wbController[0] = address << 1 | 1;
        cache[0] = data;
    } else {
        l2wbController[1] = address << 1 | 1;
        cache[1] = data;
    }
}