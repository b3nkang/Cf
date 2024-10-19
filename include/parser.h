#include "tokenizer.h"

typedef enum {
    AST_PROG,
    AST_NUM,
    AST_RET
} AstNodeType;

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

    } as;
} AstNode;

typedef struct {
    TokenArray* tokens;
    size_t currPos;
    const char* fileName;
} Parser;

AstNode* parse(TokenArray* tokens, const char* filename);
void freeAstNode(AstNode* node);
