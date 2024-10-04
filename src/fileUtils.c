#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/fileUtils.h"

static size_t getFileSize(FILE* file) {
    if (!file) {
        return 0;
    }
    long currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, currentPos, SEEK_SET);
    return size;
}

char* readInputFile(const char* filepath) {
    FILE* input = fopen(filepath, "r");
    if (!input) {
        fprintf(stderr, "Could not open source file %s\n", filepath);
        exit(1);
    }    
    size_t size = getFileSize(input);
    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for file contents\n");
        fclose(input);
        exit(1);
    }
    size_t bytesRead = fread(buffer, 1, size, input);
    if (bytesRead != size) {
        fprintf(stderr, "Error reading file %s: %s\n", 
                filepath, strerror(errno));
        free(buffer);
        fclose(input);
        exit(1);
    }
    buffer[size] = '\0';
    fclose(input);
    return buffer;
}
