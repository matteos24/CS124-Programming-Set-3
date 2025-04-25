#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity);
void swap(int *x, int *y);
int parent(int i);
int leftChild(int i);
int rightChild(int i);
void heapifyDown(MaxHeap* heap, int i);
void heapifyUp(MaxHeap* heap, int i);
void insert(MaxHeap* heap, int key);
int extractMax(MaxHeap* heap);
int peekMax(MaxHeap* heap);
void freeHeap(MaxHeap* heap);

int main() {
    MaxHeap* heap = createHeap(10);
    insert(heap, 3);
    insert(heap, 10);
    insert(heap, 5);
    insert(heap, 1);
    insert(heap, 8);

    printf("Max: %d\n", peekMax(heap));
    printf("Extracted: %d\n", extractMax(heap));
    printf("New Max: %d\n", peekMax(heap));

    freeHeap(heap);
    return 0;
}

MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int *x, int *y) {
    int temp = *x; *x = *y; *y = temp;
}

int parent(int i) { return (i - 1) / 2; }
int leftChild(int i) { return 2 * i + 1; }
int rightChild(int i) { return 2 * i + 2; }

void heapifyUp(MaxHeap* heap, int i) {
    while (i != 0 && heap->arr[parent(i)] < heap->arr[i]) {
        swap(&heap->arr[parent(i)], &heap->arr[i]);
        i = parent(i);
    }
}

void heapifyDown(MaxHeap* heap, int i) {
    int largest = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l < heap->size && heap->arr[l] > heap->arr[largest])
        largest = l;
    if (r < heap->size && heap->arr[r] > heap->arr[largest])
        largest = r;
    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        heapifyDown(heap, largest);
    }
}

void insert(MaxHeap* heap, int key) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->arr = (int*)realloc(heap->arr, heap->capacity * sizeof(int));
    }
    heap->arr[heap->size] = key;
    heapifyUp(heap, heap->size);
    heap->size++;
}

int peekMax(MaxHeap* heap) {
    if (heap->size == 0) return INT_MIN;
    return heap->arr[0];
}

int extractMax(MaxHeap* heap) {
    if (heap->size == 0) return INT_MIN;
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return root;
}

void freeHeap(MaxHeap* heap) {
    free(heap->arr);
    free(heap);
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity);
void swap(int *x, int *y);
int parent(int i);
int leftChild(int i);
int rightChild(int i);
void heapifyDown(MaxHeap* heap, int i);
void heapifyUp(MaxHeap* heap, int i);
void insert(MaxHeap* heap, int key);
int extractMax(MaxHeap* heap);
int peekMax(MaxHeap* heap);
void freeHeap(MaxHeap* heap);

int main() {
    MaxHeap* heap = createHeap(10);
    insert(heap, 3);
    insert(heap, 10);
    insert(heap, 5);
    insert(heap, 1);
    insert(heap, 8);

    printf("Max: %d\n", peekMax(heap));
    printf("Extracted: %d\n", extractMax(heap));
    printf("New Max: %d\n", peekMax(heap));

    freeHeap(heap);
    return 0;
}

MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int *x, int *y) {
    int temp = *x; *x = *y; *y = temp;
}

int parent(int i) { return (i - 1) / 2; }
int leftChild(int i) { return 2 * i + 1; }
int rightChild(int i) { return 2 * i + 2; }

void heapifyUp(MaxHeap* heap, int i) {
    while (i != 0 && heap->arr[parent(i)] < heap->arr[i]) {
        swap(&heap->arr[parent(i)], &heap->arr[i]);
        i = parent(i);
    }
}

void heapifyDown(MaxHeap* heap, int i) {
    int largest = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l < heap->size && heap->arr[l] > heap->arr[largest])
        largest = l;
    if (r < heap->size && heap->arr[r] > heap->arr[largest])
        largest = r;
    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        heapifyDown(heap, largest);
    }
}

void insert(MaxHeap* heap, int key) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->arr = (int*)realloc(heap->arr, heap->capacity * sizeof(int));
    }
    heap->arr[heap->size] = key;
    heapifyUp(heap, heap->size);
    heap->size++;
}

int peekMax(MaxHeap* heap) {
    if (heap->size == 0) return INT_MIN;
    return heap->arr[0];
}

int extractMax(MaxHeap* heap) {
    if (heap->size == 0) return INT_MIN;
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return root;
}

void freeHeap(MaxHeap* heap) {
    free(heap->arr);
    free(heap);
}
