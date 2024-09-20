#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    NUM_TOK,
    SEMI_TOK,
    EOF_TOK,
    RET_TOK
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

typedef struct {
    char* inputSource;
    size_t position;
} Tokenizer;