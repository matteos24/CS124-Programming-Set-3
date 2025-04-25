#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <unistd.h>

#include "max_heap.h"

#include "algorithms.h"

int64_t karmakar_karp(int64_t *arr, int n) {
  MaxHeap *heap = createHeap(n);
  for (int i = 0; i < n; i++) {
    insert(heap, arr[i]);
  }

  while (heap->size > 1) {
    int64_t x = extractMax(heap);
    int64_t y = extractMax(heap);
    insert(heap, labs(x - y));
  }

  int64_t result = labs(peekMax(heap));
  freeHeap(heap);
  return result;
}

int64_t repeated_random(int64_t *arr, int n, int max_iter) {
  int *sol = malloc(n * sizeof(int));
  float random_decimal = 0.0;

  for (int j = 0; j < n; j++) {
    random_decimal = (float)rand() / (float)RAND_MAX;
    if (random_decimal >= 0.5) {
      sol[j] = 1;
    } else {
      sol[j] = -1;
    }
  }

  int64_t residue = labs(dot_product(arr, sol, n));
  int64_t test_residue;

  for (int i = 0; i < max_iter; i++) {
    for (int j = 0; j < n; j++) {
      random_decimal = (float)rand() / (float)RAND_MAX;
      if (random_decimal >= 0.5) {
        sol[j] = 1;
      } else {
        sol[j] = -1;
      }
    }

    test_residue = labs(dot_product(arr, sol, n));
    if (test_residue < residue) {
      residue = test_residue;
    }
  }

  free(sol);
  return residue;
}

int64_t hill_climbing(int64_t *arr, int n, int max_iter) {
  int *sol = malloc(n * sizeof(int));
  int *sol1 = malloc(n * sizeof(int));
  float random_decimal = 0.0;

  for (int j = 0; j < n; j++) {
    random_decimal = (float)rand() / (float)RAND_MAX;
    if (random_decimal >= 0.5) {
      sol[j] = 1;
    } else {
      sol[j] = -1;
    }
    sol1[j] = sol[j];
  }

  int64_t residue = labs(dot_product(arr, sol, n));
  int64_t test_residue;

  for (int i = 0; i < max_iter; i++) {
    int index1 = rand() % (n - 1) + 1;
    int index2 = rand() % (n - 1) + 1;

    sol1[index1] = -sol[index1];
    if ((float)rand() / (float)RAND_MAX >= 0.5) {
      sol1[index2] = -sol[index2];
    }

    test_residue = labs(dot_product(arr, sol1, n));
    if (test_residue < residue) {
      residue = test_residue;
      sol[index1] = sol1[index1];
      sol[index2] = sol1[index2];
    }
  }

  free(sol);
  free(sol1);
  return residue;
}

int64_t simulated_annealing(int64_t *arr, int n, int max_iter) {
  int *sol = malloc(n * sizeof(int));
  int *sol1 = malloc(n * sizeof(int));
  int *sol2 = malloc(n * sizeof(int));
  float random_decimal = 0.0;

  for (int j = 0; j < n; j++) {
    random_decimal = (float)rand() / (float)RAND_MAX;
    if (random_decimal >= 0.5) {
      sol[j] = 1;
    } else {
      sol[j] = -1;
    }

    sol1[j] = sol[j];
    sol2[j] = sol[j];
  }

  int64_t residue = labs(dot_product(arr, sol, n));
  int64_t test_residue;
  int64_t test_residue_new;
  int64_t test_residue_new2;

  for (int i = 0; i < max_iter; i++) {
    int index1 = rand() % (n);
    int index2 = rand() % (n);

    sol1[index1] = -sol[index1];
    if ((float)rand() / (float)RAND_MAX >= 0.5) {
      sol1[index2] = -sol[index2];
    }

    test_residue = labs(dot_product(arr, sol1, n));
    if (test_residue < residue) {
      residue = test_residue;
      sol[index1] = sol1[index1];
      sol[index2] = sol1[index2];
    } else if ((float)rand() / (float)RAND_MAX <=
               probability(residue, test_residue, i)) {
      residue = test_residue;
      sol[index1] = sol1[index1];
      sol[index2] = sol1[index2];
    }

    residue = labs(dot_product(arr, sol, n));
    test_residue_new2 = labs(dot_product(arr, sol2, n));

    if (residue < test_residue_new2) {
      sol2[index1] = sol[index1];
      sol2[index2] = sol[index2];
    }
  }

  test_residue_new2 = labs(dot_product(arr, sol2, n));
  free(sol);
  free(sol1);
  free(sol2);
  return test_residue_new2;
}

