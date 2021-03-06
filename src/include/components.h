#ifndef CSCI8150_COMPONENTS_H
#define CSCI8150_COMPONENTS_H

void CPU(int pc);
void L1();
void L2();
void MEM();
void victimCache();
void levelOneDataCacheManager();
void levelOneWriteBuffer();
void levelTwoWriteBuffer();
void levelTwoDataCacheManager();

int preLoadInstructionCache(const char *testFile);
int parseTestFile(FILE *file);


void getDataCacheData(char * address);
void getInstructionCacheData(char * address);

#endif //CSCI8150_COMPONENTS_H
