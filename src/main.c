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
    // FILE* output = fopen(outputFile, "w");
    // if (!output) {
    //     fprintf(stderr, "Could not open output file %s\n", outputFile);
    //     free(sourceText);
    //     freeTokenizer(tzr);
    //     exit(1);
    // }
    // Token* currTok;
    TokenArray* tokArr = createTokenArray();
    // for (;;) {
    //     currTok = getNextToken(tzr);
    //     switch (currTok->type) {
    //         case RET_TOK: {
    //             addToken(tokArr,currTok);
    //             // Token* valueTok = getNextToken(tzr);
    //             // if (valueTok->type == NUM_TOK) {
    //             //     addToken(tokArr,valueTok);
    //             //     fprintf(output, "global _main\n");
    //             //     fprintf(output, "section .text\n");
    //             //     fprintf(output, "_main:\n");
    //             //     fprintf(output, "    mov rax, %s\n", valueTok->value);
    //             //     fprintf(output, "    ret\n");
    //             // }
    //             // freeToken(valueTok);
    //             continue;
    //         }
    //         case EOF_TOK:
    //             addToken(tokArr,currTok);
    //             // freeToken(currTok);
    //             // goto cleanup;
    //             break;
    //         case SEMI_TOK:
    //             addToken(tokArr,currTok);
    //             continue;
    //         case NUM_TOK:
    //             addToken(tokArr,currTok);
    //             continue;
    //         default:
    //             printf("error unrecognized token");
    //             // freeToken(currTok);
    //             // goto cleanup;
    //             break;
    //     }
    // }
    while (1) {
        Token* currTok = getNextToken(tzr);
        addToken(tokArr, currTok);
        if (currTok->type == EOF_TOK) {
            break;
        }
    }
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
    // fprintf(output, "global _main\n");
    // fprintf(output, "section .text\n");
    // fprintf(output, "_main:\n");

    // // TODO: place with proper traversl of ast
    // if (programAst->type == AST_PROG && 
    //     programAst->as.program.count > 0 &&
    //     programAst->as.program.stmts[0]->type == AST_RET) {
        
    //     AstNode* returnNode = programAst->as.program.stmts[0];
    //     if (returnNode->as.retStmt.val->type == AST_NUM) {
    //         fprintf(output, "    mov rax, %d\n", returnNode->as.retStmt.val->as.num.val);
    //     }
    // }
    // fprintf(output, "    ret\n");
    CodeGenContext* context = createCodeGenContext(output);
    generateCode(context, programAst);
    freeCodeGenContext(context);

// cleanup:
    printf("----------------\nToken Array Contents:\n");
    for (size_t i = 0; i < tokArr->count; i++) {
        printf("%zu: Type = ", i);
        switch (tokArr->tokens[i]->type) {
            case NUM_TOK:
                printf("NUMBER, Value = %s\n", tokArr->tokens[i]->value);
                break;
            case SEMI_TOK:
                printf("SEMICOLON\n");
                break;
            case EOF_TOK:
                printf("EOF\n");
                break;
            case RET_TOK:
                printf("RETURN, Value = %s\n", tokArr->tokens[i]->value);
                break;
            case DIV_TOK:
                printf("DIV\n");
                break;
            case MULT_TOK:
                printf("MULT\n");
                break;
            case PLUS_TOK:
                printf("PLUS\n");
                break;
            case MINUS_TOK:
                printf("MINUS\n");
                break;
            case LPAREN_TOK:
                printf("LPAREN\n");
                break;
            case RPAREN_TOK:
                printf("RPAREN\n");
                break;
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
    if (argc != 2) {
        fprintf(stderr,"Wrong format, correct is: cf <inputFile.cf>");
        return EXIT_FAILURE;
    }
    printf("Ingesting input file: %s\n",argv[1]);
    compileCf(argv[1],"test2.asm");
    return EXIT_SUCCESS;
}
