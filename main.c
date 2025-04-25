#include "algorithms.h"
#include <fcntl.h>

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <unistd.h>

#define NUMBERS_COUNT 100

int max_iters = 25000;
int64_t run_algorithm(int algorithm, long *numbers) {
  if (algorithm == 0) {
    return karmakar_karp(numbers, NUMBERS_COUNT);
  } else if (algorithm == 1) {
    return repeated_random(numbers, NUMBERS_COUNT, max_iters);
  } else if (algorithm == 2) {
    return hill_climbing(numbers, NUMBERS_COUNT, max_iters);
  } else if (algorithm == 3) {
    return simulated_annealing(numbers, NUMBERS_COUNT, max_iters);
  } else if (algorithm == 11) {
    return pre_partition_repeated_random(numbers, NUMBERS_COUNT, max_iters);
  } else if (algorithm == 12) {
    return pre_partition_hill_climbing(numbers, NUMBERS_COUNT, max_iters);
  } else if (algorithm == 13) {
    return pre_partition_simulated_annealing(numbers, NUMBERS_COUNT, max_iters);
  } else {
    fprintf(stderr, "Unknown algorithm: %d\n", algorithm);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  int fd = open("/dev/urandom", O_RDONLY);

  if (fd < 0) {

    perror("open");

    return 1;
  }

  unsigned int random_number;

  ssize_t result = read(fd, &random_number, sizeof(random_number));

  if (result < 0) {

    perror("read");

    close(fd);

    return 1;
  }

  close(fd);

  srand(time(NULL) + random_number);
  if (argc != 4) {
    fprintf(stderr, "Usage: %s flag algorithm inputfile\n", argv[0]);
    return 1;
  }

  int flag = atoi(argv[1]);
  if (flag == 1) {
    max_iters = 100;
  }
  int algorithm = atoi(argv[2]);
  const char *inputfile = argv[3];

  FILE *file = fopen(inputfile, "r");
  if (!file) {
    fprintf(stderr, "Error opening file: %s\n", inputfile);
    return 1;
  }

  long numbers[NUMBERS_COUNT];
  int count = 0;
  while (fscanf(file, "%ld", &numbers[count]) == 1) {
    count++;
  }
  fclose(file);

  if (count != NUMBERS_COUNT) {
    fprintf(stderr, "Error: input file must contain exactly %d integers.\n",
            NUMBERS_COUNT);
    return 1;
  }

  int64_t residue = run_algorithm(algorithm, numbers);

  printf("%ld\n", residue);

  return 0;
}
