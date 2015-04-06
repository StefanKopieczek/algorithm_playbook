#include "heap.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define PARENT(idx)      idx / 2
#define LEFT_CHILD(idx)  2 * idx
#define RIGHT_CHILD(idx) 2 * idx + 1

#define INFINITY         2147483647

static void bubble_up(HEAP *heap, int idx);
static void bubble_down(HEAP *heap, int idx);
static int _bubble_up(HEAP *heap, int idx);
static int _bubble_down(HEAP *heap, int idx);
static void _dump(HEAP *h);

HEAP *init(int max_size) {
    HEAP *heap = malloc(sizeof(HEAP));
    heap->data = malloc(sizeof(int) * max_size);
    heap->max_size = max_size;
    heap->size = 0;
    return heap;
}

HEAP *make_heap(int *values, int length) {
    HEAP *heap = malloc(sizeof(HEAP));
    heap->data = values;
    heap->max_size = heap->size = length;

    int idx;
    for (idx = length / 2; idx >= 0; idx--) {
        bubble_down(heap, idx);
    }

    return heap;
}

int add(HEAP *heap, int value) {
    printf("Add %d:\n", value);
    _dump(heap);
    if (heap->size < heap->max_size) {
        int new_idx = heap->size;
        heap->size++;
        heap->data[new_idx] = value;
        bubble_up(heap, new_idx);
    }
    else {
        // Unable to add new element due to lack of space.
        // Return an error.
        return -1;
    }
    _dump(heap);
    printf("%d added\n", value);
}

int add_all(HEAP *heap, int *values, int length) {
    int idx;
    for (idx = 0; idx < length; idx++) {
        add(heap, values[idx]);
    }
}

int peek(HEAP *heap) {
    return heap->data[0];
}

int pop(HEAP *heap) {
    int result = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    if (heap->size > 0)
        bubble_down(heap, 0);

    return result;
}

static void bubble_up(HEAP *heap, int idx) {
    while ((idx = _bubble_up(heap, idx)) > 0);
}

static int _bubble_up(HEAP *heap, int idx) {
    // Ensure the idx is within the heap.
    assert(idx >= 0);
    assert(idx < heap->size);

    // The root can't bubble up any further, so we're done.
    if (idx == 0)
        return -1;

    int value = heap->data[idx];
    int parent = PARENT(idx);
    int parent_val = heap->data[parent];

    if (value < parent_val) {
        // The child belongs above the parent, so switch them.
        // Return the new index so bubble-up can continue.
        heap->data[parent] = value;
        heap->data[idx] = parent_val;
        return parent;
    }
    else {
        // The child does belong below the parent, so just return -1 to
        // indicate that no more bubbling up is needed.
        return -1;
    }
}

static void bubble_down(HEAP *heap, int idx) {
    while ((idx = _bubble_down(heap, idx)) > 0);
}

static int _bubble_down(HEAP *heap, int idx) {
    // Ensure the idx is within the heap.
    assert(idx >= 0);
    assert(idx < heap->size);

    int value = heap->data[idx];
    int lchild = LEFT_CHILD(idx);
    int rchild = RIGHT_CHILD(idx);

    int lchild_val;
    if (lchild < heap->size)
        lchild_val = heap->data[lchild];
    else
        lchild_val = INFINITY;

    int rchild_val;
    if (rchild < heap->size)
        rchild_val = heap->data[rchild];
    else
        rchild_val = INFINITY;

    if (value > lchild_val) {
        // The left child belongs above the current node, so switch them
        // and return the new index of the node, so bubbling can continue.
        heap->data[lchild] = value;
        heap->data[idx] = lchild_val;
        return lchild;
    }
    else if (value > rchild_val) {
        // The right child belongs above the current node, so switch them
        // and return the new index of the node, so bubbling can continue.
        heap->data[rchild] = value;
        heap->data[idx] = rchild_val;
        return rchild;
    }

    // Neither the left nor right child was bigger than the current node,
    // so bubbling can stop.
    return -1;
}

static void _dump(HEAP *h) {
    printf("[");
    int idx;
    for (idx = 0; idx < h->size; idx++) {
        printf("%d, ", h->data[idx]);
    }
    printf("]\n");
}
