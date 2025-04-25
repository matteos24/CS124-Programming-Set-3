#include "max_heap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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

MaxHeap *createHeap(int64_t capacity) {
  MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
  heap->size = 0;
  heap->capacity = capacity;
  heap->arr = (int64_t *)malloc(capacity * sizeof(int64_t));
  return heap;
}

void swap(int64_t *x, int64_t *y) {
  int64_t temp = *x;
  *x = *y;
  *y = temp;
}

int64_t parent(int64_t i) { return (i - 1) / 2; }
int64_t leftChild(int64_t i) { return 2 * i + 1; }
int64_t rightChild(int64_t i) { return 2 * i + 2; }

void heapifyUp(MaxHeap *heap, int64_t i) {
  while (i != 0 && heap->arr[parent(i)] < heap->arr[i]) {
    swap(&heap->arr[parent(i)], &heap->arr[i]);
    i = parent(i);
  }
}

void heapifyDown(MaxHeap *heap, int64_t i) {
  int64_t largest = i;
  int64_t l = leftChild(i);
  int64_t r = rightChild(i);

  if (l < heap->size && heap->arr[l] > heap->arr[largest])
    largest = l;
  if (r < heap->size && heap->arr[r] > heap->arr[largest])
    largest = r;
  if (largest != i) {
    swap(&heap->arr[i], &heap->arr[largest]);
    heapifyDown(heap, largest);
  }
}

void insert(MaxHeap *heap, int64_t key) {
  if (heap->size == heap->capacity) {
    heap->capacity *= 2;
    heap->arr = (int64_t *)realloc(heap->arr, heap->capacity * sizeof(int64_t));
  }
  heap->arr[heap->size] = key;
  heapifyUp(heap, heap->size);
  heap->size++;
}

int64_t peekMax(MaxHeap *heap) {
  if (heap->size == 0)
    return 0;
  return heap->arr[0];
}

int64_t extractMax(MaxHeap *heap) {
  if (heap->size == 0)
    return 0;
  int64_t root = heap->arr[0];
  heap->arr[0] = heap->arr[heap->size - 1];
  heap->size--;
  heapifyDown(heap, 0);
  return root;
}

void freeHeap(MaxHeap *heap) {
  free(heap->arr);
  free(heap);
}
