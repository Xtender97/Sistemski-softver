#pragma once
#include "Enums.h"
#include "Symbol.h"
#include <vector>

class RelocationRecord
{

public:
    static vector<string> RelocationTypeMap;
    short int offset;
    RelocationType type;
    Symbol *symbol;
    bool local;

    RelocationRecord(short int offset, RelocationType type, Symbol *symbol, bool local);

    void print();

    void printToFile();
};