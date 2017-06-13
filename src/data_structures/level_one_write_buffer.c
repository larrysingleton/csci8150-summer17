#include <main.h>
// Bit 4 valid bit
// Bit 5-15 address
// Bit 16 lru bit
int l1WBController[2];
char* cache[2];

int isInL1WB(int address) {
    if(((l1WBController[0] >> 1 & 0b011111111111 == address) && l1WBController[0] >> 12 == 1)  ||
       ((l1WBController[1] >> 1 & 0b011111111111 == address) && l1WBController[1] >> 12 == 1)) {
        return 1;
    } else {
        return 0;
    }
}

void evictFromL1WB(int address) {
    if((l1WBController[0] >> 1) == address) {
        l1WBController[0] = 0;
    } else {
        l1WBController[1] = 0;
    }
}

char* fetchFromL1WB(int address) {
    if((l1WBController[0] >> 1) == address) {
        l1WBController[0] = 1 << 12 |address << 1 | 1; // Set LRU bit
        return cache[0];
    } else {
        l1WBController[1] = 1 << 12 | address << 1 | 1; // Set LRU bit
        return cache[1];
    }
}

void loadL1WB(int address, char* data) {
    if((l1WBController[0] & 0b000000000000001) == 0) {
        l1WBController[0] = 1 << 12 | address << 1 | 1;
        cache[0] = data;
    } else {
        l1WBController[1] = 1 << 12 | address << 1 | 1;
        cache[1] = data;
    }
}