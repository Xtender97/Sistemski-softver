#pragma once

#include "Symbol.h"
#include "SectionContent.h"
#include "RelocationTable.h"

class Section : public Symbol
{
public:
    int size;
    SectionContent *content;
    RelocationTable *relocationTable;

    Section(string n, bool definition, int val, char global_or_local, int serialNumber);

    Section(string name);


    void addContent(unsigned char * content, int size);

    void addRelocation(RelocationRecord * relocation);

    void setSize(int size);

    void setSerialNumber(int serial);
};