#include <pthread.h>
#include <cstdio>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#define NUM_THREADS 4

void *circle_point(void *param)
{
    int temp = *(int*) param;
    int *pcount = (int *) malloc(sizeof(int));
    for (int i = 0; i < temp; ++i)
    {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        double r = sqrt(x * x + y * y);
        if (r < 1)
        {
            *pcount = *pcount + 1;
        }
    }
    return (void *) pcount;
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    pthread_t threadIDs[NUM_THREADS] = {0};
    int count[NUM_THREADS] = {0};
    int total_point;
    int *result;
    int temp = 0;
    double count_circle = atoll(argv[1]);

    result = NULL;

    if (argc == 1)
    {
        printf("Enter n:\n");
        return -1;
    }
    if (argc != 2)
    {
        printf("Incorrect number\n");
        return -1;
    }

    total_point = count_circle / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_create(&threadIDs[i], NULL, circle_point, (void *) &total_point);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threadIDs[i], (void **) &result);
        temp += *result;
        count_circle += count[i];
    }

    double pi = 4.0 * temp / count_circle;
    printf("Pi = %17.15f\n", pi);
    return 0;
}
