#!/usr/bin/bash

for((i = 1; ; ++i)); do
    echo $i
    ./generator > input
    ./generator < input > out1
    ./generator < input > out2
    diff -w out1 out2 || break
    #diff -w <(./a < int) <(./brute < int) 
done
