#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/tokenizer.h"

Tokenizer* createTokenizer(char* source) {
    Tokenizer* tokenizer = (Tokenizer*)malloc(sizeof(Tokenizer));
    tokenizer->inputSource = source;
    tokenizer->position = 0;
    tokenizer->currLn = 1;
    tokenizer->currCol = 1;
    return tokenizer;
}

Token* getNextToken(Tokenizer* tokenizer) {
    for (;;) {
        char currChar = tokenizer->inputSource[tokenizer->position];
        if (currChar == '\0') {
            Token* retTok = (Token*)malloc(sizeof(Token));
            retTok->type = EOF_TOK;
            retTok->value = NULL;
            return retTok;
        }
        if (isspace(currChar)) {
            tokenizer->position++;
            tokenizer->currCol++;
            continue;
        }
        if (currChar == '\n') {
            tokenizer->currLn++;
            tokenizer->currCol = 1;
            tokenizer->position++;
            continue;
        }
        Token* retTok = malloc(sizeof(Token));
        retTok->ln = tokenizer->currLn;
        retTok->col = tokenizer->currCol;
        
        switch (currChar) {
            case '+':
                retTok->type = PLUS_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case '-':
                retTok->type = MINUS_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case '*':
                retTok->type = MULT_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case '/':
                retTok->type = DIV_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case '(':
                retTok->type = LPAREN_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case ')':
                retTok->type = RPAREN_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case ';':
                retTok->type = SEMI_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case '=':
                if (tokenizer->inputSource[tokenizer->position + 1] == '=') {
                    retTok->type = EQEQ_TOK;
                    retTok->value = NULL;
                    tokenizer->position += 2;
                    tokenizer->currCol += 2;
                    return retTok;
                } else {
                    retTok->type = EQ_TOK;
                    retTok->value = NULL;
                    tokenizer->position++;
                    tokenizer->currCol++;
                    return retTok;
                }
            case '!':
                if (tokenizer->inputSource[tokenizer->position + 1] == '=') {
                    retTok->type = NEQ_TOK;
                    retTok->value = NULL;
                    tokenizer->position += 2;
                    tokenizer->currCol += 2;
                    return retTok;
                } else {
                    fprintf(stderr, "Error: Expected '=' after '!' at line %d, column %d\n", 
                            tokenizer->currLn, tokenizer->currCol);
                    exit(1);
                }
            case '<':
                if (tokenizer->inputSource[tokenizer->position + 1] == '=') {
                    retTok->type = LEQ_TOK;
                    retTok->value = NULL;
                    tokenizer->position += 2;
                    tokenizer->currCol += 2;
                    return retTok;
                } else {
                    retTok->type = LT_TOK;
                    retTok->value = NULL;
                    tokenizer->position++;
                    tokenizer->currCol++;
                    return retTok;
                }
            case '>':
                if (tokenizer->inputSource[tokenizer->position + 1] == '=') {
                    retTok->type = GEQ_TOK;
                    retTok->value = NULL;
                    tokenizer->position += 2;
                    tokenizer->currCol += 2;
                    return retTok;
                } else {
                    retTok->type = GT_TOK;
                    retTok->value = NULL;
                    tokenizer->position++;
                    tokenizer->currCol++;
                    return retTok;
                }
            case '{':
                retTok->type = LBRACE_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
            case '}':
                retTok->type = RBRACE_TOK;
                retTok->value = NULL;
                tokenizer->position++;
                tokenizer->currCol++;
                return retTok;
        }
        if (isdigit(currChar)) {
            free(retTok);
            return readNum(tokenizer);
        }
        if (isalpha(currChar)) {
            free(retTok);
            return readIdentifier(tokenizer);
        }
        fprintf(stderr, "Error: Unexpected character '%c' at line %d, column %d\n", currChar, tokenizer->currLn, tokenizer->currCol);
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
    retTok->ln = tokenizer->currLn;
    retTok->col = tokenizer->currCol;
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
    char* wordBuf = (char*)malloc(sizeof(char) * (wordLen + 1));
    strncpy(wordBuf, &tokenizer->inputSource[wordStart], wordLen);
    wordBuf[wordLen] = '\0';
    Token* retTok = (Token*)malloc(sizeof(Token));
    retTok->ln = tokenizer->currLn;
    retTok->col = tokenizer->currCol;
    if (strcmp(wordBuf, "rendre") == 0) {
        retTok->type = RET_TOK;
        retTok->value = wordBuf;
        return retTok;
    }
    if (strcmp(wordBuf, "soit") == 0) {
        retTok->type = VAR_TOK;
        retTok->value = wordBuf;
        return retTok;
    }
    if (strcmp(wordBuf, "si") == 0) {
        retTok->type = IF_TOK;
        retTok->value = wordBuf;
        return retTok;
    }
    if (strcmp(wordBuf, "sinon") == 0) {
        retTok->type = ELSE_TOK;
        retTok->value = wordBuf;
        return retTok;
    }
    // else is identifier
    retTok->type = IDENT_TOK;
    retTok->value = wordBuf;
    return retTok;
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
