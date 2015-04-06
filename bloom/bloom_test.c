#include "bloom.h"

#include <stdio.h>

#define PASS 1
#define FAIL 0

typedef struct test {
    const char *name;
    int (*fn) (BLOOM *b);
} TEST;

int do_test(TEST *test);
int test_init(BLOOM *b);

TEST TESTS[] = {
    {"init", &test_init},
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
    BLOOM *b = new_bloom(100, &standard_hash, 30);
    int result = (test->fn)(b);
    free_bloom(b);

    if (result == PASS)
        printf("Test '%s' passed\n", test->name);
    else
        printf("Test '%s' FAILED\n", test->name);

    return result;
}

int test_init(BLOOM *b) {
    int idx = 0;
    for (idx = 0; idx < 100; idx++) {
        BLOOM_MEMBER m = {&idx, sizeof(int)};
        if (bloom_contains(b, m))
            return FAIL;
    }

    return PASS;
}
