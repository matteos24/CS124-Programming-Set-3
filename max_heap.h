// max_heap.h
#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <limits.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity);
void insert(MaxHeap* heap, int key);
int extractMax(MaxHeap* heap);
int peekMax(MaxHeap* heap);
void freeHeap(MaxHeap* heap);

#endif // MAX_HEAP_H