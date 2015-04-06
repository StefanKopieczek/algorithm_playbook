#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int data[] = { 17, 3, 25, 12, 2, 5, 42, 7, 9, 10 };

    HEAP *h = init(10);
    int idx = 0;
    for (idx = 0; idx < 10; idx++) {
        add(h, data[idx]);
    }

    for (idx = 0; idx < 10; idx++) {
        printf("%d\n", pop(h));
    }

    free(h->data);
    free(h);
    printf("\n\n\n");

    HEAP *h2 = make_heap(data, 10);
    while (h2->size > 0) {
        printf("%d\n", pop(h2));
    }
    free(h2);
}
