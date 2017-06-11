#include <main.h>


// Bit 1-valid
// Bit 2-dirty
// Bit 3-LRU
// Bit 4-14 address
// Bit 15-16 cache state
int l1CacheController[256];
int l1CacheControllerExtendedStatus[256];
char* l1DataCache[4][64];

#define l1CacheControlleraddress(i) (i & 0b0001111111111100)

int isInL1Cache(int address) {
    // There are 2048 possible memory addresses, we need to fit them into 256
    int cacheControllerBlock = address % 256; // This will mean there are 8 possible address

    // Check if the record is in the cache.
    if ((l1CacheController[cacheControllerBlock] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) ||
        (l1CacheController[cacheControllerBlock + 1] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) ||
        (l1CacheController[cacheControllerBlock + 2] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) ||
        (l1CacheController[cacheControllerBlock + 3] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address)) {
        return HIT;
    }

    // Check if any of them are just empty.
    else if(l1CacheController[cacheControllerBlock] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 1] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 2] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 3] >> 15 == 0) {
        return MISS_I;
    }

    // Check if any of them are populated, but don't need to be written.
    else if(l1CacheController[cacheControllerBlock] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 1] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 2] >> 15 == 0 ||
        l1CacheController[cacheControllerBlock + 3] >> 15 == 0) {
        return MISS_C;
    }

    // Worst case scenario, cache doesn't have it and we we have to write it back.
    else {
        return MISS_D;
    }
}

void victimizeL1(int address) {

}

void setL1RowWaitingL2(int address) {

}