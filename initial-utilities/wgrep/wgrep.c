#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFER_SIZE = 10;

char* bufferLine(char* buffer, char* line);

int main(int argc, char **argv) { 
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    char* pattern = argv[1];
    if (argc == 2) {
        char* line = NULL;
        size_t linecap = 0;
        ssize_t linelen;
        while ((linelen = getline(&line, &linecap, stdin) > 0)) {
            if (strstr(line, pattern) != NULL) {
                printf("%s", line);
            }
        }
    }

    if (argc == 3) {
        FILE* file = fopen(argv[2], "r");
        if (file != NULL) {
            char* line = malloc(BUFFER_SIZE);
            char* bufferedString = NULL;
            while (fgets(line, BUFFER_SIZE, file) != NULL) {
                size_t len = strlen(line);
                char lc = line[len-1];
                if (len > 0) {
                    if (lc != '\n' && lc != EOF) {
                        bufferedString = bufferLine(bufferedString, line);
                    }
                    if (lc == '\n') {
                        bufferedString = bufferLine(bufferedString, line);
                        if (strstr(bufferedString, pattern) != NULL) {
                            printf("%s", bufferedString);
                        }
                        free(bufferedString);
                        bufferedString = NULL;
                    }
                    if (lc == EOF) {
                        bufferedString = bufferLine(bufferedString, line);
                        if (strstr(bufferedString, pattern) != NULL) {
                            printf("%s", bufferedString);
                        }
                        free(bufferedString);
                        bufferedString = NULL;
                    }
                }
            }
            fclose(file);
            free(line);
        }

        else {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
    }
    
}

char* bufferLine(char* buffer, char* line) {
    size_t lineSize = strlen(line);
    if (buffer == NULL) {
        buffer = malloc(lineSize+1);
        if (strlcpy(buffer, line, lineSize+1) != lineSize) {
            printf("wgrep: failed buffering line\n");
            exit(1);
        }
        return buffer;
    }
    size_t bufferSize = strlen(buffer);
    char* t = malloc(bufferSize+1);
    strlcpy(t, buffer, bufferSize+1);
    free(buffer);
    buffer = malloc(bufferSize + lineSize + 1);
    strlcpy(buffer, t, bufferSize+1);
    strlcat(buffer, line, bufferSize + lineSize + 1);
    free(t);
    return buffer;
}

