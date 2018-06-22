#!/bin/bash

#SBATCH --job-name=MDP
#SBATCH --time=08:00:00
#SBATCH --cpus-per-task=24
#SBATCH --mem=1000

# Load modules
module load foss/2018a

# Run the code
make clean
make
./mdpsolver -f
