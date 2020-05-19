#pragma once
#include "Enums.h"
#include "Symbol.h"

class RelocationRecord
{
    int offset;
    RelocationType type;
    Symbol *symbol;
};