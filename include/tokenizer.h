#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    EOF_TOK,    // \0
    SEMI_TOK,   // ;
    RET_TOK,    // retourner
    VAR_TOK,    // soit
    IDENT_TOK,  // <var>
    EQ_TOK,     // =
    EQEQ_TOK,   // ==
    NEQ_TOK,    // !=
    LT_TOK,     // <
    LEQ_TOK,    // <=
    GT_TOK,     // >
    GEQ_TOK,    // >=
    NUM_TOK,    // <num>
    PLUS_TOK,   // +
    MINUS_TOK,  // -
    MULT_TOK,   // *
    DIV_TOK,    // /
    LPAREN_TOK, // (
    RPAREN_TOK, // )
    IF_TOK,     // si
    ELSE_TOK,   // sinon
    LBRACE_TOK, // {
    RBRACE_TOK, // }
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