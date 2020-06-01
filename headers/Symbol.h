#pragma once
#include <string>
#include <vector>
#include "Enums.h"

using namespace std;

class Symbol;
class RelocationRecord;

struct forwardListElem
{
    int offset;
    int size;
    Symbol *section;
};

struct relocationListElem{
    int offset;
    RelocationType type;
    Symbol *section;
};

class Symbol
{
public:
    string name;
    Symbol *section;
    bool isDefined;
    short int value;
    int serialNumber;
    char scope;
    vector<forwardListElem> forwardList;
    vector<RelocationRecord*> allOffsets;
    RelocationRecord* relocationType;
    bool equDefined;

    Symbol(string name, Symbol *section_serial, bool isDefinition, int val, char scope, int serialNumber);

    Symbol(string name, Symbol *section_serial, bool isDefinition, int val, char scope);

    void backPatch();

    void addToForwardList(int offset, Symbol *section, int nmbOfBytes);

    void addToOffsetList(RelocationRecord* record);

    void print();

    void virtual setSerialNumber(int serial);

    void setEquDefined();

    void setRelocationType(RelocationRecord* record);
};
