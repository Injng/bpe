#!/bin/bash

gcc -g -Wall -Wextra src/main.c src/freq.c src/encode.c -o main.o -fsanitize=address
