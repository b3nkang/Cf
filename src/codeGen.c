#include "../include/codeGen.h"
#include <stdlib.h>

CodeGenContext* createCodeGenContext(FILE* output) {
    CodeGenContext* context = malloc(sizeof(CodeGenContext));
    context->output = output;
    context->currentFunction = NULL;
    context->labelCount = 0;
    return context;
}

void freeCodeGenContext(CodeGenContext* context) {
    free(context);
}

void generateProgram(CodeGenContext* context, AstNode* node) {
    fprintf(context->output, "global _main\n");
    fprintf(context->output, "section .text\n");
    fprintf(context->output, "_main:\n");    
    for (size_t i = 0; i < node->as.program.count; i++) {
        generateCode(context, node->as.program.stmts[i]);
    }
}

void generateReturn(CodeGenContext* context, AstNode* node) {
    generateExpression(context, node->as.retStmt.val);
    fprintf(context->output, "    ret\n");
}

void generateExpression(CodeGenContext* context, AstNode* node) {
    switch (node->type) {
        case AST_NUM:
            fprintf(context->output, "    mov rax, %d\n", node->as.num.val);
            break;
        default:
            fprintf(stderr, "Error: Unsupported expression type in code generation\n");
            exit(1);
    }
}

void generateCode(CodeGenContext* context, AstNode* node) {
    if (!node) return;
    switch (node->type) {
        case AST_PROG:
            generateProgram(context, node);
            break;
        case AST_RET:
            generateReturn(context, node);
            break;
        default:
            fprintf(stderr, "Error: Unknown node type in code generation\n");
            exit(1);
    }
}