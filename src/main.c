#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/fileUtils.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/codeGen.h"

void compileCf (const char* sourceFile, const char* outputFile) {
    char* sourceText = readInputFile(sourceFile);
    Tokenizer* tzr = createTokenizer(sourceText);
    TokenArray* tokArr = createTokenArray();
    while (1) {
        Token* currTok = getNextToken(tzr);
        addToken(tokArr, currTok);
        if (currTok->type == EOF_TOK) {
            break;
        }
    }
    // printf("Tokens received:\n");
    // for (size_t i = 0; i < tokArr->count; i++) {
    //     printf("Token %zu: Type = %d, Value = %s\n", 
    //         i, 
    //         tokArr->tokens[i]->type,
    //         tokArr->tokens[i]->value ? tokArr->tokens[i]->value : "NULL");
    // }
    AstNode* programAst = parse(tokArr, sourceFile);
    printf("----------------\n");
    printf("AST Structure:\n");
    printAst(programAst, 4);
    printf("----------------\n////////////////\n");
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        fprintf(stderr, "Could not open output file %s\n", outputFile);
        free(sourceText);
        freeTokenizer(tzr);
        exit(1);
    }
    CodeGenContext* context = createCodeGenContext(output);
    generateCode(context, programAst);
    freeCodeGenContext(context);
// cleanup:
    printf("----------------\nToken Array Contents:\n");
    for (size_t i = 0; i < tokArr->count; i++) {
        printf("%zu: Type = ", i);
        switch (tokArr->tokens[i]->type) {
            case NUM_TOK:
                printf("NUMBER, Value = %s\n", tokArr->tokens[i]->value); break;
            case SEMI_TOK:
                printf("SEMICOLON\n"); break;
            case EOF_TOK:
                printf("EOF\n"); break;
            case RET_TOK:
                printf("RETURN, Value = %s\n", tokArr->tokens[i]->value); break;
            case DIV_TOK:
                printf("DIV\n"); break;
            case MULT_TOK:
                printf("MULT\n"); break;
            case PLUS_TOK:
                printf("PLUS\n"); break;
            case MINUS_TOK:
                printf("MINUS\n"); break;
            case LPAREN_TOK:
                printf("LPAREN\n"); break;
            case RPAREN_TOK:
                printf("RPAREN\n"); break;
            case EQ_TOK:
                printf("EQ\n"); break;
            case VAR_TOK:
                printf("VAR\n"); break;
            case IDENT_TOK:
                printf("IDENT\n"); break;
            case IF_TOK:
                printf("IF\n"); break;
            case ELSE_TOK:
                printf("ELSE\n"); break;
            case LBRACE_TOK:
                printf("LBRACE\n"); break;
            case RBRACE_TOK:
                printf("RBRACE\n"); break;
            default:
                printf("UNKNOWN\n");
        }
    }
    printf("Total tokens: %zu\n----------------\n\n", tokArr->count);
    fclose(output);
    freeAstNode(programAst);
    freeTokenArray(tokArr);
    freeTokenizer(tzr);
    free(sourceText);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr,"Wrong format, correct is: cf <inputFile.cf> <asmOutputName.asm>");
        return EXIT_FAILURE;
    }
    printf("Ingesting input file: %s\n",argv[1]);
    compileCf(argv[1],argv[2]);
    return EXIT_SUCCESS;
}
