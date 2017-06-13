#include <main.h>


// Bit 1-valid
// Bit 2-dirty
// Bit 3-LRU
// Bit 4-14 address
// Bit 15-16 cache state

int l1CacheController[256];
int l1CacheControllerExtendedStatus[256];
char* l1DataCache[4][64];

#define l1CacheControlleraddress(i) ((i & 0b0001111111111100) >> 2)

int isInL1Cache(int address) {
    // There are 2048 possible memory addresses, we need to fit them into 256
    int cacheControllerBlock = address % 64; // This will mean there are 8 possible address

    // Check if the record is in the cache.
    if ((l1CacheController[cacheControllerBlock] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) ||
        (l1CacheController[cacheControllerBlock + 64] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) ||
        (l1CacheController[cacheControllerBlock + 128] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) ||
        (l1CacheController[cacheControllerBlock + 192] >> 15 == 1 &&
            l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address)) {
        return HIT;
    }

    // Check if any of them are just empty.
    else if(l1CacheController[cacheControllerBlock] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 64] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 128] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 192] >> 15 == 0) {
        return MISS_I;
    }

    // Check if any of them are populated, but don't need to be written.
    else if(l1CacheController[cacheControllerBlock] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 64] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 128] >> 15 == 0 ||
            l1CacheController[cacheControllerBlock + 192] >> 15 == 0) {
        return MISS_C;
    }

    // Worst case scenario, cache doesn't have it and we we have to write it back.
    else {
        return MISS_D;
    }
}

int victimizeL1(int address) {
    int cacheControllerBlock = address % 64; // This will mean there are 8 possible address

    if((l1CacheController[cacheControllerBlock] >> 12 & 001) != 1) {
        l1DataCache[0][cacheControllerBlock] = NULL;
        return l1CacheController[cacheControllerBlock + 64] >> 2 & 0b00011111111111;
    } else if ((l1CacheController[cacheControllerBlock] >> 12 & 001) != 1) {
        l1DataCache[1][cacheControllerBlock + 64] = NULL;
        return l1CacheController[cacheControllerBlock + 64] >> 2 & 0b00011111111111;
    } else if ((l1CacheController[cacheControllerBlock + 128] >> 12 & 001) != 1) {
        l1DataCache[2][cacheControllerBlock + 128] = NULL;
        return l1CacheController[cacheControllerBlock + 128] >> 2 & 0b00011111111111;
    } else {
        l1DataCache[3][cacheControllerBlock + 192] = NULL;
        return l1CacheController[cacheControllerBlock + 192] >> 2 & 0b00011111111111;
    }
}


char* fetchFromL1Cache(int address) {
    // There are 2048 possible memory addresses, we need to fit them into 256
    int cacheControllerBlock = address % 64; // This will mean there are 8 possible address

    if(l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) {
        return l1DataCache[0][cacheControllerBlock];
    } else if (l1CacheControlleraddress(l1CacheController[cacheControllerBlock + 64]) == address) {
        return l1DataCache[1][cacheControllerBlock];
    } else if (l1CacheControlleraddress(l1CacheController[cacheControllerBlock + 128]) == address) {
        return l1DataCache[2][cacheControllerBlock];
    } else {
        return l1DataCache[3][cacheControllerBlock];
    }
}

void loadL1Cache(int address, char* data) {
    // There are 2048 possible memory addresses, we need to fit them into 256
    int cacheControllerBlock = address % 64; // This will mean there are 8 possible address

    if(l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) {
        l1DataCache[0][cacheControllerBlock] = data;
        if (l1CacheControllerExtendedStatus[cacheControllerBlock] == WR_WAIT_L2D) {
            l1CacheControllerExtendedStatus[cacheControllerBlock] = WR_ALLOC;
        } else if (l1CacheControllerExtendedStatus[cacheControllerBlock] == WR_ALLOC) {
            l1CacheControllerExtendedStatus[cacheControllerBlock] = READY;
        }
    } else if (l1CacheControlleraddress(l1CacheController[cacheControllerBlock + 64]) == address){
        l1DataCache[1][cacheControllerBlock] = data;
        if (l1CacheControllerExtendedStatus[cacheControllerBlock + 64] == WR_WAIT_L2D) {
            l1CacheControllerExtendedStatus[cacheControllerBlock + 64] = WR_ALLOC;
        } else if (l1CacheControllerExtendedStatus[cacheControllerBlock + 64] == WR_ALLOC) {
            l1CacheControllerExtendedStatus[cacheControllerBlock + 64] = READY;
        }
    } else if (l1CacheControlleraddress(l1CacheController[cacheControllerBlock + 128]) == address){
        l1DataCache[2][cacheControllerBlock] = data;
        if (l1CacheControllerExtendedStatus[cacheControllerBlock + 128] == WR_WAIT_L2D) {
            l1CacheControllerExtendedStatus[cacheControllerBlock + 128] = WR_ALLOC;
        } else if (l1CacheControllerExtendedStatus[cacheControllerBlock + 128] == WR_ALLOC) {
            l1CacheControllerExtendedStatus[cacheControllerBlock + 128] = READY;
        }
    } else {
        l1DataCache[3][cacheControllerBlock] = data;
        if (l1CacheControllerExtendedStatus[cacheControllerBlock + 192] == WR_WAIT_L2D) {
            l1CacheControllerExtendedStatus[cacheControllerBlock + 192] = WR_ALLOC;
        } else if (l1CacheControllerExtendedStatus[cacheControllerBlock + 192] == WR_ALLOC) {
            l1CacheControllerExtendedStatus[cacheControllerBlock + 192] = READY;
        }
    }
}

void setL1RowStatus(int address, int cacheState) {
    int cacheControllerBlock = address % 64;

    // Find an empty row.
    if(l1CacheController[cacheControllerBlock] >> 15 != 1) {
        l1CacheController[cacheControllerBlock] = (0b100 << 13) | (address << 2);
        l1CacheControllerExtendedStatus[cacheControllerBlock] = cacheState;
    } else if (l1CacheController[cacheControllerBlock + 64] >> 15 != 1){
        l1CacheController[cacheControllerBlock + 64] = (0b100 << 13) | (address << 2);
        l1CacheControllerExtendedStatus[cacheControllerBlock + 64] = cacheState;
    } else if (l1CacheController[cacheControllerBlock + 128] >> 15 != 1){
        l1CacheController[cacheControllerBlock + 128] = (0b100 << 13) | (address << 2);
        l1CacheControllerExtendedStatus[cacheControllerBlock + 128] = cacheState;
    } else if (l1CacheController[cacheControllerBlock + 192] >> 15 != 1) {
        l1CacheController[cacheControllerBlock + 192] = (0b100 << 13) | (address << 2);
        l1CacheControllerExtendedStatus[cacheControllerBlock + 192] = cacheState;
    }
}

int getL1RowStatus(int address) {
    int cacheControllerBlock = address % 64;

    if(l1CacheControlleraddress(l1CacheController[cacheControllerBlock]) == address) {
        return l1CacheControllerExtendedStatus[cacheControllerBlock];
    } else if (l1CacheControlleraddress(l1CacheController[cacheControllerBlock + 64]) == address) {
        return l1CacheControllerExtendedStatus[cacheControllerBlock + 64];
    } else if (l1CacheControlleraddress(l1CacheController[cacheControllerBlock + 128]) == address) {
        return l1CacheControllerExtendedStatus[cacheControllerBlock + 128];
    } else {
        return l1CacheControllerExtendedStatus[cacheControllerBlock + 192];
    }
}
