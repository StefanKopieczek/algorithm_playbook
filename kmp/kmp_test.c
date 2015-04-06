#include "kmp.h"

#include <stdio.h>

int main(int argc, char **argv) {
    int *matches = kmp("The cat sat on the catamaran", "cat");
    int idx = 0;
    while (matches[idx] != -1) {
        printf("Match at: %d\n", matches[idx++]);
    }
    printf("Done\n");
}
