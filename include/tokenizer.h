#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    EOF_TOK,
    SEMI_TOK,
    RET_TOK,
    VAR_TOK,
    IDENT_TOK,
    EQ_TOK,
    NUM_TOK,
    PLUS_TOK,
    MINUS_TOK,
    MULT_TOK,
    DIV_TOK,
    LPAREN_TOK,
    RPAREN_TOK
} TokenType;

typedef struct {
    TokenType type;
    char* value;
    int ln;
    int col;
} Token;

typedef struct {
    char* inputSource;
    size_t position;
    int currLn;
    int currCol;
} Tokenizer;

typedef struct {
    Token** tokens; // array of toks
    size_t count;
    size_t capacity;
} TokenArray;

Tokenizer* createTokenizer(char* source);
Token* getNextToken(Tokenizer* tokenizer);
void freeTokenizer(Tokenizer* tokenizer);
void freeToken(Token* token);
Token* readNum(Tokenizer* tokenizer);
Token* readIdentifier(Tokenizer* tokenizer);
TokenArray* createTokenArray();
void addToken(TokenArray* arr, Token* newToken);
void freeTokenArray(TokenArray* arr);