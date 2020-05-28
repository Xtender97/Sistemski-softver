#pragma once
#include <string>
#include <vector>

using namespace std;

class Symbol;

struct forwardListElem
{
    int offset;
    int size;
    Symbol *section;
};

class Symbol
{
public:
    string name;
    Symbol *section;
    bool isDefined;
    bool definedInEQU;
    short int value;
    int serialNumber;
    char scope;
    vector<forwardListElem> forwardList;

    Symbol(string name, Symbol *section_serial, bool isDefinition, int val, char scope, int serialNumber);

    Symbol(string name, Symbol *section_serial, bool isDefinition, int val, char scope);

    void backPatch();

    void addToForwardList(int offset, Symbol *section, int nmbOfBytes);

    void print();

    void setEQUDefinition();

    void virtual setSerialNumber(int serial);
};
