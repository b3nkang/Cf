#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

AstNode* parse(TokenArray* tokens, const char* fileName);
static AstNode* parseProgram(Parser* parser);
static AstNode* parseStatement(Parser* parser);
static AstNode* parseReturnStatement(Parser* parser);
static AstNode* parseExpression(Parser* parser);
static AstNode* parseVarDeclaration(Parser* parser);
static AstNode* parseTerm(Parser* parser);
static AstNode* parseFactor(Parser* parser);
static AstNode* parsePrimary(Parser* parser);

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
    if (match(parser, VAR_TOK)) {
        return parseVarDeclaration(parser);
    }
    return parseExpression(parser);
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
    AstNode* left = parseTerm(parser);
    while (match(parser, PLUS_TOK) || match(parser, MINUS_TOK)) {
        Token* op = advance(parser);
        AstNode* right = parseTerm(parser);
        AstNode* binop = malloc(sizeof(AstNode));
        binop->type = AST_BINOP;
        binop->ln = op->ln;
        binop->col = op->col;
        binop->as.binop.left = left;
        binop->as.binop.right = right;
        binop->as.binop.op = (op->type == PLUS_TOK) ? OP_ADD : OP_SUB;
        left = binop;
    }
    return left;
}

static AstNode* parseVarDeclaration(Parser* parser) {
    Token* varToken = advance(parser);  // consume var
    if (!match(parser, IDENT_TOK)) {
        parserError(parser, "Expected identifier after the variable (e.g. assigne)");
    }
    Token* nameToken = advance(parser);
    if (!match(parser, EQ_TOK)) {
        parserError(parser, "Expected '=' after identifier in variable declaration");
    }
    advance(parser);    // consume '='
    AstNode* initializer = parseExpression(parser);
    if (!match(parser, SEMI_TOK)) {
        parserError(parser, "Expected ';' after variable declaration");
    }
    advance(parser);    // consume ';'
    AstNode* node = malloc(sizeof(AstNode));
    node->type = AST_VAR_DECL;
    node->ln = varToken->ln;
    node->col = varToken->col;
    node->as.varDecl.name = strdup(nameToken->value);
    node->as.varDecl.initializer = initializer;
    return node;
}

static AstNode* parseTerm(Parser* parser) {
    AstNode* left = parseFactor(parser);
    while (match(parser, MULT_TOK) || match(parser, DIV_TOK)) {
        Token* op = advance(parser);
        AstNode* right = parseFactor(parser);
        
        AstNode* binop = malloc(sizeof(AstNode));
        binop->type = AST_BINOP;
        binop->ln = op->ln;
        binop->col = op->col;
        binop->as.binop.left = left;
        binop->as.binop.right = right;
        binop->as.binop.op = (op->type == MULT_TOK) ? OP_MULT : OP_DIV;
        
        left = binop;
    }
    return left;
}


static AstNode* parseFactor(Parser* parser) {
    if (match(parser, LPAREN_TOK)) {
        advance(parser);  // consume (
        AstNode* expr = parseExpression(parser);
        
        if (!match(parser, RPAREN_TOK)) {
            parserError(parser, "Expected ')'");
        }
        advance(parser);  // consume )
        return expr;
    }
    return parsePrimary(parser);
}

static AstNode* parsePrimary(Parser* parser) {
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
    if (current->type == IDENT_TOK) {
        Token* idToken = advance(parser);
        AstNode* node = malloc(sizeof(AstNode));
        node->type = AST_VAR_REF;
        node->ln = idToken->ln;
        node->col = idToken->col;
        node->as.varRef.name = strdup(idToken->value);
        return node;
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
        case AST_BINOP:
            freeAstNode(node->as.binop.left);
            freeAstNode(node->as.binop.right);
            break;
        case AST_VAR_DECL:
            free(node->as.varDecl.name);
            freeAstNode(node->as.varDecl.initializer);
            break;
        case AST_VAR_REF:
            free(node->as.varRef.name);
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
        case AST_VAR_DECL:
            printf("Variable Declaration: %s\n", node->as.varDecl.name);
            printf("%*sInitializer:\n", indent + 2, "");
            printAst(node->as.varDecl.initializer, indent + 2);
            break;
        case AST_VAR_REF:
            printf("Variable Reference: %s\n", node->as.varRef.name);
            break;
        case AST_BINOP:
            printf("Binary Operation: ");
            switch (node->as.binop.op) {
                case OP_ADD:
                    printf("+\n");
                    break;
                case OP_SUB:
                    printf("-\n");
                    break;
                case OP_MULT:
                    printf("*\n");
                    break;
                case OP_DIV:
                    printf("/\n");
                    break;
            }
            printf("%*sLeft: ", indent + 2, "");
            printAst(node->as.binop.left, 0);
            printf("%*sRight: ", indent + 2, "");
            printAst(node->as.binop.right, 0);
            break;
    }
}
