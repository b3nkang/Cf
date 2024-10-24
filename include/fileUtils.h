#pragma once

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192 // 8 KB

typedef enum {
    FILE_SUCCESS = 0,
    FILE_NOT_FOUND = -1,
    FILE_READ_ERROR = -2,
    FILE_WRITE_ERROR = -3
} FileResult;

char* readInputFile(const char* filepath);
FileResult writeToFile(const char* filepath, const char* content);

