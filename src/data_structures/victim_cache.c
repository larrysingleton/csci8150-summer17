// Bit 5-15 address
// Bit 16 lru bit
int l1VCController[2];
char* cache[2];

int isInVC(int address) {
    if(l1VCController[0] >> 1 == address || l1VCController[1] >> 1 == address) {
        return 1;
    } else {
        return 0;
    }
}

void loadVC(int address, char* data) {
    if((l1VCController[0] & 0b000000000000001) == 0) {
        l1VCController[0] = address << 1 | 1;
        cache[0] = data;
    } else {
        l1VCController[1] = address << 1 | 1;
        cache[1] = data;
    }
}

char* fetchFromVC(int address) {
    if((l1VCController[0] >> 1) == address) {
        l1VCController[0] = address << 1 | 1; // Set LRU bit
        return cache[0];
    } else {
        l1VCController[1] = address << 1 | 1; // Set LRU bit
        return cache[1];
    }
}

void evictFromVC(int address) {
    if((l1VCController[0] >> 1) == address) {
        l1VCController[0] = 0;
    } else {
        l1VCController[1] = 0;
    }
}