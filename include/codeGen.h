#pragma once

#include <stdio.h>
#include "parser.h"
#include "symTab.h"

typedef struct {
    FILE* output;
    const char* currentFunction;
    int labelCount;
    SymbolTable* symbols;
} CodeGenContext;

CodeGenContext* createCodeGenContext(FILE* output);

void freeCodeGenContext(CodeGenContext* context);
void generateCode(CodeGenContext* context, AstNode* node);
void generateProgram(CodeGenContext* context, AstNode* node);
void generateReturn(CodeGenContext* context, AstNode* node);
void generateExpression(CodeGenContext* context, AstNode* node, int stackOffset);