#ifndef SMK_BITFIELD
#define SMK_BITFIELD

typedef struct bitfield {
    unsigned char *data;
    int size_bits;
} BITFIELD;

BITFIELD *new_bitfield(int size_bits);
void free_bitfield(BITFIELD *b);
unsigned char bitfield_set(BITFIELD *bitfield, int idx, unsigned char newval);
unsigned char bitfield_get(BITFIELD *bitfield, int idx);

#endif
