#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <chrono>
#include <thread>

int print_val() // int *p)
{
    int temp=50;
    int val=temp;
    std::cout << val << std::endl;
    return val;
}

int main(void)
{
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        print_val();
    }
    return 0;
}