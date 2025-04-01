#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const unsigned short BUFFER_SIZE = 100;

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    uint32_t count = 0;
    char prevChar = '\0';
    char* line = malloc(BUFFER_SIZE);
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        while (fgets(line, BUFFER_SIZE, file) != NULL) {
            for (unsigned int i = 0; i < strlen(line); i++) {
                if (prevChar != line[i]) {
                    if (prevChar != '\0') {
                        fwrite(&count, sizeof(int), 1, stdout);
                        printf("%c", prevChar);
                        count = 0;
                    }
                    prevChar = line[i];
                    count++;
                }
                else {
                    count++;
                }
            }
        }
        fclose(file);
    }
    if (count > 0) {
        fwrite(&count, sizeof(int), 1, stdout);
        printf("%c", prevChar);
    }
    free(line);
}


