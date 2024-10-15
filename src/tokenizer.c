#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/tokenizer.h"

Tokenizer* createTokenizer(char* source) {
    Tokenizer* tokenizer = (Tokenizer*)malloc(sizeof(Tokenizer));
    tokenizer->inputSource = source;
    tokenizer->position = 0;
    return tokenizer;
}

Token* getNextToken(Tokenizer* tokenizer) {
    for (;;) {
        char currChar = tokenizer->inputSource[tokenizer->position];
        if (isspace(currChar)) {
            tokenizer->position++;
            continue;
        }
        if (currChar == '\0') {
            Token* retTok = (Token*)malloc(sizeof(Token));
            retTok->type = EOF_TOK;
            retTok->value = NULL;
            return retTok;
        }
        if (isdigit(currChar)) {
            return readNum(tokenizer);
        }
        if (currChar == ';') {
            Token* retTok = (Token*)malloc(sizeof(Token));
            retTok->type = SEMI_TOK;
            retTok->value = NULL;
            tokenizer->position++;
            return retTok;
        }
        if (isalpha(currChar)) {
            return readIdentifier(tokenizer);
        }
        fprintf(stderr, "Error: Unexpected character '%c' at position %zu\n", currChar, tokenizer->position);
        exit(1);
    }
}

Token* readNum(Tokenizer* tokenizer) {
    size_t numStart = tokenizer->position;
    while (isdigit(tokenizer->inputSource[tokenizer->position])) {
        tokenizer->position++;
    }
    size_t numLen = tokenizer->position - numStart;
    Token* retTok = (Token*)malloc(sizeof(Token));
    retTok->type = NUM_TOK;
    retTok->value = malloc(numLen+1);
    strncpy(retTok->value,&tokenizer->inputSource[numStart],numLen);
    retTok->value[numLen] = '\0';
    return retTok;
}

Token* readIdentifier(Tokenizer* tokenizer) {
    size_t wordStart = tokenizer->position;
    while(isalnum(tokenizer->inputSource[tokenizer->position])) {
        tokenizer->position++;
    }
    size_t wordEnd = tokenizer->position;
    size_t wordLen = wordEnd - wordStart;
    char* wordBuf = (char*)malloc(sizeof(wordLen+1));
    strncpy(wordBuf,&tokenizer->inputSource[wordStart],wordLen);
    wordBuf[wordLen] = '\0';
    Token* retTok = (Token*)malloc(sizeof(Token));
    if (strncmp(&tokenizer->inputSource[wordStart],"retourner",wordLen) == 0 && wordLen == 9) {
        retTok->type = RET_TOK;
        retTok->value = wordBuf;
        return retTok;
    }
    // TODO: implement tokenizing for strings
    free(wordBuf);
    free(retTok);
    fprintf(stderr, "Error: Unknown identifier at position %zu\n", wordStart);
    exit(1);
}

void freeTokenizer(Tokenizer* tokenizer) {
    free(tokenizer);
}

void freeToken(Token* token) {
    if (token->value != NULL) {
        free(token->value);
    }
    free(token);
}

TokenArray* createTokenArray() {
    TokenArray* tokArr = malloc(sizeof(TokenArray));
    tokArr->capacity = 16;
    tokArr->count = 0;
    tokArr->tokens = malloc(sizeof(Token*) * tokArr->capacity);
    return tokArr;
}

void addToken(TokenArray* tokArr, Token* tok) {
    if (tokArr->count >= tokArr->capacity) {
        size_t newCapacity = tokArr->capacity * 2;
        Token** newTokens = malloc(sizeof(Token*) * newCapacity);
        for (size_t i = 0; i < tokArr->count; i++) {
            newTokens[i] = tokArr->tokens[i];
        }
        free(tokArr->tokens);
        tokArr->tokens = newTokens;
        tokArr->capacity = newCapacity;
    }
    tokArr->tokens[tokArr->count] = tok;
    tokArr->count++;
}

void freeTokenArray(TokenArray* arr) {
    for (size_t i = 0; i < arr->count; i++) {
        freeToken(arr->tokens[i]);
    }
    free(arr->tokens);
    free(arr);
}
