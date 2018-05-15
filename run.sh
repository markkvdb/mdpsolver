#!/bin/bash

echo Clean code
make clean 

echo Compile new code
make

echo Run code
./mdpsolver

echo Create plots
Rscript create_figures.R