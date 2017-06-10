#ifndef CSCI8150_COMPONENTS_H
#define CSCI8150_COMPONENTS_H

void CPU(int64_t instruction);
void L1();
void L2();
void MEM();
void victimCache();
void writeBuffer();

int preLoadInstructionCache(const char *testFile);
int parseTestFile(FILE *file);


void getDataCacheData(char * address);
void getInstructionCacheData(char * address);

#endif //CSCI8150_COMPONENTS_H
