#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

AstNode* parse(TokenArray* tokens, const char* fileName);
static AstNode* parseProgram(Parser* parser);
static AstNode* parseReturnStatement(Parser* parser);
static AstNode* parseVarDeclaration(Parser* parser);
static AstNode* parseIfStatement(Parser* parser);
static AstNode* parseStatement(Parser* parser);
static AstNode* parseExpression(Parser* parser);
static AstNode* parseArithmetic(Parser* parser);  
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

static AstNode* parseIfStatement(Parser* parser) {
    Token* ifToken = advance(parser);
    AstNode* ifNode = malloc(sizeof(AstNode));
    ifNode->type = AST_IF;
    ifNode->ln = ifToken->ln;
    ifNode->col = ifToken->col;
    if (!match(parser, LPAREN_TOK)) {
        parserError(parser, "Expected '(' after 'si'");
    }
    advance(parser);
    ifNode->as.ifStmt.condition = parseExpression(parser);
    if (!ifNode->as.ifStmt.condition) {
        parserError(parser, "Expected condition in if statement");
    }
    if (!match(parser, RPAREN_TOK)) {
        parserError(parser, "Expected ')' after condition");
    }
    advance(parser);
    if (!match(parser, LBRACE_TOK)) {
        parserError(parser, "Expected '{' after condition");
    }
    advance(parser);
    ifNode->as.ifStmt.thenStmts = malloc(sizeof(AstNode*) * 16);
    ifNode->as.ifStmt.thenCount = 0;
    while (!match(parser, RBRACE_TOK)) {
        AstNode* stmt = parseStatement(parser);
        if (!stmt) {
            parserError(parser, "Invalid statement in if block");
        }
        ifNode->as.ifStmt.thenStmts[ifNode->as.ifStmt.thenCount++] = stmt;
    }
    advance(parser);
    ifNode->as.ifStmt.elseStmts = NULL;
    ifNode->as.ifStmt.elseCount = 0;
    if (match(parser, ELSE_TOK)) {
        advance(parser);
        if (!match(parser, LBRACE_TOK)) {
            parserError(parser, "Expected '{' after 'sinon'");
        }
        advance(parser);
        ifNode->as.ifStmt.elseStmts = malloc(sizeof(AstNode*) * 16);
        while (!match(parser, RBRACE_TOK)) {
            AstNode* stmt = parseStatement(parser);
            if (!stmt) {
                parserError(parser, "Invalid statement in else block");
            }
            ifNode->as.ifStmt.elseStmts[ifNode->as.ifStmt.elseCount++] = stmt;
        }
        advance(parser);
    }
    return ifNode;
}

static AstNode* parseStatement(Parser* parser) {
    Token* current = peek(parser);
    if (!current) {
        parserError(parser, "Unexpected end of input");
    }
    printf("Parsing statement, current token type: %d\n", current->type);
    if (match(parser, RET_TOK)) {
        return parseReturnStatement(parser);
    }
    if (match(parser, VAR_TOK)) {
        return parseVarDeclaration(parser);
    }
    if (match(parser, IF_TOK)) {
        return parseIfStatement(parser);
    }
    if (match(parser, NUM_TOK) || match(parser, IDENT_TOK) || match(parser, LPAREN_TOK)) {
        return parseExpression(parser);
    }
    parserError(parser, "Expected statement");
    return NULL;
}

static AstNode* parseReturnStatement(Parser* parser) {
    advance(parser);  // consume rendre
    
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
    AstNode* left = parseArithmetic(parser);
    if (!left) {
        parserError(parser, "Expected expression");
    }
    while (match(parser, EQEQ_TOK) || match(parser, NEQ_TOK) || match(parser, LT_TOK) || match(parser, LEQ_TOK) || match(parser, GT_TOK) || match(parser, GEQ_TOK)) {
        Token* op = advance(parser);
        AstNode* right = parseArithmetic(parser);
        if (!right) {
            parserError(parser, "Expected expression after operator");
        }
        AstNode* binop = malloc(sizeof(AstNode));
        binop->type = AST_BINOP;
        binop->ln = op->ln;
        binop->col = op->col;
        binop->as.binop.left = left;
        binop->as.binop.right = right;
        switch (op->type) {
            case EQEQ_TOK: binop->as.binop.op = OP_EQ; break;
            case NEQ_TOK:  binop->as.binop.op = OP_NEQ; break;
            case LT_TOK:   binop->as.binop.op = OP_LT; break;
            case LEQ_TOK:  binop->as.binop.op = OP_LEQ; break;
            case GT_TOK:   binop->as.binop.op = OP_GT; break;
            case GEQ_TOK:  binop->as.binop.op = OP_GEQ; break;
            default:
                parserError(parser, "Invalid comparison operator");
        }
        left = binop;
    }
    return left;
}

static AstNode* parseArithmetic(Parser* parser) {
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
        case AST_IF:
            freeAstNode(node->as.ifStmt.condition);
            for (size_t i = 0; i < node->as.ifStmt.thenCount; i++) {
                freeAstNode(node->as.ifStmt.thenStmts[i]);
            }
            free(node->as.ifStmt.thenStmts);
            if (node->as.ifStmt.elseStmts) {
                for (size_t i = 0; i < node->as.ifStmt.elseCount; i++) {
                    freeAstNode(node->as.ifStmt.elseStmts[i]);
                }
                free(node->as.ifStmt.elseStmts);
            }
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
                case OP_ADD: printf("+\n"); break;
                case OP_SUB: printf("-\n"); break;
                case OP_MULT: printf("*\n"); break;
                case OP_DIV: printf("/\n"); break;
                case OP_EQ: printf("==\n"); break;
                case OP_NEQ: printf("!=\n"); break;
                case OP_LT: printf("<\n"); break;
                case OP_LEQ: printf("<=\n"); break;
                case OP_GT: printf(">\n"); break;
                case OP_GEQ: printf(">=\n"); break;
            }
            printf("%*sLeft: ", indent + 2, "");
            printAst(node->as.binop.left, 0);
            printf("%*sRight: ", indent + 2, "");
            printAst(node->as.binop.right, 0);
            break;
        case AST_IF:
            printf("If Statement\n");
            printf("%*sCondition:\n", indent + 2, "");
            printAst(node->as.ifStmt.condition, indent + 2);
            printf("%*sThen Block:\n", indent + 2, "");
            for (size_t i = 0; i < node->as.ifStmt.thenCount; i++) {
                printAst(node->as.ifStmt.thenStmts[i], indent + 3);
            }
            if (node->as.ifStmt.elseCount > 0) {
                printf("%*sElse Block:\n", indent + 2, "");
                for (size_t i = 0; i < node->as.ifStmt.elseCount; i++) {
                    printAst(node->as.ifStmt.elseStmts[i], indent + 3);
                }
            }
            break;
    }
}
