#pragma once

#include <stdlib.h>

typedef struct Symbol {
    char* name;
    int stackOffset;
    struct Symbol* next;
} Symbol;

typedef struct SymbolTable {
    Symbol* symbols;
    int nextOffset;
} SymbolTable;

SymbolTable* createSymbolTable(void);
Symbol* lookupSymbol(SymbolTable* table, const char* name);
Symbol* addSymbol(SymbolTable* table, const char* name);
void freeSymbolTable(SymbolTable* table);