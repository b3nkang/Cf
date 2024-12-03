#pragma once

#include "tokenizer.h"

typedef enum {
    AST_PROG,
    AST_NUM,
    AST_RET,
    AST_BINOP,
    AST_VAR_DECL,
    AST_VAR_REF,
    AST_IF
} AstNodeType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MULT,
    OP_DIV,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_LEQ,
    OP_GT,
    OP_GEQ
} BinaryOpType;

typedef struct AstNode {
    AstNodeType type;
    int ln;
    int col;
    union {
        struct {
            struct AstNode** stmts;
            size_t count;
        } program;
        struct {
            struct AstNode* val;
        } retStmt; 
        struct {
            int val;
        } num;
        struct {
            BinaryOpType op;
            struct AstNode* left;
            struct AstNode* right;
        } binop;
        struct {
            char* name;
            struct AstNode* initializer;
        } varDecl;
        struct {
            char* name;
        } varRef;
        struct {
            struct AstNode* condition;
            struct AstNode** thenStmts;
            size_t thenCount;
            struct AstNode** elseStmts;
            size_t elseCount;
        } ifStmt;
    } as;
} AstNode;

typedef struct {
    TokenArray* tokens;
    size_t currPos;
    const char* fileName;
} Parser;

AstNode* parse(TokenArray* tokens, const char* filename);
void freeAstNode(AstNode* node);
void printAst(AstNode* node, int indent);
