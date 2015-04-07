#ifndef SMK_BLOOM
#define SMK_BLOOM

#include "bitfields.h"
#include <stdint.h>

typedef struct bloom_member {
    void *data;
    int size;
} BLOOM_MEMBER;

typedef uint32_t (*BLOOM_HASH) (BLOOM_MEMBER item, int seed);

typedef struct bloom {
    BITFIELD *bits;
    BLOOM_HASH hash;
    int num_hashes;
    int num_elements;
} BLOOM;

BLOOM *new_bloom(int size, BLOOM_HASH hash, int num_hashes);
void free_bloom(BLOOM *b);
uint32_t standard_hash(BLOOM_MEMBER item, int seed);
int bloom_add(BLOOM *b, BLOOM_MEMBER item);
int bloom_add_all(BLOOM *b, BLOOM_MEMBER *items, int num_items);
unsigned char bloom_contains(BLOOM *b, BLOOM_MEMBER item);

#endif
