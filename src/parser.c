#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

AstNode* parse(TokenArray* tokens, const char* fileName);
static AstNode* parseProgram(Parser* parser);
static AstNode* parseStatement(Parser* parser);
static AstNode* parseReturnStatement(Parser* parser);
static AstNode* parseExpression(Parser* parser);

static Token* peek(Parser* parser) {
    if (parser->currPos >= parser->tokens->count) {
        return NULL;
    }
    return parser->tokens->tokens[parser->currPos];
}

static Token* advance(Parser* parser) {
    Token* current = peek(parser);
    parser->currPos++;
    return current;
}

static int match(Parser* parser, TokenType type) {
    Token* current = peek(parser);
    return current && current->type == type;
}

static void parserError(Parser* parser, const char* message) {
    Token* current = peek(parser);
    fprintf(stderr, "%s:%d: error: %s\n", parser->fileName, current ? current->ln : 0, message);
    exit(1);
}

AstNode* parse(TokenArray* tokens, const char* fileName) {
    Parser parser = {
        .tokens = tokens,
        .currPos = 0,
        .fileName = fileName
    };
    return parseProgram(&parser);
}

static AstNode* parseProgram(Parser* parser) {
    AstNode* program = malloc(sizeof(AstNode));
    program->type = AST_PROG;
    program->as.program.stmts = malloc(sizeof(AstNode*) * 16); // keep 16 for now as intial cap
    program->as.program.count = 0;
    
    while (!match(parser, EOF_TOK)) {
        AstNode* stmt = parseStatement(parser);
        program->as.program.stmts[program->as.program.count++] = stmt;
    }
    
    return program;
}

static AstNode* parseStatement(Parser* parser) {
    if (match(parser, RET_TOK)) {
        return parseReturnStatement(parser);
    }
    parserError(parser, "Expected statement");
    return NULL;
}

static AstNode* parseReturnStatement(Parser* parser) {
    advance(parser);  // consume retourner
    
    AstNode* returnNode = malloc(sizeof(AstNode));
    returnNode->type = AST_RET;
    returnNode->as.retStmt.val = parseExpression(parser);
    
    if (!match(parser, SEMI_TOK)) {
        parserError(parser, "Expected semicolon after return value");
    }
    advance(parser);  // consume semi
    
    return returnNode;
}

static AstNode* parseExpression(Parser* parser) {
    Token* current = peek(parser);
    if (current->type == NUM_TOK) {
        Token* numToken = advance(parser);
        AstNode* numNode = malloc(sizeof(AstNode));
        numNode->type = AST_NUM;
        numNode->ln = numToken->ln;
        numNode->col = numToken->col;
        numNode->as.num.val = atoi(numToken->value);
        return numNode;
    }
    parserError(parser, "Expected expression");
    return NULL;
}

void freeAstNode(AstNode* node) {
    if (node == NULL) return;
    switch (node->type) {
        case AST_PROG:
            for (size_t i = 0; i < node->as.program.count; i++) {
                freeAstNode(node->as.program.stmts[i]);
            }
            free(node->as.program.stmts);
            break;
        case AST_RET:
            freeAstNode(node->as.retStmt.val);
            break;
        case AST_NUM:
            break;
    }    
    free(node);
}

void printAst(AstNode* node, int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    switch (node->type) {
        case AST_PROG:
            printf("Program (statements: %zu)\n", node->as.program.count);
            for (size_t i = 0; i < node->as.program.count; i++) {
                printAst(node->as.program.stmts[i], indent + 1);
            }
            break;  
        case AST_RET:
            printf("Return Statement\n");
            printAst(node->as.retStmt.val, indent + 1);
            break; 
        case AST_NUM:
            printf("Number: %d\n", node->as.num.val);
            break;
    }
}
