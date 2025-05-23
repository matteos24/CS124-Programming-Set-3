#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <unistd.h>

#include "max_heap.h"

int64_t karmakar_karp(int64_t *arr, int n);
int64_t repeated_random(int64_t *arr, int n, int max_iter);
int64_t hill_climbing(int64_t *arr, int n, int max_iter);
int64_t simulated_annealing(int64_t *arr, int n, int max_iter);
int64_t pre_partition_repeated_random(int64_t *arr, int n, int max_iter);
int64_t pre_partition_hill_climbing(int64_t *arr, int n, int max_iter);
int64_t pre_partition_simulated_annealing(int64_t *arr, int n, int max_iter);

int64_t dot_product(int64_t *arr1, int *arr2, int n);
int64_t *conversion(int *arr1, int64_t *arr2, int n);
double t_iter(int iter);
double probability(int64_t residue1, int64_t residue2, int iter);
int64_t random_1_to_10_12();

int main(void) {

  srand(time(NULL));
  int64_t *test_array = malloc(100 * sizeof(int64_t));
  int64_t *result_array = malloc(7 * sizeof(int64_t));
  double *runtime_array = malloc(7 * sizeof(double));
  FILE *results_file = fopen("results.csv", "w");
  FILE *runtime_file = fopen("runtime.csv", "w");
  clock_t start;
  clock_t end;
  double elapsed_time;
  int64_t result;

  if (!results_file || !runtime_file) {
    perror("Error opening CSV files");
    return 1;
  }

  for (int i = 0; i < 50; i++) {
    printf("This is iteration %i\n", i);
    for (int j = 0; j < 100; j++) {

      test_array[j] = random_1_to_10_12();
    }

    start = clock();
    printf("This is iteration %i\n", i);
    result = karmakar_karp(test_array, 100);
    printf("This is iteration %i\n", i);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    result_array[0] = result;
    runtime_array[0] = elapsed_time;
    printf("This is iteration %i\n", i);

    start = clock();
    result = repeated_random(test_array, 100, 100000);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    result_array[1] = result;
    runtime_array[1] = elapsed_time;
    printf("This is iteration %i\n", i);

    start = clock();
    result = hill_climbing(test_array, 100, 100000);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    result_array[2] = result;
    runtime_array[2] = elapsed_time;
    printf("This is iteration %i\n", i);

    start = clock();
    result = simulated_annealing(test_array, 100, 100000);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    result_array[3] = result;
    runtime_array[3] = elapsed_time;
    printf("This is iteration %i\n", i);

    start = clock();
    result = pre_partition_repeated_random(test_array, 100, 100000);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    result_array[4] = result;
    runtime_array[4] = elapsed_time;
    printf("This is iteration %i\n", i);

    start = clock();
    result = pre_partition_hill_climbing(test_array, 100, 100000);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    result_array[5] = result;
    runtime_array[5] = elapsed_time;
    printf("This is iteration %i\n", i);

    start = clock();
    result = pre_partition_simulated_annealing(test_array, 100, 100000);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    result_array[6] = result;
    runtime_array[6] = elapsed_time;
    printf("This is iteration %i\n", i);

    for (int k = 0; k < 7; k++) {
      fprintf(results_file, "%lld", result_array[k]);
      if (k != 6)
        fprintf(results_file, ",");
    }
    fprintf(results_file, "\n");

    for (int k = 0; k < 7; k++) {
      fprintf(runtime_file, "%f", runtime_array[k]);
      if (k != 6)
        fprintf(runtime_file, ",");
    }
    fprintf(runtime_file, "\n");
    fflush(results_file);
    fflush(runtime_file);
  }

  fclose(results_file);
  fclose(runtime_file);
  free(test_array);
  free(result_array);
  free(runtime_array);

  printf("%f\n", random_1_to_10_12() / (pow(10.0, 12.0)));
}

int64_t karmakar_karp(int64_t *arr, int n) {
  MaxHeap *heap = createHeap(n);
  for (int i = 0; i < n; i++) {
    insert(heap, arr[i]);
  }
  while (heap->size > 1) {
    int64_t x = extractMax(heap);
    int64_t y = extractMax(heap);
    insert(heap, llabs(x - y));
  }

  int64_t result = llabs(peekMax(heap));
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

  int64_t residue = llabs(dot_product(arr, sol, n));
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

    test_residue = llabs(dot_product(arr, sol, n));
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

  int64_t residue = llabs(dot_product(arr, sol, n));
  int64_t test_residue;

  for (int i = 0; i < max_iter; i++) {
    memcpy(sol1, sol, n * sizeof(int));
    int index1 = rand() % n;
    int index2 = rand() % n;

    sol1[index1] = -sol[index1];
    if ((float)rand() / (float)RAND_MAX >= 0.5) {
      sol1[index2] = -sol[index2];
    }

    test_residue = llabs(dot_product(arr, sol1, n));
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

  int64_t residue = llabs(dot_product(arr, sol, n));
  int64_t test_residue;
  int64_t test_residue_new;

  for (int i = 0; i < max_iter; i++) {
    memcpy(sol1, sol, n * sizeof(int));
    int index1 = rand() % (n);
    int index2 = rand() % (n);

    sol1[index1] = -sol[index1];
    if ((float)rand() / (float)RAND_MAX >= 0.5) {
      sol1[index2] = -sol[index2];
    }

    test_residue = llabs(dot_product(arr, sol1, n));
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
    residue = llabs(dot_product(arr, sol, n));
    test_residue_new = llabs(dot_product(arr, sol2, n));

    if (residue < test_residue_new) {
      memcpy(sol2, sol, n * sizeof(int));
    }
  }

  test_residue_new = llabs(dot_product(arr, sol2, n));
  free(sol);
  free(sol1);
  free(sol2);
  return test_residue_new;
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
    memcpy(sol1, sol, n * sizeof(int));
    index1 = (rand() % (n));
    index2 = (rand() % (n));

    while (sol[index1] == index2) {
      index1 = (rand() % (n));
      index2 = (rand() % (n));
    }

    sol1[index1] = index2;
    free(second_converted_array);
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
  }
  memcpy(sol1, sol, n * sizeof(int));
  memcpy(sol2, sol, n * sizeof(int));

  int64_t *converted_array = conversion(sol, arr, n);
  int64_t residue = karmakar_karp(converted_array, n);
  int64_t test_residue;
  int64_t test_residue2;
  int64_t *second_converted_array = malloc(n * sizeof(int64_t));
  test_residue2 = residue;
  for (int i = 0; i < max_iter; i++) {
    memcpy(sol1, sol, n * sizeof(int));
    index1 = (rand() % (n));
    index2 = (rand() % (n));

    while (sol[index1] == index2) {
      index1 = (rand() % (n));
      index2 = (rand() % (n));
    }

    sol1[index1] = index2;
    free(second_converted_array);
    second_converted_array = conversion(sol1, arr, n);
    test_residue = karmakar_karp(second_converted_array, n);
    if (test_residue < residue) {
      residue = test_residue;
      sol[index1] = sol1[index1];
    } else if ((float)rand() / (float)RAND_MAX <=
               probability(residue, test_residue, i)) {
      residue = test_residue;
      sol[index1] = sol1[index1];
    } else {
      continue;
    }

    free(converted_array);
    converted_array = conversion(sol, arr, n);
    residue = karmakar_karp(converted_array, n);

    if (residue < test_residue2) {
      memcpy(sol2, sol, n * sizeof(int));
      test_residue2 = residue;
    }
  }
  free(sol);
  free(sol1);
  free(sol2);
  free(converted_array);
  free(second_converted_array);

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
