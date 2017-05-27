#ifndef CSCI8150_DATA_STRUCTURES_H_H
#define CSCI8150_DATA_STRUCTURES_H_H

// Each row is 64 bytes, we allocate 64 rows
// for a total of 512 byte instruction cache
#define INS_CACHE_ROWS 64 //64 rows in the instruction cache.
#define INS_CACHE_CELLS 8 //8 Instructions per row.
#define INS_SIZE_IN_BYTES 8

typedef unsigned char instruction[INS_SIZE_IN_BYTES]; // An instruction is made up of 8 bytes

#endif //CSCI8150_DATA_STRUCTURES_H_H