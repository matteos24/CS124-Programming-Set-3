

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <stdlib.h>

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

#endif // MAX_HEAP_H
