#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/fileUtils.h"
#include "../include/tokenizer.h"

void compileCf (const char* sourceFile, const char* outputFile) {
    char* sourceText = readInputFile(sourceFile);
    Tokenizer* tzr = createTokenizer(sourceText);
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        fprintf(stderr, "Could not open output file %s\n", outputFile);
        free(sourceText);
        freeTokenizer(tzr);
        exit(1);
    }
    Token* currTok;
    TokenArray* tokArr = createTokenArray();
    for (;;) {
        currTok = getNextToken(tzr);
        switch (currTok->type) {
            case RET_TOK: {
                addToken(tokArr,currTok);
                Token* valueTok = getNextToken(tzr);
                if (valueTok->type == NUM_TOK) {
                    addToken(tokArr,valueTok);
                    fprintf(output, "global _main\n");
                    fprintf(output, "section .text\n");
                    fprintf(output, "_main:\n");
                    fprintf(output, "    mov rax, %s\n", valueTok->value);
                    fprintf(output, "    ret\n");
                }
                // freeToken(valueTok);
                continue;
            }
            case EOF_TOK:
                addToken(tokArr,currTok);
                // freeToken(currTok);
                goto cleanup;
            case SEMI_TOK:
                addToken(tokArr,currTok);
                continue;
            case NUM_TOK:
                addToken(tokArr,currTok);
                continue;
            default:
                printf("error unrecognized token");
                // freeToken(currTok);
                goto cleanup;
        }
    }
cleanup:
    printf("\n----------------\nToken Array Contents:\n");
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
            default:
                printf("UNKNOWN\n");
        }
    }
    printf("Total tokens: %zu\n----------------\n\n", tokArr->count);
    fclose(output);
    free(sourceText);
    freeTokenArray(tokArr);
    freeTokenizer(tzr);
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
