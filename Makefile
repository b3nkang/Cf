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
TEST_FILE_INPUT = test.cf

# Source files
SRCS = src/main.c src/tokenizer.c src/fileUtils.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(COMPILER)

# Compile the compiler
$(COMPILER): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for object files
src/%.o: src/%.c
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

# Full pipeline: compile CF file and run resulting executable
full: compile_cf $(EXEC)
	@echo "Running generated program:"
	./$(EXEC) || true
	@echo "Direct exit code: $$?"
	@echo "\nRunning test with system:"
	@bash -c './$(EXEC); echo $$?'

.PHONY: all clean compile_cf full