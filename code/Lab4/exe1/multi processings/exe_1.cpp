#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>
#include <sys/wait.h>
#include <fstream>

int count_circle(int total_point)
{
    int count_circle = 0;

    srand(time(NULL));

    for (int i = 0; i < total_point / 2; i++)
    {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        double r = (x * x + y * y);
        if (r < 1)
            ++count_circle;
    }
    return count_circle;
}

int main(int argc, char const *argv[])
{
    int total_point = 0, n;
    double pi;
    pid_t pid_B, pid_C;
    std::string output1 = "output1.txt";
    std::string output2 = "output2.txt";

    // Step 1: Get user input.
    if (argc == 1)
    {
        printf("Please execute program such as.\n./exe4_1 1000000\n");
        return -1;
    } else if (argc != 2)
    {
        printf("Incorrect number.\n");
        return -1;
    }

    total_point = atoll(argv[1]);
    if (total_point <= 0)
    {
        printf("Incorrect parameter\n");
        return -1;
    }

    // Step 2: Fork 02 children process to calculate PI.
    pid_B = fork();
    if (pid_B == 0)
    {
        std::ofstream file_(output1);
        file_ << count_circle(total_point);
        file_.close();
        exit(EXIT_SUCCESS);
    }

    pid_C = fork();
    if (pid_C == 0)
    {
        std::ofstream file_(output2);
        file_ << count_circle(total_point);
        file_.close();
        exit(EXIT_SUCCESS);
    }

    // Step 3: Wait children process done.
    int w1, w2, status1, status2;
    w1 = waitpid(pid_B, &status1, 0);
    if (w1 == -1)
        perror("waitpid");
        exit(EXIT_FAILURE);
    // printf("%d terminated: %d\n", pid_B, w1);

    w2 = waitpid(pid_C, &status2, 0);
    if (w2 == -1)
        perror("waitpid");
        exit(EXIT_FAILURE);
    // printf("%d terminated: %d\n", pid_C, w2);

    // Step 4: Combine results.
    int result_total = 0, result1, result2;

    std::ifstream file_1(output1);
    file_1 >> result1;
    file_1.close();

    std::ifstream file_2(output2);
    file_2 >> result2;
    file_2.close();

    result_total = result1 + result2;
    pi = 4.0 * result_total / total_point;
    printf("Pi = %17.15f\n", pi);

    return 0;
}
