//Feel free to add more libraries if needed
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

  //DO THINGS

  fclose(file);

  //PROBABLY DO MORE THINGS

  return 0;

}
