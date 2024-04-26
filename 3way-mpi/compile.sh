#!/bin/bash
# Load the desired OpenMPI module
module load OpenMPI/4.1.4-GCC-11.3.0

# Compile the MPI program using mpicc
mpicc -O3 mpi.c -o proj4_mpi
