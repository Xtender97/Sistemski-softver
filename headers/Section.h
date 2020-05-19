#pragma once

#include "Symbol.h"
#include "SectionContent.h"
#include "RelocationTable.h"

class Section : public Symbol
{
    int size;
    SectionContent *content;
    RelocationTable *relocationTable;

    Section(string n, int section_serail, bool definition, int val, char global_or_local);
};