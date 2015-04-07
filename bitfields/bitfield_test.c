#include "bitfields.h"

#include <stdio.h>

#define PASS 1
#define FAIL 0

typedef struct test {
    const char *name;
    int (*fn) (BITFIELD *b);
} TEST;

int do_test(TEST *test);
int test_init(BITFIELD *b);
int test_set_get1(BITFIELD *b);
int test_set_get2(BITFIELD *b);
int test_set_get3(BITFIELD *b);
int test_set_get4(BITFIELD *b);
int test_set_get5(BITFIELD *b);
int test_set_return1(BITFIELD *b);
int test_set_return2(BITFIELD *b);
int test_set_return3(BITFIELD *b);
int test_set_return4(BITFIELD *b);

TEST TESTS[] = {
    {"init", *test_init},
    {"set_get1", *test_set_get1},
    {"set_get2", *test_set_get1},
    {"set_get3", *test_set_get3},
    {"set_get4", *test_set_get4},
    {"set_get5", *test_set_get5},
    {"set_return1", *test_set_return1},
    {"set_return2", *test_set_return2},
    {"set_return3", *test_set_return3},
    {"set_return4", *test_set_return4},
};

int NUM_TESTS = sizeof(TESTS) / sizeof(TEST);

int main(int argc, char **argv) {
    int idx;
    int successes = 0;
    for (idx = 0; idx < NUM_TESTS; idx++) {
        int res = do_test(&TESTS[idx]);
        if (res == PASS)
            successes++;
    }

    printf("\n%d tests of %d passed: %.2f%%\n",
           successes,
           NUM_TESTS,
           (100 * (float)successes / NUM_TESTS));

    if (successes != NUM_TESTS)
        return 1;

    return 0;
}

int do_test(TEST *test) {
    BITFIELD *bf = new_bitfield(17);
    int result = (test->fn)(bf);
    free_bitfield(bf);

    if (result == PASS)
        printf("Test '%s' passed\n", test->name);
    else
        printf("Test '%s' FAILED\n", test->name);

    return result;
}

int test_init(BITFIELD *bitfield) {
    int idx = 0;
    for (idx = 0; idx < bitfield->size_bits; idx++) {
        if (bitfield_get(bitfield, idx))
            return FAIL;
    }

    return PASS;
}

int test_set_get1(BITFIELD *bitfield) {
    bitfield_set(bitfield, 3, 1);
    return (bitfield_get(bitfield, 3) == 1);
}

int test_set_get2(BITFIELD *bitfield) {
    bitfield_set(bitfield, 3, 1);
    bitfield_set(bitfield, 3, 0);
    return (bitfield_get(bitfield, 3) == 0);
}

int test_set_get3(BITFIELD *bitfield) {
    bitfield_set(bitfield, 0, 1);
    char res = bitfield_get(bitfield, 0);
    return (bitfield_get(bitfield, 0) == 1);
}

int test_set_get4(BITFIELD *bitfield) {
    bitfield_set(bitfield, 8, 1);
    return (bitfield_get(bitfield, 8) == 1);
}

int test_set_get5(BITFIELD *bitfield) {
    bitfield_set(bitfield, 15, 1);
    return (bitfield_get(bitfield, 15) == 1);
}

int test_set_return1(BITFIELD *bitfield) {
    return (bitfield_set(bitfield, 2, 0) == 0);
}

int test_set_return2(BITFIELD *bitfield) {
    return (bitfield_set(bitfield, 2, 1) == 1);
}

int test_set_return3(BITFIELD *bitfield) {
    bitfield_set(bitfield, 2, 1);
    return (bitfield_set(bitfield, 2, 1) == 0);
}

int test_set_return4(BITFIELD *bitfield) {
    bitfield_set(bitfield, 2, 1);
    return (bitfield_set(bitfield, 2, 0) == 1);
}
