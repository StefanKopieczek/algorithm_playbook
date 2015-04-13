#include "rabin_karp.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *text = "I am a banana";
    char *s = "ana";
    int *matches = rabin_karp_match(text, s);
    int idx = 0;
    while (matches[idx] != -1) {
        printf("Match at %d\n", matches[idx]);
        idx ++;
    }

    free(matches);
    printf("Done!\n");
    return 0;
}
