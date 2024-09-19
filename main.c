#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void compileCf (const char* sourceFile, const char* outputFile, int num) {
    FILE* input = fopen(sourceFile, "r");
    if (!input) {
        fprintf(stderr, "Could not open source file %s\n", sourceFile);
        exit(1);
    }    
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        fprintf(stderr, "Could not open output file %s\n", outputFile);
        exit(1);
    }
    fprintf(output, "global _main\n");
    fprintf(output, "section .text\n");
    fprintf(output, "_main:\n");
    fprintf(output, "    mov rax, %d\n", num);
    fprintf(output, "    ret\n");
    fclose(input);
    fclose(output);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr,"Wrong format, correct is: cf <inputFile.cf>");
        return EXIT_FAILURE;
    }
    printf("%s\n",argv[1]);
    compileCf("test.c","test.asm", atoi(argv[1]));
    return EXIT_SUCCESS;
}
