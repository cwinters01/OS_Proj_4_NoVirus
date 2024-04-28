# OS_Proj_4
This is for group 6 for project 4 in CIS 520

HOW TO COMPILE, RUN, AND SCHEDULE THE CODE ON BEOCAT

MUST LOAD IN MODULES:
module load CMake/3.23.1-GCCcore-11.3.0 foss/2022a OpenMPI/4.1.4-GCC-11.3.0 CUDA/11.7.0

How to:

1. Log into Beocat
2. Change directory to the folder which you want to run (Pthreads, MPI, or OpenMP)
3. Run the compile script (./compile.sh); you may need to add permissions for the file (chmod u+x "filename")
4. Run the program with the following (sbatch --time=1:00:00 --mem-per-cpu=1G --cpus-per-task=1 --nodes=1 --constraints=moles ./run.sh)
   NOTE: you can change the cpus per task and nodes parameters
5. You can see the status of the job with (kstat -j #####) where #### is the job number
6. When completed, an output file will be placed in the directory
