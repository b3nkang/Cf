#pragma once

#include <stdio.h>
#include "parser.h"
#include "symTab.h"

typedef struct {
    FILE* output;
    AstNode* currentFunction;
    int labelCount;
    SymbolTable* symbols;
    int varStackOffset;
    int tempStackOffset;
    int tempStackOffsetStart;
    int maxVarOffset;
    int minTempOffset;
    char* codeBuffer;
    size_t bufferSize;
    size_t bufferCapacity;
} CodeGenContext;

CodeGenContext* createCodeGenContext(FILE* output);

void freeCodeGenContext(CodeGenContext* context);
void generateCode(CodeGenContext* context, AstNode* node);
void generateProgram(CodeGenContext* context, AstNode* node);
void generateReturn(CodeGenContext* context, AstNode* node);
void generateExpression(CodeGenContext* context, AstNode* node);