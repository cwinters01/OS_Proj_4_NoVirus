#include <stdio.h>
#include <mpi.h>

int main() {
    int world_rank, world_size; //int for rank and number of processes
    
    MPI_Init(NULL, NULL); //initialize the MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //get rank of processes
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //get size of processes
    
    printf("Hello from process %d of %d\n", world_rank, world_size);
    
    MPI_Finalize(); //finalize and close MPI environment
    
    return 0;
}
