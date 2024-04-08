//Feel free to add more libraries if needed
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Will have to adjust
#define CHUNK_SIZE 1000

typedef struct {
  char **lines;
  int start;
  int end;
}Targs;
/*
// Finds the maximum ASCII value in a line
int max_ascii_value(char *line){
  int max = 0;

  while (*line){
    if(*line > max) max = *line;
    line++;
  }
  return max;
}*/

// Finds the maximum ASCII value in a line
int max_ascii_value(char *line, int nchars){
  int max = 0;

  for(int i = 0; i < nchars; i++){
    if((int)line[i] > max)
      max = (int)line[i];
  }
  return max;
}

// Finds the maximum ASCII in a chunk
void *find_max_ascii(void *args){
  Targs *targs = (Targs *)args;
  
  for (int i = targs->start; i < targs->end; i++){
    int nchars = strlen(targs->lines[i]);
    int max = max_ascii_value(targs->lines[i], nchars);
    printf("%d: %d\n", i, max);
  }
  pthread_exit(NULL);
  return NULL;
}

int main(){
  /*
  if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }*/


  int nlines = 0, max_lines = 100;
  FILE *file;
  char *line = (char*) malloc( 2001 ); // no lines larger 
  pthread_t threads[CHUNK_SIZE];
  Targs targs[CHUNK_SIZE];

  file = fopen("~dan/625/wiki_dump.txt", "r");
  if(file == NULL){
    perror("Error opening file");
    return 1;
  }

  while(nlines < max_lines){
    // Allocates memory for lines in a chunk
    char **lines = (char **)malloc(CHUNK_SIZE * sizeof(char *));
    if(lines == NULL){
      perror("Memory allocation failed");
      return 1;
    }

    // Reads lines into the chunk
    int line_count = 0;
    while (line_count < CHUNK_SIZE && fgets(line, 2000, file) != NULL){
      lines[line_count] = strdup(line); // Copies line into the array
      if(lines[line_count] == NULL){
        perror("Memory allocation failed");
        return 1;
      }
      line_count++;
      nlines++;
    }
    
    // Assigns arguments for the thread
    targs[line_count].lines = lines;
    targs[line_count].start = 0;
    targs[line_count].end = line_count;

    // Creates a thread to process the chunk
    if(pthread_create(&threads[line_count], NULL, find_max_ascii, (void *)&targs[line_count]) != 0){
      perror("Failed to create thread");
      return 1;
    }

    // Waits for the thread to finish
    pthread_join(threads[line_count], NULL);

    // Frees memory for lines
    for(int i = 0; i < line_count; i++){
      free(lines[i]);
    }
    free(lines);

    // Breaks loop if end of file is reached
    if(feof(file)) break;
  }

  fclose(file);
  free(line);
  return 0;
/*
  for ( i = 0; i < max_lines; i++ )  {
    err = fscanf(file, "%[^\n]\n", line);
    if( err == EOF ) break;
      nchars = strlen( line );
      printf("%d: %.1f\n", nlines, find_avg(line, nchars));
      nlines++;
   }

  //DO THINGS
  char **lines = malloc(CHUNK_SIZE * sizeof(char *));

  if (lines == NULL){
    perror("Memory allocation failed");
    return 1;
  }

  for (int i = 0; i < CHUNK_SIZE; i++) {
    lines[i] = malloc(1024 * sizeof(char)); // Will probably need to adjust the size
    if (lines[i] == NULL) {
        perror("Memory allocation failed");
        return 1;
    }
  }
  // Reads lines and process them in chunks using pthreads
  int line_count = 0;
  int chunk_count = 0;
  pthread_t threads[CHUNK_SIZE];
  Targs targs[CHUNK_SIZE];

  while(fgets(lines[line_count], CHUNK_SIZE, file) != NULL){
    if (line_count == CHUNK_SIZE){
      // Assigns thread arguments
      targs[chunk_count].lines = lines;
      targs[chunk_count].start = chunk_count * CHUNK_SIZE;
      targs[chunk_count].end = targs[chunk_count].start + CHUNK_SIZE;
      
      // Creates a new thread to process the chunk if valid
      if (pthread_create(&threads[chunk_count], NULL, find_max_ascii, (void *)&targs[chunk_count]) != 0){
        perror("Failed to create thread");
        return 1;
      }
      chunk_count++;
      line_count = 0;
    }
    else{
      lines[line_count][strlen(lines[line_count]) - 1] = '\0'; // Removes the newline character
      line_count++;
    }
  }

  // Processes the remaining lines
  if (line_count > 0){
    // Assigns thread arguments
    targs[chunk_count].lines = lines;
    targs[chunk_count].start = chunk_count * CHUNK_SIZE;
    targs[chunk_count].end = line_count;

    // Creates a new thread to process the chunk if valid
    if (pthread_create(&threads[chunk_count], NULL, find_max_ascii, (void *)&targs[chunk_count]) != 0){
      perror("Failed to create thread");
      return 1;
    }
    chunk_count++;
  }

  // Waits for all the threads to finish
  for (int i = 0; i <= chunk_count; i++) pthread_join(threads[i], NULL);

  fclose(file);

  // Frees the data
  for (int i = 0; i < CHUNK_SIZE; i++){
    free(lines[i]);
  }
  free(lines);

  return 0;
*/
}