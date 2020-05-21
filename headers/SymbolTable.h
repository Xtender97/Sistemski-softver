#pragma once
#include <unordered_map>
#include "Symbol.h"

class SymbolTable
{

private:
    SymbolTable();
    static SymbolTable *instance;

    SymbolTable(const SymbolTable &c);
    SymbolTable &operator=(const SymbolTable &c);

public:
    int max_serial;

    static SymbolTable *getInstance();

    unordered_map<string, Symbol *> symbolTable;

    void backPatch(); // not implemented

    void addSymbol(Symbol *symbol);

    bool symbolExists(string symbol_name);

    Symbol * getSymbol(string symbol_name);

    void sort(); // not implemented

    void print();

    void printAllSectionContents();

    void printAllRelocationTables();
};
