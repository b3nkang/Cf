# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Assembly settings
ASM = nasm
ASMFLAGS = -f macho64
LDFLAGS = -lSystem -syslibroot $(shell xcrun -sdk macosx --show-sdk-path) -e _main -arch x86_64 -platform_version macos 13.0.0 13.0.0

# Files
COMPILER = cf
ASM_FILE = test2.asm
OBJ_FILE = program.o
EXEC = program
TEST_FILE_INPUT = test2.cf

# Source files
SRCS = src/main.c src/tokenizer.c src/fileUtils.c src/parser.c src/codeGen.c

# Object files are generated from source files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = include/fileUtils.h include/tokenize.h include/parser.h include/codeGen.h

# Default target
all: $(COMPILER)

# Compile the compiler - Now depends on headers too
$(COMPILER): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for object files - Added header dependency
src/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the compiler on test input
compile_cf: $(COMPILER)
	./$(COMPILER) $(TEST_FILE_INPUT)

# Compile assembly to object file
$(OBJ_FILE): $(ASM_FILE)
	$(ASM) $(ASMFLAGS) $< -o $@

# Link object file to create executable
$(EXEC): $(OBJ_FILE)
	ld $(LDFLAGS) $< -o $@

# Clean build files
clean:
	rm -f $(COMPILER) $(OBJ_FILE) $(EXEC) $(ASM_FILE) $(OBJS)
	rm -f src/*.o
	rm -f $(COMPILER)

# Full pipeline: compile CF file and run resulting executable
full: compile_cf $(EXEC)
	@echo "Running generated program:"
	./$(EXEC) || true
	@echo "Direct exit code: $$?"
	@echo "\nRunning test with system:"
	@bash -c './$(EXEC); echo $$?'

.PHONY: all clean compile_cf full