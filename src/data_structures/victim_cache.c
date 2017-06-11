// Bit 5-15 address
// Bit 16 lru bit
int vcController[2];
char* cache[2];

int isInVC(int address) {
    if(vcController[0] >> 1 == address || vcController[1] >> 1 == address) {
        return 1;
    } else {
        return 0;
    }
}

loadVC(int address, char* data) {
    if(vcController[0] & 0b000000000000001 == 0) {
        vcController[0] = address << 1 | 1;
        cache[0] = data;
    } else {
        vcController[1] = address << 1 | 1;
        cache[1] = data;
    }
}