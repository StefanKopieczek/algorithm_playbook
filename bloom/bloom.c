#include "bloom.h"

#include <stdlib.h>

BLOOM *new_bloom(int size, BLOOM_HASH hash, int num_hashes) {
    BLOOM *bloom = malloc(sizeof(BLOOM));
    bloom->bits = new_bitfield(size);
    bloom->hash = hash;
    bloom->num_hashes = num_hashes;
    bloom->num_elements = 0;

    return bloom;
}

void free_bloom(BLOOM *bloom) {
    free_bitfield(bloom->bits);
    free(bloom);
}

uint32_t standard_hash(BLOOM_MEMBER item, int key) {
    return murmur3_32(item.data, item.size, key);
}

int bloom_add(BLOOM *b, BLOOM_MEMBER item) {
    int idx;
    unsigned char changed = 0;
    for (idx = 0; idx < b->num_hashes; idx++) {
        uint32_t hash = b->hash(item, idx) % b->bits->size_bits;
        changed &= bitfield_set(b->bits, hash, 1);
    }

    return changed;
}

int bloom_add_all(BLOOM *b, BLOOM_MEMBER *items, int num_items) {
    int idx = 0;
    unsigned char changed = 0;
    for (idx = 0; idx < num_items; idx++) {
        changed &= bloom_add(b, items[idx]);
    }

    return changed;
}

unsigned char bloom_contains(BLOOM *b, BLOOM_MEMBER item) {
    int idx;
    unsigned char changed = 0;
    for (idx = 0; idx < b->num_hashes; idx++) {
        uint32_t hash = b->hash(item, idx) % b->bits->size_bits;
        if (bitfield_get(b->bits, hash) == 0)
            return 0;
    }

    return 1;
}
