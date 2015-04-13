#include "rabin_karp.h"

#include <stdlib.h>
#include <stdio.h>

#define PASS 1
#define FAIL 0

typedef struct test {
    const char *name;
    int (*fn) ();
} TEST;

static int do_test(TEST *test);
static int test_single_1();
static int test_multiple_1();
static int test_multiple_2();

static TEST TESTS[] = {
    {"single1", &test_single_1},
    {"multiple1", &test_multiple_1},
    {"multiple2", &test_multiple_2}
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

static int test_single_1() {
    char *text = "I am a banana";
    char *s = "ana";
    int *matches = rabin_karp_match(text, s);

    int result;
    if (matches[0] == 8 && matches[1] == 10 && matches[2] == -1)
        result = PASS;
    else
        result = FAIL;

    free(matches);
    return result;
}

static int test_multiple_1() {
    char *text = "I am a banana";
    char *s[] = {"ana", "am"};
    int *matches = rabin_karp_multi_match(text, s, 2);

    int result;

    if (matches[0] == 2 && matches[1] == 8 && matches[2] == 10 && matches[3] == -1)
        result = PASS;
    else
        result = FAIL;

    free(matches);
    return result;
}

static int test_multiple_2() {
    char *text = "I am a banana";
    char *s[] = {"ana", "ban"};
    int *matches = rabin_karp_multi_match(text, s, 2);

    int result;

    if (matches[0] == 7 && matches[1] == 8 && matches[2] == 10 && matches[3] == -1)
        result = PASS;
    else
        result = FAIL;

    free(matches);
    return result;
}

static int do_test(TEST *test) {
    int result = (test->fn)();

    if (result == PASS)
        printf("Test '%s' passed\n", test->name);
    else
        printf("Test '%s' FAILED\n", test->name);

    return result;
}
