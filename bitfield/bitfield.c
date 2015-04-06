#include "bitfield.h"

#include <assert.h>
#include <stdlib.h>

BITFIELD *new_bitfield(int size_bits) {
    BITFIELD *bitfield = calloc(1, sizeof(BITFIELD));
    bitfield->size_bits = size_bits;

    int size_bytes = size_bits / 8;
    if ((size_bits % 8) != 0)
        size_bytes++;

    bitfield->data = malloc(size_bytes);
    return bitfield;
}

void free_bitfield(BITFIELD *bitfield) {
    free(bitfield->data);
    free(bitfield);
}

unsigned char bitfield_set(BITFIELD *bitfield, int idx, unsigned char newval) {
    assert(newval == 0 || newval == 1);
    int byte_idx = idx / 8;
    unsigned char shift = ((8 - (idx % 8)) - 1);
    unsigned char mask = 1 << shift;
    unsigned char oldval = (bitfield->data[byte_idx] & mask) >> shift;

    if (newval) {
        bitfield->data[byte_idx] |= mask;
    }
    else {
        bitfield->data[byte_idx] &= ~mask;
    }

    return (oldval != newval);
}

unsigned char bitfield_get(BITFIELD *bitfield, int idx) {
    int byte_idx = idx / 8;
    unsigned char shift = ((8 - (idx % 8)) - 1);
    unsigned char mask = 1 << shift;

    return (bitfield->data[byte_idx] & mask) >> shift;
}
