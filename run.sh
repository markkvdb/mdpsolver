#!/bin/bash

echo Create experiments
Rscript create_experiments.R

echo Clean code
make clean 

echo Compile new code
make

echo Run code
./mdpsolver -f

echo Create plots
Rscript create_figures.R