#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

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

void find_max_ascii(LineData *line_data) {
    int max = max_ascii_value(line_data->line, line_data->length);
    printf("%d: %d\n", line_data->line_number, max);
    free(line_data->line);
    free(line_data);
}

int main() {
    FILE *file;
    file = fopen("/homes/dan/625/wiki_dump.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    char *line_buffer = NULL;
    size_t buffer_size = 0;
    int line_number = 0; 

    int num_threads = 4; // Change this to adjust the number of threads

    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp single
        {
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
        
                #pragma omp task
                {
                    find_max_ascii(line_data);
                }
                line_number++;
            }
        }
    }

    if (line_buffer) free(line_buffer);
    fclose(file);

    return 0;
}
