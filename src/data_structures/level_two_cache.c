#include <main.h>


// Bit 1-valid
// Bit 2-dirty
// Bit 3-LRU
// Bit 4-14 address
// Bit 15-16 cache state
int l2CacheController[812];
int l2CacheControllerExtendedStatus[409];
char* l2DataCache[2][409];

#define l1CacheControlleraddress(i) (i & 0b0001111111111100)

int isInL2Cache(int address) {
    // There are 2048 possible memory addresses, we need to fit them into 256
    int cacheControllerBlock = address % 812; // This will mean there are 8 possible address

    // Check if the record is in the cache.
    if ((l2CacheController[cacheControllerBlock] >> 15 == 1 &&
         l1CacheControlleraddress(l2CacheController[cacheControllerBlock]) == address) ||
        (l2CacheController[cacheControllerBlock + 1] >> 15 == 1 &&
         l1CacheControlleraddress(l2CacheController[cacheControllerBlock]) == address)) {
        return HIT;
    }

        // Check if any of them are just empty.
    else if(l2CacheController[cacheControllerBlock] >> 15 == 0 ||
            l2CacheController[cacheControllerBlock + 1] >> 15 == 0) {
        return MISS_I;
    }

        // Check if any of them are populated, but don't need to be written.
    else if(l2CacheController[cacheControllerBlock] >> 15 == 0 ||
            l2CacheController[cacheControllerBlock + 1] >> 15 == 0) {
        return MISS_C;
    }

        // Worst case scenario, cache doesn't have it and we we have to write it back.
    else {
        return MISS_D;
    }
}

void setL2RowWaiting(int address) {

}