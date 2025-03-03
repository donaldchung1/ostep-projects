#include <stdio.h>
#include <stdlib.h>

const int BUFFER_SIZE = 10;

void cat(char* filepath);

int main(int argc, char **argv) {
    for (unsigned int i = 1; i < argc; i++) {
        cat(argv[i]);
    }
}

void cat(char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (file != NULL) {
        char* line = malloc(BUFFER_SIZE);
        while (fgets(line, BUFFER_SIZE, file) != NULL) {
            printf("%s", line);
        }
        fclose(file);
        free(line);
    }
    else {
        printf("wcat: cannot open file\n");
        exit(1);
    }
}
