#include <tests.h>

int test_registerFile() {
    char* test = "test char";
    int registerLocation = loadRegister(test);
    if(registerLocation == -1) {
        return ERR;
    }
    if(strcmp(fetchRegister(registerLocation), "test char") != 0) {
        return ERR;
    }
    return OK;
}