int64_t pre_partition_repeated_random(int64_t *arr, int n, int max_iter) {
  int *sol = malloc(n * sizeof(int));
  for (int j = 0; j < n; j++) {
    sol[j] = (rand() % (n));
  }
  int64_t *converted_array = conversion(sol, arr, n);
  int64_t residue = karmakar_karp(converted_array, n);
  int64_t test_residue;

  for (int i = 0; i < max_iter; i++) {
    for (int j = 0; j < n; j++) {
      sol[j] = (rand() % (n));
    }
    converted_array = conversion(sol, arr, n);
    test_residue = karmakar_karp(converted_array, n);

    if (test_residue < residue) {
      residue = test_residue;
    }
  }

  free(sol);
  free(converted_array);
  return residue;
}

int64_t pre_partition_hill_climbing(int64_t *arr, int n, int max_iter) {
  int *sol = malloc(n * sizeof(int));
  int *sol1 = malloc(n * sizeof(int));
  int index1;
  int index2;

  for (int j = 0; j < n; j++) {
    sol[j] = (rand() % (n));
    sol1[j] = sol[j];
  }

  int64_t *converted_array = conversion(sol, arr, n);
  int64_t residue = karmakar_karp(converted_array, n);
  int64_t test_residue;
  int64_t *second_converted_array = malloc(n * sizeof(int64_t));

  for (int i = 0; i < max_iter; i++) {
    index1 = (rand() % (n));
    index2 = (rand() % (n));

    while (sol[index1] == index2) {
      index1 = (rand() % (n));
      index2 = (rand() % (n));
    }

    sol1[index1] = index2;
    second_converted_array = conversion(sol1, arr, n);
    test_residue = karmakar_karp(second_converted_array, n);

    if (test_residue < residue) {
      residue = test_residue;
      sol[index1] = sol1[index1];
    }
  }

  free(sol);
  free(sol1);
  free(converted_array);
  free(second_converted_array);
  return residue;
}

int64_t pre_partition_simulated_annealing(int64_t *arr, int n, int max_iter) {
  int *sol = malloc(n * sizeof(int));
  int *sol1 = malloc(n * sizeof(int));
  int *sol2 = malloc(n * sizeof(int));
  int index1;
  int index2;

  for (int j = 0; j < n; j++) {
    sol[j] = (rand() % (n));
    sol1[j] = sol[j];
    sol2[j] = sol[j];
  }

  int64_t *converted_array = conversion(sol, arr, n);
  int64_t residue = karmakar_karp(converted_array, n);
  int64_t test_residue;
  int64_t test_residue2;
  int64_t *second_converted_array = malloc(n * sizeof(int64_t));
  int64_t *third_converted_array = malloc(n * sizeof(int64_t));

  for (int i = 0; i < max_iter; i++) {
    index1 = (rand() % (n));
    index2 = (rand() % (n));

    while (sol[index1] == index2) {
      index1 = (rand() % (n));
      index2 = (rand() % (n));
    }

    sol1[index1] = index2;
    second_converted_array = conversion(sol1, arr, n);
    test_residue = karmakar_karp(second_converted_array, n);
    if (test_residue < residue) {
      residue = test_residue;
      sol[index1] = sol1[index1];
    } else if ((float)rand() / (float)RAND_MAX <=
               probability(residue, test_residue, i)) {
      residue = test_residue;
      sol[index1] = sol1[index1];
    }

    converted_array = conversion(sol, arr, n);
    residue = karmakar_karp(converted_array, n);
    third_converted_array = conversion(sol2, arr, n);
    test_residue2 = karmakar_karp(third_converted_array, n);

    if (residue < test_residue2) {
      sol2[index1] = sol[index1];
    }
  }

  third_converted_array = conversion(sol2, arr, n);
  test_residue2 = karmakar_karp(third_converted_array, n);
  free(sol);
  free(sol1);
  free(sol2);
  free(converted_array);
  free(second_converted_array);
  free(third_converted_array);

  return test_residue2;
}

int64_t dot_product(int64_t *arr1, int *arr2, int n) {
  int64_t result = 0;
  for (int i = 0; i < n; i++) {
    result = result + (arr1[i] * arr2[i]);
  }
  return result;
}

int64_t *conversion(int *arr1, int64_t *arr2, int n) {
  int64_t *final_array = malloc(n * sizeof(int64_t));
  for (int j = 0; j < n; j++) {
    final_array[j] = 0;
  }

  for (int j = 0; j < n; j++) {
    final_array[arr1[j]] = final_array[arr1[j]] + arr2[j];
  }
  return final_array;
}

double t_iter(int iter) {
  int steps = iter / 300; // Integer division is same as floor function
  return 1e10 * pow(0.8, (double)steps);
}

double probability(int64_t residue1, int64_t residue2, int iter) {
  double delta = (double)residue2 - (double)residue1;
  double temp = t_iter(iter);
  return exp(-delta / temp);
}

int64_t random_1_to_10_12() {
  int64_t r = 0;
  // Combine multiple rand() calls to get enough bits
  r = ((int64_t)rand() << 45) | ((unsigned long long)rand() << 30) |
      ((int64_t)rand() << 15) | (unsigned long long)rand();

  // Now r is a 60-bit random number
  return (r % 1000000000000ULL) + 1;
}
