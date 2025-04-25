// max_heap.h
#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <limits.h>

#include <stdlib.h>
typedef struct {
  int64_t *arr;
  int64_t size;
  int64_t capacity;
} MaxHeap;

MaxHeap *createHeap(int64_t capacity);
void swap(int64_t *x, int64_t *y);
int64_t parent(int64_t i);
int64_t leftChild(int64_t i);
int64_t rightChild(int64_t i);
void heapifyDown(MaxHeap *heap, int64_t i);
void heapifyUp(MaxHeap *heap, int64_t i);
void insert(MaxHeap *heap, int64_t key);
int64_t extractMax(MaxHeap *heap);
int64_t peekMax(MaxHeap *heap);
void freeHeap(MaxHeap *heap);

#endif // MAX_HEAP_H
