#include <tests.h>

int test_memoryLoadBlock() {
    long address = 0b00000000001000001;
    char* data = "30013eb5efb1ead13876cd55f13c19f359920f9d5b3cd70c5a6af03c65432145";
    loadMemoryBlock(address, data);
    char* value = fetchMemoryBlock(address);
    if(strcmp(value,"30013eb5efb1ead13876cd55f13c19f359920f9d5b3cd70c5a6af03c65432145") != 0) {
        return ERR;
    } else return OK;
}