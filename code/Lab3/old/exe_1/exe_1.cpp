#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "ex1.hpp"

void process_file_by_child(string, string);
void process_file_by_parent(string, string, string);

int main()
{
    pid_t proc1, proc2;
    string input_file_1 = "input/movie-100k_1.txt";
    string input_file_2 = "input/movie-100k_2.txt";
    string output_1 = "output/avg-movie_1.txt";
    string output_2 = "output/avg-movie_2.txt";
    string output = "output/final-movie.txt";

    proc1 = fork();

    if (proc1 == 0)
    {
        printf("Child process 1:\npid %d \nppid%d\n", getpid(), getppid());
        process_file_by_child(input_file_1, output_1);
    }

    else //if (proc1 > 0)
    {
        proc2 = fork();

        if (proc2 == 0)
        {
            printf("\nChild process 2:\npid %d \nppid%d\n", getpid(), getppid());
            process_file_by_child(input_file_2, output_2);
        }
        else// if (proc2 > 0)
        {
            wait(NULL);
            printf("\nParent process:\npid %d \nppid%d\n", getpid(), getppid());
            process_file_by_parent(output_1, output_2, output);
        }
    }
    return 0;
}
