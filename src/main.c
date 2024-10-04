#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/fileUtils.h"
#include "../include/tokenize.h"

void compileCf (const char* sourceFile, const char* outputFile, int num) {
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
    for (;;) {
        currTok = getNextToken(tzr);
        switch (currTok->type) {
            case RET_TOK: {
                Token* valueToken = getNextToken(tzr);
                if (valueToken->type == NUM_TOK) {
                    fprintf(output, "global _main\n");
                    fprintf(output, "section .text\n");
                    fprintf(output, "_main:\n");
                    fprintf(output, "    mov rax, %s\n", valueToken->value);
                    fprintf(output, "    ret\n");
                }
                freeToken(valueToken);
                break;
            }
            case EOF_TOK:
                freeToken(currTok);
                goto cleanup;
            default:
                freeToken(currTok);
                goto cleanup;
        }
    }
cleanup:
    fclose(output);
    free(sourceText);
    freeTokenizer(tzr);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr,"Wrong format, correct is: cf <inputFile.cf>");
        return EXIT_FAILURE;
    }
    printf("%s\n",argv[1]);
    compileCf("test.cf","test2.asm", atoi(argv[1]));
    return EXIT_SUCCESS;
}
