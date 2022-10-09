#include <pthread.h>
#include <cstdio>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#define INTERVAL 10000

int main()
{
    int interval, i;
    double rand_x, rand_y, origin_dist, pi;
    int circle_points = 0, square_points = 0;

    srand(time(NULL));

    for (i = 0; i < (INTERVAL * INTERVAL); ++i)
    {
        rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL;

        origin_dist = rand_x * rand_x + rand_y * rand_y;
        if (origin_dist <= 1)
        {
            ++circle_points;
        }
        ++square_points;
        pi = double(4 * circle_points) / square_points;

        std::cout << rand_x << " " << rand_y << " "
                  << circle_points << " " << square_points
                  << " - " << pi << std::endl;
        if (i < 20)
        {
            std::getchar();
        }
    }

    std::cout << " Pi = " << pi;

    return 0;
}