/*
    int world_rank, world_size; //int for rank and number of processes
    
    MPI_Init(NULL, NULL); //initialize the MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //get rank of processes
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //get size of processes
    
    printf("Hello from process %d of %d\n", world_rank, world_size);
    
    MPI_Finalize(); //finalize and close MPI environment
    */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <mpi.h>
    
#define NUM_THREADS 10 // Define the number of pthreads

typedef struct {
    char *line;
    int length;
    int line_number; 
} LineData;

int max_ascii_value(char *line, int nchars) {
    int max = 0;
    for (int i = 0; i < nchars; i++) {
        if ((int)line[i] > max)
            max = (int)line[i];
    }
    return max;
}

void *find_max_ascii(void *args) {
    LineData *line_data = (LineData *)args;
    int max = max_ascii_value(line_data->line, line_data->length);
    printf("%d: %d\n", line_data->line_number, max);
    free(line_data->line);
    free(line_data);
    pthread_exit(NULL);
    return NULL;
}

int main() {
    int world_rank, world_size; //int for rank and number of processes
    
    MPI_Init(NULL, NULL); //initialize the MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //get rank of processes
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //get size of processes

    if (size <= 1){
        perror("Error: Must have more than 1 process.\n");
        MPI_Finalize();
        return 1;
    }
    
    FILE *file;
    if (world_rank == 0){
        file = fopen("/homes/dan/625/wiki_dump.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            MPI_Finalize();
                return 1;
        }
    }

    char *line_buffer = NULL;
    size_t buffer_size = 0;
    int line_number = 0; 

    while (getline(&line_buffer, &buffer_size, file) != -1) {
        if (line_number % world_size == world_rank){
            LineData *line_data = (LineData *)malloc(sizeof(LineData));
            if (line_data == NULL) {
                perror("Memory allocation failed");
                fclose(file);
                MPI_Finalize();
                return 1;
            }
    
            line_data->line = strdup(line_buffer);
            if (line_data->line == NULL) {
                perror("Memory allocation failed");
                fclose(file);
                free(line_data);
                MPI_Finalize();
                return 1;
            }
    
            line_data->length = strlen(line_data->line);
            line_data->line_number = line_number; 
    
            int max = max_ascii_value(line_data->line, line_data->length);
            printf("%d: %d\n", line_data->line_number, max);
            
            free(line_data->line);
            free(line_data);
        }
        line_number++;
    }

    if (line_buffer) free(line_buffer);
    if (rank == 0) fclose(file);

    MPI_Finalize();
    return 0;
}
