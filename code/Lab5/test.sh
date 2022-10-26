#!/bin/bash
echo "Input file:"
cat input.txt
echo "Results"
g++ sched.cpp queue.cpp -o sched -lpthread
cat input.txt | ./sched
