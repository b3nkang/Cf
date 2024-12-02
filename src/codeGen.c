#include "../include/codeGen.h"
#include <stdlib.h>
#include <stdarg.h>

#define TEMP_STACK_START 1024

CodeGenContext* createCodeGenContext(FILE* output) {
    CodeGenContext* context = malloc(sizeof(CodeGenContext));
    context->output = output;
    context->currentFunction = NULL;
    context->labelCount = 0;
    context->symbols = createSymbolTable();
    context->varStackOffset = 0;
    context->tempStackOffsetStart = TEMP_STACK_START;
    context->tempStackOffset = context->tempStackOffsetStart;
    context->maxVarOffset = 0;
    context->minTempOffset = context->tempStackOffsetStart;
    context->codeBuffer = NULL;
    context->bufferSize = 0;
    context->bufferCapacity = 0;
    return context;
}

void freeCodeGenContext(CodeGenContext* context) {
    freeSymbolTable(context->symbols);
    free(context->codeBuffer);
    free(context);
}

void appendToBuffer(CodeGenContext* context, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int neededSize = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);
    if (context->bufferSize + neededSize > context->bufferCapacity) {
        context->bufferCapacity = (context->bufferCapacity + neededSize) * 2;
        context->codeBuffer = realloc(context->codeBuffer, context->bufferCapacity);
    }
    va_start(args, format);
    vsprintf(context->codeBuffer + context->bufferSize, format, args);
    va_end(args);
    context->bufferSize += neededSize - 1;
}

void generateVarDeclaration(CodeGenContext* context, AstNode* node) {
    generateExpression(context, node->as.varDecl.initializer);
    Symbol* sym = addSymbol(context->symbols, node->as.varDecl.name);
    if (!sym) {
        fprintf(stderr, "Error: Variable '%s' already declared\n", node->as.varDecl.name);
        exit(1);
    }
    context->varStackOffset += 8;
    sym->stackOffset = context->varStackOffset;
    if (context->varStackOffset > context->maxVarOffset) {
        context->maxVarOffset = context->varStackOffset;
    }
    appendToBuffer(context, "    mov [rbp - %d], rax\n", sym->stackOffset);
}

void generateVarReference(CodeGenContext* context, AstNode* node) {
    Symbol* sym = lookupSymbol(context->symbols, node->as.varRef.name);
    if (!sym) {
        fprintf(stderr, "Error: Undefined variable '%s'\n", node->as.varRef.name);
        exit(1);
    }
    appendToBuffer(context, "    mov rax, [rbp - %d]\n", sym->stackOffset);
}

void generateExpression(CodeGenContext* context, AstNode* node) {
    switch (node->type) {
        case AST_NUM:
            appendToBuffer(context, "    mov rax, %d\n", node->as.num.val);
            break;
        case AST_VAR_REF:
            generateVarReference(context, node);
            break;
        case AST_BINOP: {
            context->tempStackOffset -= 8;
            if (context->tempStackOffset <= context->varStackOffset) {
                fprintf(stderr, "Error: Stack overflow due to too many temporaries\n");
                exit(1);
            }
            int leftTempOffset = context->tempStackOffset;
            if (context->tempStackOffset < context->minTempOffset) {
                context->minTempOffset = context->tempStackOffset;
            }
            generateExpression(context, node->as.binop.left);
            appendToBuffer(context, "    mov [rbp - %d], rax\n", leftTempOffset);
            generateExpression(context, node->as.binop.right);
            appendToBuffer(context, "    mov rbx, rax\n");
            appendToBuffer(context, "    mov rax, [rbp - %d]\n", leftTempOffset);
            context->tempStackOffset += 8;
            switch (node->as.binop.op) {
                case OP_ADD:
                    appendToBuffer(context, "    add rax, rbx\n");
                    break;
                case OP_SUB:
                    appendToBuffer(context, "    sub rax, rbx\n");
                    break;
                case OP_MULT:
                    appendToBuffer(context, "    imul rax, rbx\n");
                    break;
                case OP_DIV:
                    appendToBuffer(context, "    cqo\n");
                    appendToBuffer(context, "    idiv rbx\n");
                    break;
                case OP_EQ:
                case OP_NEQ:
                case OP_LT:
                case OP_LEQ:
                case OP_GT:
                case OP_GEQ:
                    appendToBuffer(context, "    cmp rax, rbx\n");
                    appendToBuffer(context, "    mov rax, 0\n");
                    switch (node->as.binop.op) {
                        case OP_EQ:
                            appendToBuffer(context, "    sete al\n");
                            break;
                        case OP_NEQ:
                            appendToBuffer(context, "    setne al\n");
                            break;
                        case OP_LT:
                            appendToBuffer(context, "    setl al\n");
                            break;
                        case OP_LEQ:
                            appendToBuffer(context, "    setle al\n");
                            break;
                        case OP_GT:
                            appendToBuffer(context, "    setg al\n");
                            break;
                        case OP_GEQ:
                            appendToBuffer(context, "    setge al\n");
                            break;
                        default:
                            break;
                    }
                    appendToBuffer(context, "    movzx rax, al\n");
                    break;
                default:
                    fprintf(stderr, "Error: Unsupported binary operator in code generation\n");
                    exit(1);
            }
            break;
        }
        default:
            fprintf(stderr, "Error: Unsupported expression type in code generation\n");
            exit(1);
    }
}

void generateReturn(CodeGenContext* context, AstNode* node) {
    generateExpression(context, node->as.retStmt.val);
    appendToBuffer(context, "    leave\n");
    appendToBuffer(context, "    and rsp, -16\n");
    appendToBuffer(context, "    mov rdi, rax\n");
    appendToBuffer(context, "    mov rax, 0x2000001\n");
    appendToBuffer(context, "    syscall\n");
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

void generateProgram(CodeGenContext* context, AstNode* node) {
    for (size_t i = 0; i < node->as.program.count; i++) {
        generateCode(context, node->as.program.stmts[i]);
    }
    int totalStackSize = context->maxVarOffset + (context->tempStackOffsetStart - context->minTempOffset);
    if (totalStackSize % 16 != 0) {
        totalStackSize += 16 - (totalStackSize % 16);
    }
    fprintf(context->output, "global _main\n");
    fprintf(context->output, "section .text\n");
    fprintf(context->output, "_main:\n");
    fprintf(context->output, "    push rbp\n");
    fprintf(context->output, "    mov rbp, rsp\n");
    fprintf(context->output, "    sub rsp, %d\n", totalStackSize);
    fwrite(context->codeBuffer, 1, context->bufferSize, context->output);
    free(context->codeBuffer);
    context->codeBuffer = NULL;
    context->bufferSize = 0;
    context->bufferCapacity = 0;
}
