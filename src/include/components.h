#ifndef CSCI8150_COMPONENTS_H
#define CSCI8150_COMPONENTS_H

void CPU();
void L1();
void L2();
void MEM();

int preLoadInstructionCache(const char *testFile);

void getDataCacheData(char * address);
void getInstructionCacheData(char * address);

#endif //CSCI8150_COMPONENTS_H
