#ifndef _SMK_HEAP
#define _SMK_HEAP

typedef struct heap {
    int *data;
    int size;
    int max_size;
} HEAP;

HEAP *init(int max_size);
void heap_free(HEAP *heap);
HEAP *make_heap(int *values, int length);
int add(HEAP *heap, int value);
int add_all(HEAP *heap, int *values, int length);
int peek(HEAP *heap);
int pop(HEAP *heap);

#endif
