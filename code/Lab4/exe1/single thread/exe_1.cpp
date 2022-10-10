#include <pthread.h>
#include <cstdio>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    int total_point;
    int square_points = 0, count_circle = 0;
    double x, y, r, pi;

    if (argc == 1)
    {
        printf("Please execute program such as.\n./exe4_1 1000000\n");
        return -1;
    }
    if (argc != 2)
    {
        printf("Incorrect number\n");
        return -1;
    }
    total_point = atoll(argv[1]);

    for (int i = 0; i < total_point; ++i)
    {
        x = (double)rand() / (double)RAND_MAX;
        y = (double)rand() / (double)RAND_MAX;
        r = sqrt(x * x + y * y);
        if (r <= 1)
        {
            count_circle += 1;
        }
        ++square_points;
        pi = double((4.0 * count_circle) / square_points);
    }

    printf("Pi = %17.15f\n", pi);

    return 0;
}
