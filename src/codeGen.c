#include "../include/codeGen.h"
#include <stdlib.h>

CodeGenContext* createCodeGenContext(FILE* output) {
    CodeGenContext* context = malloc(sizeof(CodeGenContext));
    context->output = output;
    context->currentFunction = NULL;
    context->labelCount = 0;
    context->symbols = createSymbolTable();
    return context;
}

void freeCodeGenContext(CodeGenContext* context) {
    freeSymbolTable(context->symbols);
    free(context);
}

void generateVarDeclaration(CodeGenContext* context, AstNode* node) {
    generateExpression(context, node->as.varDecl.initializer, 8);
    Symbol* sym = addSymbol(context->symbols, node->as.varDecl.name);
    if (!sym) {
        fprintf(stderr, "Error: Variable '%s' already declared\n", node->as.varDecl.name);
        exit(1);
    }
    fprintf(context->output, "    mov [rbp - %d], rax\n", sym->stackOffset);
}

void generateVarReference(CodeGenContext* context, AstNode* node) {
    Symbol* sym = lookupSymbol(context->symbols, node->as.varRef.name);
    if (!sym) {
        fprintf(stderr, "Error: Undefined variable '%s'\n", node->as.varRef.name);
        exit(1);
    }
    fprintf(context->output, "    mov rax, [rbp - %d]\n", sym->stackOffset);
}

void generateProgram(CodeGenContext* context, AstNode* node) {
    fprintf(context->output, "global _main\n");
    fprintf(context->output, "section .text\n");
    fprintf(context->output, "_main:\n");
    fprintf(context->output, "    push rbp\n");
    fprintf(context->output, "    mov rbp, rsp\n");
    fprintf(context->output, "    sub rsp, 128\n");
    for (size_t i = 0; i < node->as.program.count; i++) {
        generateCode(context, node->as.program.stmts[i]);
    }
}


void generateReturn(CodeGenContext* context, AstNode* node) {
    generateExpression(context, node->as.retStmt.val,8);
    // fprintf(context->output, "    ret\n");
    fprintf(context->output, "    leave\n");
    fprintf(context->output, "    and rsp, -16\n");
    fprintf(context->output, "    mov rdi, rax\n");
    fprintf(context->output, "    mov rax, 0x2000001\n");
    fprintf(context->output, "    syscall\n");
}

void generateExpression(CodeGenContext* context, AstNode* node, int stackOffset) {
    switch (node->type) {
        case AST_NUM:
            fprintf(context->output, "    mov rax, %d\n", node->as.num.val);
            break;
        case AST_VAR_REF:
            generateVarReference(context, node);
            break;
        case AST_BINOP:
            generateExpression(context, node->as.binop.left, stackOffset);
            fprintf(context->output, "    mov [rbp - %d], rax\n", stackOffset);
            generateExpression(context, node->as.binop.right, stackOffset + 8);
            fprintf(context->output, "    mov rbx, rax\n");
            fprintf(context->output, "    mov rax, [rbp - %d]\n", stackOffset);
            switch (node->as.binop.op) {
                case OP_ADD:
                    fprintf(context->output, "    add rax, rbx\n");
                    break;
                case OP_SUB:
                    fprintf(context->output, "    sub rax, rbx\n");
                    break;
                case OP_MULT:
                    fprintf(context->output, "    imul rax, rbx\n");
                    break;
                case OP_DIV:
                    fprintf(context->output, "    cqo\n");
                    fprintf(context->output, "    idiv rbx\n");
                    break;
            }
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
        case AST_VAR_DECL:
            generateVarDeclaration(context, node);
            break;
        default:
            fprintf(stderr, "Error: Unknown node type in code generation\n");
            exit(1);
    }
}