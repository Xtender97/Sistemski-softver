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

    RelocationRecord(short int offset, RelocationType type, Symbol *symbol);

    void print();
};