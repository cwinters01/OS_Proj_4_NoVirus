#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

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
    FILE *file = fopen("/homes/dan/625/wiki_dump.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    char *line_buffer = NULL;
    size_t buffer_size = 0;
    int line_number = 0; 

    while (getline(&line_buffer, &buffer_size, file) != -1) {
        LineData *line_data = (LineData *)malloc(sizeof(LineData));
        if (line_data == NULL) {
            perror("Memory allocation failed");
            fclose(file);
            return 1;
        }

        line_data->line = strdup(line_buffer);
        if (line_data->line == NULL) {
            perror("Memory allocation failed");
            fclose(file);
            free(line_data);
            return 1;
        }

        line_data->length = strlen(line_data->line);
        line_data->line_number = line_number; 

        int thread_index = line_number % NUM_THREADS;
        if (pthread_create(&threads[thread_index], NULL, find_max_ascii, (void *)line_data) != 0) {
            perror("Failed to create thread");
            fclose(file);
            free(line_data->line);
            free(line_data);
            return 1;
        }

        pthread_join(threads[thread_index], NULL);
        line_number++;
    }

    fclose(file);
    if (line_buffer) free(line_buffer);
    return 0;
}
