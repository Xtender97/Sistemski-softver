#pragma once
#include <string>
#include <vector>


using namespace std;


class Symbol
{
public:
    string name;
    Symbol* section;
    bool isDefined;
    short int value;
    int serialNumber;
    char scope;
    vector<int> forwardList;

    Symbol(string name, Symbol* section_serial, bool isDefinition, int val, char scope, int serialNumber);

    Symbol(string name, Symbol* section_serial, bool isDefinition, int val, char scope);
    
    void backPatch();

    void addToForwardList(int offset);

    void print();

    void virtual setSerialNumber(int serial);
};
