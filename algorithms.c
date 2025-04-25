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

int64_t dot_product(int64_t *arr1, int64_t *arr2, int n);
double t_iter(int iter);
double probability(int64_t residue1, int64_t residue2, int iter);



int main(void)
{   
    srand(time(NULL));
    int n;
    int64_t *arr = malloc(n * sizeof(*arr));
    int64_t residue = karmarkar_karp(arr, n);
    printf("The residue is %i", residue);
    free(arr);

}

int64_t karmarkar_karp(int64_t *arr, int n) 
{
    // First, we build a max-heap of the n elements
    MaxHeap *heap = createHeap(n);
    for (int i = 0; i < n; i++) {
        insert(heap, arr[i]);
    }

    while (heap->size > 1) {
        int64_t x = extractMax(heap);
        int64_t y = extractMax(heap);
        insert(heap, x - y);
    }

    int64_t result = peekMax(heap);
    freeHeap(heap);
    return result;
}

int64_t repeated_random(int64_t *arr, int n, int max_iter)
{
    int* sol = malloc(n * sizeof(int));
    float random_decimal = 0.0;
    
    for (int j = 0; j < n; j++)
    {
        random_decimal  = (float)rand() / (float)RAND_MAX;
        if(random_decimal >= 0.5)
        {
            sol[j] = 1;
        }
        else
        {
            sol[j] = -1;
        }

    }

    int64_t residue = abs(dot_product(arr, sol, n));
    int64_t test_residue;

    for (int i = 0; i < max_iter; i++)
    {
        for (int j = 0; j < n; j++)
        {
            random_decimal  = (float)rand() / (float)RAND_MAX;
            if(random_decimal >= 0.5)
            {
                sol[j] = 1;
            }
            else
            {
                sol[j] = -1;
            }

        }

        test_residue = abs(dot_product(arr, sol, n));
        if (test_residue < residue)
        {
            residue = test_residue;
        }

    }
    
    free(sol);
    return residue;
}

int64_t hill_climbing(int64_t *arr, int n, int max_iter)
{
    int* sol = malloc(n * sizeof(int));
    int* sol1 = malloc(n * sizeof(int));
    float random_decimal = 0.0;
    
    for (int j = 0; j < n; j++)
    {
        random_decimal  = (float)rand() / (float)RAND_MAX;
        if(random_decimal >= 0.5)
        {
            sol[j] = 1;
        }
        else
        {
            sol[j] = -1;
        }
        sol1[j] = sol[j];
    }

    int64_t residue = abs(dot_product(arr, sol, n));
    int64_t test_residue;

    for (int i = 0; i < max_iter; i++)
    {
        int index1 = rand() % (n - 1) + 1;
        int index2 = rand() % (n - 1) + 1;

        sol1[index1] = -sol[index1];
        if ((float)rand() / (float)RAND_MAX >= 0.5)
        {
            sol1[index2] = -sol[index2]; 
        }

        test_residue = abs(dot_product(arr, sol1, n));
        if (test_residue < residue)
        {
            residue = test_residue;
            sol[index1] = sol1[index1];
            sol[index2] = sol1[index2];
        }
    }

    free(sol);
    free(sol1);
    return residue;

}

int64_t simulated_annealing(int64_t *arr, int n, int max_iter)
{
    int* sol = malloc(n * sizeof(int));
    int* sol1 = malloc(n * sizeof(int));
    int* sol2 = malloc(n * sizeof(int));
    float random_decimal = 0.0;
    
    for (int j = 0; j < n; j++)
    {
        random_decimal  = (float)rand() / (float)RAND_MAX;
        if(random_decimal >= 0.5)
        {
            sol[j] = 1;
        }
        else
        {
            sol[j] = -1;
        }

        sol1[j] = sol[j];
        sol2[j] = sol[j];
    }

    int64_t residue = abs(dot_product(arr, sol, n));
    int64_t test_residue;
    int64_t test_residue_new;
    int64_t test_residue_new2;

    for (int i = 0; i < max_iter; i++)
    {
        int index1 = rand() % (n - 1) + 1;
        int index2 = rand() % (n - 1) + 1;

        sol1[index1] = -sol[index1];
        if ((float)rand() / (float)RAND_MAX >= 0.5)
        {
            sol1[index2] = -sol[index2]; 
        }

        test_residue = abs(dot_product(arr, sol1, n));
        if (test_residue < residue)
        {
            residue = test_residue;
            sol[index1] = sol1[index1];
            sol[index2] = sol1[index2];
        }
        else if((float)rand() / (float)RAND_MAX <= probability(residue, test_residue, i))
        {
            sol[index1] = sol1[index1];
            sol[index2] = sol1[index2];
        }

        test_residue_new = abs(dot_product(arr, sol, n));
        test_residue_new2 = abs(dot_product(arr, sol2, n));

        if (test_residue_new < test_residue_new2)
        {
            sol2[index1] = sol[index1];
            sol2[index2] = sol[index2];
        }
        

    }

    test_residue_new2 = abs(dot_product(arr, sol2, n));
    return test_residue_new2;

}


int64_t dot_product(int64_t *arr1, int64_t *arr2, int n)
{
    int64_t result = 0;
    for (int i = 0; i < n; i++)
    {
        result  = result + (arr1[i] * arr2[i]);
    }
    return result;
}

double t_iter(int iter)
{
    int steps = iter / 300;               //Integer division is same as floor function
    return 1e10 * pow(0.8, (double)steps);
}

double probability(int64_t residue1, int64_t residue2, int iter)
{
    double delta = (double)residue2 - (double)residue1;
    double temp  = t_iter(iter);
    return exp(-delta / temp);
}




