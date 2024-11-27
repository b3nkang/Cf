#include <string.h>
#include "../include/symTab.h"

SymbolTable* createSymbolTable() {
    SymbolTable* table = malloc(sizeof(SymbolTable));
    table->symbols = NULL;
    table->nextOffset = 8;
    return table;
}

Symbol* lookupSymbol(SymbolTable* table, const char* name) {
    for (Symbol* sym = table->symbols; sym != NULL; sym = sym->next) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
    }
    return NULL;
}

Symbol* addSymbol(SymbolTable* table, const char* name) {
    if (lookupSymbol(table, name) != NULL) {
        return NULL;
    }
    Symbol* sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->stackOffset = table->nextOffset;
    sym->next = table->symbols;
    table->symbols = sym;
    table->nextOffset += 8;
    return sym;
}

void freeSymbolTable(SymbolTable* table) {
    Symbol* current = table->symbols;
    while (current != NULL) {
        Symbol* next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    free(table);
}