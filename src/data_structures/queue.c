#include <stdint.h>

// Queues of 8 rows with 8 cells of 8byte instructions (aka each row is 64 bytes).
struct queues {
    int64_t cpuToL1[8][8];
    int64_t L1ToCpu[8][8];
    int64_t L1ToL2[8][8];
    int64_t L2ToL1[8][8];
    int64_t L2ToMem[8][8];
    int64_t MemToL2[8][8];
};